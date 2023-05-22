#include "splashState.hpp"
#include "imguiUI.hpp"


namespace Engine
{
	splashState::splashState(std::shared_ptr<applicationData> &data) : m_data(data)
	{
	}

	splashState::~splashState()
	{
	}

	void splashState::Init() 
	{
		m_data->timeAccumulator = 0;
		//load and put required assests for :this state in the map
		this->m_data->m_assets->loadFont(mainFONT, hack_ttfPATH);
		this->m_data->m_assets->loadTexture(splashSCREEN, splashScreenPATH);

		//setting background and font with text
		m_background.setTexture(this->m_data->m_assets->getTexture(splashSCREEN));
		bgWidthScaler = (float)m_data->size.x/(float)m_background.getGlobalBounds().width;
		bgHeightScaler =  (float)m_data->size.y/(float)m_background.getGlobalBounds().height;
		m_background.scale(bgWidthScaler, bgHeightScaler); //default position is (0, 0)

		m_gameTitle.setFont(this->m_data->m_assets->getFont(mainFONT));
		m_gameTitle.setString("capybara");
		m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
		m_gameTitle.setPosition(m_data->size.x / 2, m_data->size.y / 2 - 300.f);

		//add sounds and animations and stuff

	}

	void splashState::processInput() //converts user input into numbers mostly boolean
	{
		if(this->m_data->escAccumulator > transitionTime)
		{
			this->m_data->m_window->close();
		}
		if(this->m_data->m_inputs->m_event.type == sf::Event::Resized)
		{
			this->m_data->size.x = this->m_data->m_inputs->m_event.size.width;
			this->m_data->size.y = this->m_data->m_inputs->m_event.size.height;
			this->m_data->m_inputs->getLetterBoxView(this->m_data->view, this->m_data->size.x, this->m_data->size.y);
		}
		if(this->m_data->m_inputs->m_event.type == sf::Event::MouseMoved)
		{
			this->m_data->mousePosition.x = this->m_data->m_inputs->m_event.mouseMove.x;
			this->m_data->mousePosition.y = this->m_data->m_inputs->m_event.mouseMove.y;
		}
	}

	void splashState::Update(const sf::Time& deltaTime)
	{
		//global window updates;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
		{
			this->m_data->m_isEscButtonPressed = true;
			this->m_data->escAccumulator+= deltaTime.asSeconds();
		}
		else 
		{
			this->m_data->m_isEscButtonPressed = false; 
			this->m_data->escAccumulator = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) { this->m_data->m_isFullScreen = 1;} 

		//state specific process;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
		{ 
			m_isEnterButtonPressed = true;
		}
		m_data->timeAccumulator += deltaTime.asSeconds();
		if(m_data->timeAccumulator > transitionTime || m_isEnterButtonPressed)
		{
			this->m_data->m_states->addGlobalState(std::make_unique<Engine::imguiUI>(m_data));
		}

		//mouse coords relative to the view
		//std::cout<<m_data->m_window->mapPixelToCoords(sf::Mouse::getPosition(*this->m_data->m_window)).x<<", "<<m_data->m_window->mapPixelToCoords(sf::Mouse::getPosition(*this->m_data->m_window)).y<<"\n";
		//global processes - send off the Input to the input manager to update
		//this->m_data->m_inputs->switchFullScreen(this->m_data->m_isFullScreen);
	}

	void splashState::Draw()
	{
		m_data->m_window->draw(m_background);
		m_data->m_window->draw(m_gameTitle);
		if(m_data->m_isEscButtonPressed) 
		{
			//flag for drawing exit animation
			//m_data->m_window->draw(m_exit);
		}
	}
}
