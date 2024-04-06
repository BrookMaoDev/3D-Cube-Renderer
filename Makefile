all:
	g++ -Idependencies\include\SDL2 -Ldependencies\lib -o main main.cpp Cube.cpp lin_alg.cpp -lmingw32 -lSDL2main -lSDL2
