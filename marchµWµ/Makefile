CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -O3

BIN		:= bin
SRC 		:= src
E_SRC 	:= src/Engine
M_SRC 	:= src/microcontroller

INCLUDE	:= include
E_INCLUDE 	:= include/Engine
M_INCLUDE 	:= include/microcontroller

IMGUI_DIR 	:= lib/imgui
LIB		:= 

LIBRARIES	:= -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lGL
EXECUTABLE	:= march 


run: $(BIN)/$(EXECUTABLE)
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(E_SRC)/*.cpp $(E_SRC)/managers/*.cpp $(E_SRC)/states/*.cpp $(E_SRC)/states/imguiUI/*.cpp $(M_SRC)/memory/*.cpp  $(M_SRC)/IO/*.cpp $(IMGUI_DIR)/*.cpp $(IMGUI_DIR)/backends/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(E_INCLUDE) -I$(M_INCLUDE) -I$(M_INCLUDE)/bus -I$(M_INCLUDE)/memory -I$(M_INCLUDE)/IO -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends $^ -o $@ $(LIBRARIES)
