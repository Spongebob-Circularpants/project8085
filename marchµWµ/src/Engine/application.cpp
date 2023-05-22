#include "application.hpp"
#include "splashState.hpp"
#include "imguiUI.hpp"

namespace Engine
{
	//the "kernel"
	Application::Application(bool Fullscreen, std::string title,int width, int height) 
	: 
		m_applicationData(std::make_shared<Engine::applicationData>())
	{
		if (!Fullscreen)
		{
			this->m_applicationData->m_window->create(
					sf::VideoMode(width, height), 
					title , 
					sf::Style::Resize + sf::Style::Close + sf::Style::Titlebar);
		}
		else
		{
			this->m_applicationData->m_window->create(
					sf::VideoMode::getFullscreenModes()[0], 
					title, 
					sf::Style::Fullscreen);
		}

		this->m_applicationData->m_isFullScreen = Fullscreen;
		this->m_applicationData->size.x = width;
		this->m_applicationData->size.y = height;

		//view for letterbox effect
		m_applicationData->view.setSize(width, height);
		m_applicationData->view.setCenter( width/ 2, height/ 2 );
		this->m_applicationData->m_inputs->getLetterBoxView(m_applicationData->view, width, height);
	


		//let the user control this variable later
		//I can imagine it would be quite the headache
		//keep waiting for the splash screen whe you have
		//an exam tomorrow
		bool splashStateEnable = true;
		if(splashStateEnable)
		{
			//splash state kind of acts like a temporary global state
			this->m_applicationData->m_states->addGlobalState(std::make_unique<splashState>(m_applicationData)); 
			this->m_applicationData->m_states->addState(std::make_unique<nullState>()); 
		}
		else
		{
			this->m_applicationData->m_states->addGlobalState(std::make_unique<Engine::imguiUI>(m_applicationData));
			//same line here because this will be some other state later
			this->m_applicationData->m_states->addState(std::make_unique<nullState>()); 
		}
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{	
		this->m_applicationData->m_window->setFramerateLimit(30);
		while (this->m_applicationData->m_window->isOpen())
		{
			//clock
			this->m_applicationData->m_clock.restart();

			//SFML/Dear ImGui Input/Output front-end
			this->m_applicationData->m_states->processStateChange(); //meta-update

			//Input
			this->m_applicationData->m_inputs->pollEvent(
					*(this->m_applicationData->m_window),
					*(this->m_applicationData->m_states->getCurrentState()),
					*(this->m_applicationData->m_states->globalState()));

			//Update
			this->m_applicationData->m_states->globalState()->Update(this->m_delta);
			this->m_applicationData->m_states->getCurrentState()->Update(this->m_delta);
 
			//Draw
        		this->m_applicationData->m_window->clear(sf::Color::Black);
			this->m_applicationData->m_window->setView(this->m_applicationData->view);
			this->m_applicationData->m_states->getCurrentState()->Draw();
			this->m_applicationData->m_states->globalState()->Draw();

			//Display
        		this->m_applicationData->m_window->display();
			
			this->m_delta = this->m_applicationData->m_clock.getElapsedTime();
			//std::cout<<"FPS: "<<1.0/this->m_delta.asSeconds()<<"\n";
/*							
 								|
								|
							  pipe|
								|
							     \ /
								.

				microcontroller backend using the imguiUI class
*/
		}
	}

	unsigned Application::independentAccess(unsigned address)
	{
		return this->m_applicationData->m_muController->m_ram->dmaOutput(address);
	}
}
