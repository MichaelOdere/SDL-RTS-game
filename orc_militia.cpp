#include "orc_militia.hpp"

OrcMilitia::OrcMilitia(SDL_Setup* passed_SDL_Setup, std::string FilePath, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment) :
Character( passed_SDL_Setup, FilePath, starting_x, starting_y, passed_MouseX, passed_MouseY, passed_environment)
{
    team = 2;
    health = 75;
    max_health = 75;
    attack = 0.015;
    defense = 0.0025;

    type = 2;
}

OrcMilitia::~OrcMilitia()
{
}

void OrcMilitia::Update(){

    Character::Update();

}
