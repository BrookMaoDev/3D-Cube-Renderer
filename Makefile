all:
	g++ -Idependencies\include\SDL2 -Ldependencies\lib -o main main.cpp Cube.cpp -lmingw32 -lSDL2main -lSDL2
