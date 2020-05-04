# Simple Box2D and SDL2 wrapper

## Dependencies
* Box2D (Headers already in include/ and static library already in lib/)
* SDL2

## Compile on Linux
* Run `compile.sh` file
* Run `g++  -Iinclude/ -Llib/ main.cpp wrapper.cpp -lbox2d -lSDL2 -lSDL2_image -o main.out -w` command
