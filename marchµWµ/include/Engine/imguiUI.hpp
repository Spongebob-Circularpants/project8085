#pragma once

#include <SFML/System/Time.hpp>

#include "state.hpp"
#include "application.hpp"
#include "definitions.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include <string>
#include <sstream>
#include <iomanip>

namespace Engine
{
	//wrapper for imgui as a state
	class imguiUI : public Engine::State
	{
	public:
		imguiUI(std::shared_ptr<Engine::applicationData> &data);
		~imguiUI();

		void Init() override;
		void processInput() override;
		void Update(const sf::Time& deltaTime) override;
		void Draw() override;

	private:
		void dmaUI();
		float dmaUIWidth;

		void menuBarUI(); //this is basic for now
		float menuBarHeight;

		void inputButtonsUI();
		float inputButtonsUIWidth, inputButtonsUIHeight;

		void architectureUI();
		float architectureUIWidth;
		
		ImGuiWindowFlags windowFlags;
		ImFont* hack_ttf; 
		ImVec4 hexToRGBA(const std::string& hexColor);
		std::shared_ptr<Engine::applicationData> m_data;
	};
}
