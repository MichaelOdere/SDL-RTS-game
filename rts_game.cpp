#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "main.hpp"

int main(int argc, char *argv[])
{
    Main main;

    main.GameLoop(); //starts game

    return 0;
}
