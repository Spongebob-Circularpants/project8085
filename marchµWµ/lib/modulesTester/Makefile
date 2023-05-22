CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++11 -Wformat

#release
#CXX_FLAGS := -O3 -Wall -Wextra -std=c++11 -Wformat

BIN		:= bin
SRC 		:= src
IMGUI_DIR 	:= imgui
INCLUDE	:= include
LIB		:= 

LIBRARIES	:= -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lGL
EXECUTABLE	:= main 


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)


$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(IMGUI_DIR)/*.cpp $(IMGUI_DIR)/backends/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
