all: build

build:
	g++ -c program/*.cpp -Iinclude && mv *.o compile
	g++ ./compile/*.o -Wall -I./include -L./lib main.cpp -o main -lraylib -lopengl32 -lgdi32 -lwinmm
	main.exe

clean:
	rm *.exe
	rm ./compile/*.o

ejecutar:
	main.exe