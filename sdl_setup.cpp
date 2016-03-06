#include "sdl_setup.hpp"

SDL_Setup::SDL_Setup(bool* quit) //Constructor
{
    window = NULL;
    window = SDL_CreateWindow("Man vs Orc", 100, 100, 1024, 768, SDL_WINDOW_SHOWN); //Screen size: 1024x768

    if (window == NULL) //error checking
    {
        std::cout << "Window could not be created" << std::endl;
        *quit = true;
    }
    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ev = new SDL_Event();
}

SDL_Setup::~SDL_Setup() //Destructor
{
    //avoids memory leaks
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete ev;
}

SDL_Renderer* SDL_Setup::GetRenderer()
{
    return renderer;
}

SDL_Event* SDL_Setup::GetEv()
{
    return ev;
}

void SDL_Setup::Begin()
{
    SDL_PollEvent(ev);
    SDL_RenderClear(renderer);

}

void SDL_Setup::End()
{
    SDL_RenderPresent(renderer);
}
