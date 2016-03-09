#include "orc_militia.hpp"

OrcMilitia::OrcMilitia(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment) :
Character( passed_SDL_Setup, passed_image, starting_x, starting_y, passed_MouseX, passed_MouseY, passed_environment)
{
    team = 2;
    health = 75;
    max_health = 75;
    attack = 0.015;
    defense = 0.001;
    environment->addMilitia();

    type = 2;
}

OrcMilitia::~OrcMilitia()
{
}

void OrcMilitia::Update(){

    Character::Update();

    if (health <= 0)
    {
        environment->removeMilitia(); //tell AI militia killed
    }

}
