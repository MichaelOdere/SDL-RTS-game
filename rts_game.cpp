#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "imports.hpp"
#include "main.hpp"

int main(int argc, char *argv[])
{
    Main main;

    main.GameLoop(); //starts game

    return 0;
}
