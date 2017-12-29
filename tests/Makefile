CC=g++
CXXFLAGS=-c -std=c++11 -Wall
INC=  -I../include
SOURCES=main.cpp ../src/later_async_call.cpp ../src/lift_cabine.cpp ../src/open_door_strategy.cpp ../src/close_door_strategy.cpp ../src/lift_move_strategy.cpp ../src/lift_message.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tests_lift

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS)  -o $@ -pthread -lgmock -lgmock_main
.cpp.o:
	$(CC) $(CXXFLAGS) $< -o $@ $(INC)
clean:
	rm -rf *.o tests_lift
