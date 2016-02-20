#include "main.hpp"
#include <math.h>

Main::Main() //Constructor
{

    quit = false; //boolean for game loop
    sdl_setup = new SDL_Setup(&quit);

    MouseX = 0;
    MouseY = 0;

    gameMap = new Environment(sdl_setup, &MouseX, &MouseY);

    optionsMenu = new SubMenu(sdl_setup, &MouseX, &MouseY,0);

    showMenu = false;

}

Main::~Main() //Destructor
{
    //avoids memory leaks
    delete sdl_setup;
    delete gameMap;
    delete optionsMenu;
}

void Main::GameLoop()
{
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        SDL_GetMouseState(&MouseX, &MouseY); //sets x and y of mouse location for each loop

        gameMap->DrawBack();

        gameMap->Update(optionsMenu->getWhatToMake());
        menuType = gameMap->getMenuType();
        showMenu = gameMap->shouldMenu();

        if(showMenu){
            optionsMenu->Draw();
        }
        optionsMenu->UpdateType(menuType);
        optionsMenu->Update();

        sdl_setup->End();
    }
}
