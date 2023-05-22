#include "imguiUI.hpp"


void Engine::imguiUI::architectureUI()
{
	//only useful in this scope so static
	static float height;
	ImGui::PushFont(hack_ttf);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

	if(ImGui::Begin("Architecture", nullptr, windowFlags | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::SetWindowPos(ImVec2(dmaUIWidth + 2 * padding, padding + menuBarHeight));

		architectureUIWidth = inputButtonsUIWidth;
		height = this->m_data->size.y - inputButtonsUIHeight - 3 * padding - menuBarHeight;
		ImGui::SetWindowSize(ImVec2(architectureUIWidth, height));

		if(ImGui::BeginChild("Friend"))
		{

			ImGui::SetWindowSize(ImVec2(architectureUIWidth - 2 * padding, height/9));
			ImGui::SetWindowPos(ImVec2(dmaUIWidth + 3 * padding, height + menuBarHeight - height/9 ));

			ImGui::EndChild();
		}

	}

	ImGui::End();
	ImGui::PopStyleColor();  // Restore the previous style			
	ImGui::PopFont();

}
