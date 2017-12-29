CC=g++
CXXFLAGS=-c -std=c++11 -Wall
INC=  -I./include
SOURCES=./src/main.cpp ./src/later_async_call.cpp ./src/open_door_strategy.cpp ./src/close_door_strategy.cpp ./src/lift_move_strategy.cpp ./src/lift_message.cpp ./src/lift_cabine.cpp ./src/lift_listener.cpp ./src/lift_logic.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lift_emulator

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ -pthread
.cpp.o:
	$(CC) $(CXXFLAGS) $< -o $@ $(INC)
clean:
	rm -rf ./src/*.o lift_emulator
