#include "character_creator.hpp"

CharacterCreator::CharacterCreator(Environment passed_environment)
{
     environment = passed_environment;
}

CharacterCreator::~CharacterCreator()
{

}

void CharacterCreator::CreateCharacter(SDL_Setup* sdl_setup, std::string FilePath, int *MouseX, int *MouseY)
{
     characters.push_back(new Character(sdl_setup, FilePath.c_str(), MouseX, MouseY, environment));
}
