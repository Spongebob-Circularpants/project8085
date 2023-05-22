#include "imguiUI.hpp"

void Engine::imguiUI::dmaUI()
{

	ImGui::PushFont(hack_ttf);
	const static int totalMemory = 65536;
	static int startingAddress = 0;
	static int finalAddress = 0;
	static int usableRows = 0;
	static char inputText[5] = "";
	static bool hover;

	ImGui::Begin("Direct Memory Access", nullptr, windowFlags);
	ImGui::SetWindowPos(ImVec2(padding, padding + menuBarHeight));

	dmaUIWidth = m_data->size.x / 6;
	ImGui::SetWindowSize(ImVec2(dmaUIWidth, m_data->size.y - 2 * padding - menuBarHeight));

	// Begin the table
	ImGui::BeginTable("MemoryTable", 2, 
			ImGuiTableFlags_SizingStretchProp |
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_BordersOuterH |
			ImGuiTableFlags_BordersV |
			ImGuiTableFlags_BordersOuter);

	hover = 0;
	if (ImGui::IsItemHovered()) hover = 1;

	// Table header
	ImGui::TableSetupColumn("Address");
	ImGui::TableSetupColumn("Memory");
	ImGui::TableHeadersRow();

	usableRows = (ImGui::GetContentRegionAvail().y / (ImGui::GetTextLineHeightWithSpacing() + 4));
	finalAddress = startingAddress + usableRows;
	if(finalAddress>totalMemory) 
	{
		startingAddress = totalMemory - usableRows;
		finalAddress = totalMemory;
	}
	static char dmaUIData[55][3];
	//55 here is after observing it's the max number of rows
	//that's rendered. Of course when you change the font, this
	//number is going to change but since it can't be both static
	//and dynamic, this is the result 

	// Table content (65536 rows) not really; teehee
	for (int row = startingAddress; row < finalAddress; ++row)
	{
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("\t%#06X\t", row);

		ImGui::TableSetColumnIndex(1);
		unsigned activeIndex = row - startingAddress;
		std::snprintf(dmaUIData[activeIndex], sizeof(dmaUIData[activeIndex]), "%x", this->m_data->m_muController->m_ram->dmaOutput(row));

		// Calculate cell width and height
		float cellWidth = ImGui::GetContentRegionAvail().x / 2.0f;
		float cellHeight = ImGui::GetTextLineHeight();

		// Calculate position to center the input text
		ImVec2 startPos = ImGui::GetCursorScreenPos();
		startPos.x += (cellWidth - ImGui::CalcTextSize(dmaUIData[activeIndex]).x) * 0.5f  + 25;
		startPos.y += (cellHeight - ImGui::GetTextLineHeightWithSpacing()) * 0.5f;

		// Center-align the input text
		ImGui::SetCursorScreenPos(startPos);

		ImGui::PushID(activeIndex);
		//if data cell was modified, relay that to the ram
		if (ImGui::InputText("##data_cell",
					dmaUIData[activeIndex],
					sizeof(dmaUIData[0]),
					ImGuiInputTextFlags_CharsHexadecimal))
		{
			if(!strlen(dmaUIData[activeIndex]))
			{
				strcpy(dmaUIData[activeIndex], "00\0");
			}
			this->m_data->m_muController->m_ram->dmaInput(row, std::stoi(dmaUIData[activeIndex], 0, 16));
		}
		ImGui::PopID();

		if (ImGui::IsItemHovered()) hover = 1;

	}
	// End the table
	ImGui::EndTable();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3.0f, 4.0f));

	// Small UI for user input of startingAddress
	ImGui::Text("Address :");
	ImGui::SameLine();
	//Input field for hex
	//Try buffer overflowing this, sajen
	if (ImGui::InputText("##InputField", 
				inputText, 
				sizeof(inputText), 
				ImGuiInputTextFlags_CharsHexadecimal))
	{
		if(!strlen(inputText))
		{
			startingAddress = 0;
		}
		else 
		{
			startingAddress = std::stoi(inputText, 0, 16);
			if(startingAddress<0) { startingAddress = 0; }
		}
	}
	if (ImGui::IsItemHovered()) hover = 1;

	if(hover)
	{
		// Handle arrow key events
		if (ImGui::IsKeyPressed(ImGuiKey_DownArrow) || ImGui::IsKeyPressed(ImGuiKey_J))
		{
			startingAddress++; // Increase the number on Up arrow key press
		}
		else if ( (ImGui::IsKeyPressed(ImGuiKey_UpArrow) || ImGui::IsKeyPressed(ImGuiKey_K) ) && startingAddress)
		{
			startingAddress--; // Decrease the number on Down arrow key press
		}
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::End();
	ImGui::PopFont();
}

