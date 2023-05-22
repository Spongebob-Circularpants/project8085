#include "imguiUI.hpp"

void Engine::imguiUI::inputButtonsUI()
{
	const unsigned numButtonsH = 5, numButtonsV = 4;
	const char *buttonNames[numButtonsH * numButtonsV] =
	{
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"A", 
		"B",
		"C",
		"D",
		"E",
		"F",

		"Insert",
		"RUN",
		"--Address",
		"TRAP",
	};


	if(ImGui::Begin("inputButtons", nullptr, windowFlags | ImGuiWindowFlags_NoTitleBar))
	{
		inputButtonsUIHeight = this->m_data->size.y/2;
		inputButtonsUIWidth = this->m_data->size.x - dmaUIWidth * 2 - padding * 4;
		ImGui::SetWindowSize(ImVec2(inputButtonsUIWidth, inputButtonsUIHeight));
		ImGui::SetWindowPos(ImVec2(dmaUIWidth + 2 * padding, this->m_data->size.y - inputButtonsUIHeight - padding));


		// Calculate the size of the button relative to the window size
		ImVec2 buttonSize(inputButtonsUIWidth * 0.24f,  inputButtonsUIHeight* 0.18f);

		/* doesn't work, fix
		// Dynamic button size on the basis of hover
		if (ImGui::IsItemHovered())
		{
			// Change the button size when hovered
			buttonSize.x *= 1.5f;
			buttonSize.y *= 1.5f;
		}
		*/

		// Begin the buttons
		for(unsigned i = 0; i<numButtonsH; i++)
		{

			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
			for(unsigned j = 0; j<numButtonsV; j++)
			{
				if(j > 0) ImGui::SameLine();
				unsigned activeIndex = i * numButtonsV + j;

				if(ImGui::Button(buttonNames[activeIndex], buttonSize))
				{
					//do stuff
				}
				
			}
			ImGui::PopStyleColor(3);
		}

	}
	ImGui::End();

}
