#ifndef SDL_SETUP_HPP
#define SDL_SETUP_HPP

#include "imports.hpp"

class SDL_Setup
{
public:
    SDL_Setup(bool* quit);
    ~SDL_Setup();

    SDL_Renderer* GetRenderer();
    SDL_Event* GetEv();

    void Begin();
    void End();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* ev;
};


#endif // SDL_SETUP_HPP
