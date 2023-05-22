#include "imguiUI.hpp"

namespace Engine
{
	imguiUI::imguiUI(std::shared_ptr<applicationData> &data)
	:
		m_data(data)
	{
	}

	imguiUI::~imguiUI()
	{
		ImGui::SFML::Shutdown();
	}

	void imguiUI::Init()
	{
		if(!ImGui::SFML::Init(*(m_data->m_window)))
		{
			this->m_data->m_muController->m_output->consoleWrite("ImGui done goofed up\n");
			exit(-1);
		}

		//Font Configs
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* fontAtlas = io.Fonts;
		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = false;  // Ensure font data is not deleted by ImFontAtlas
		fontConfig.PixelSnapH = true;             // Enable pixel snapping for sharper text rendering

		//load font
		hack_ttf = fontAtlas->AddFontFromFileTTF(hack_ttfPATH, fontSize, &fontConfig);
		fontAtlas->AddFontFromFileTTF(arialPATH, fontSize, &fontConfig);
		io.FontDefault = fontAtlas->Fonts.back(); 
		// Set the custom font as the default font
		if (!io.Fonts->IsBuilt()) {
    			if(!ImGui::SFML::UpdateFontTexture())
			{
				this->m_data->m_muController->m_output->consoleWrite("ImGui done goofed up\n");
			}
		}

		//colors
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); 
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); 
		colors[ImGuiCol_Text] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); 
		colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_Border] = hexToRGBA("0x7f11e0");//externally sourced colors that I can't be bothered to calculate the values for so I wrote a function to convert hex to ImVec4
		colors[ImGuiCol_WindowBg] =ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_MenuBarBg] =ImVec4(0.0f, 0.0f, 0.0f, 1.0f);


		//window styles; 
		ImGuiStyle& style = ImGui::GetStyle();
    		style.WindowPadding = ImVec2(10.0f, 17.0f);
    		style.FramePadding = ImVec2(10.0f, 3.0f);
    		style.CellPadding = ImVec2(10.0f, 2.0f);
    		style.ItemSpacing = ImVec2(19.0f, 4.0f);
    		style.WindowRounding = 12.0f;
    		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    		style.AntiAliasedLines = false;

		//any window with other than these features make no sense here
    		windowFlags = ImGuiWindowFlags_NoResize | 
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoScrollbar;

		//transitioning purposes; everything here is for a reason
		//and that reason was found using my lifespan as a medium
		//of currency
		ImGui::SFML::ProcessEvent(this->m_data->m_inputs->m_event);
		ImGui::SFML::Update(*(this->m_data->m_window), this->m_data->m_clock.getElapsedTime());
	}

	void imguiUI::processInput()
	{
		ImGui::SFML::ProcessEvent(this->m_data->m_inputs->m_event);

		//for SFML window
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
            //move and click; not click and move
            if(this->m_data->m_inputs->m_event.type == sf::Event::MouseMoved)
		{
			this->m_data->mousePosition.x = this->m_data->m_inputs->m_event.mouseMove.x;
			this->m_data->mousePosition.y = this->m_data->m_inputs->m_event.mouseMove.y;
		}

	}
	
	void imguiUI::Update(const sf::Time& deltaTime)
	{
		//global SFML window updates;
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
		
		//ImGui's stuff
		//all immediate mode stuff and their consequences are updated here
		//just list them as you please
		ImGui::SFML::Update(*(this->m_data->m_window), deltaTime);
		menuBarUI();
		dmaUI();
		inputButtonsUI();
		architectureUI();
		ImGui::ShowDemoWindow();
	}

	void imguiUI::Draw()
	{
		if(m_data->m_isEscButtonPressed) 
		{
			//flag for drawing exit animation on here
			//m_data->m_window->draw(m_exit);
		}

		ImGui::SFML::Render(*(this->m_data->m_window));
	}

	//utils
	ImVec4 imguiUI::hexToRGBA(const std::string& hexColor)
	{
		std::string colorString = hexColor;
		if (colorString[0] == '#')
			colorString = colorString.substr(1); // Remove leading '#'
		else if (colorString[1] == 'x' || colorString[1] == 'X')
			colorString = colorString.substr(2);

		// Convert hex color to decimal values
		unsigned int decimalColor = 0;
		std::stringstream ss;
		ss << std::hex << colorString;
		ss >> decimalColor;

		// Extract individual color components (R, G, B)
		float r = (decimalColor >> 16 & 0xFF) / 255.0f;
		float g = (decimalColor >> 8 & 0xFF) / 255.0f;
		float b = (decimalColor & 0xFF) / 255.0f;

		// Set alpha value (change as desired or default to 1.0 for full opacity)
		float a = 1.0f;

		// Create ImVec4 color object
		ImVec4 imguiColor(r, g, b, a);
		return imguiColor;
	}
}
