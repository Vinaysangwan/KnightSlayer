compile: build run

build:
	gcc $(wildcard ./src/*.c) -o ./out/sdl_game.exe -lSDL3

run:
	./out/sdl_game.exe