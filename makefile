CXX = g++
CXXFLAGS = -Wall -fdiagnostics-color=always -Wextra
OBJECTS = windows_Shell.o ubuntu_Shell.o Shell.o

shell: $(OBJECTS) main.cpp
	$(CXX) $(CXXFLAGS) $(OBJECTS) main.cpp -o main

windows_shell: Shell.h Shell.cpp Shell.o Node.o Hero.o Area.o Item.o
	$(CXX) $(CXXFLAGS) -c windows_Shell.cpp


memory_test:
	valgrind ./main

clean:
	rm *.o
	rm *~

run:
	./main

val1:
	valgrind ./main main_map1.txt main_craft.txt
