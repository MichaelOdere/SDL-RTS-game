#ifndef CHARACTER_CREATOR_HPP_INCLUDED
#define CHARACTER_CREATOR_HPP_INCLUDED
#include "imports.hpp"
#include "environment.hpp"
#include "character.hpp"
#include "sdl_setup.hpp"

class CharacterCreator
{
    public:
        CharacterCreator(Environment passed_environment);
        ~CharacterCreator();

        void CreateCharacter(SDL_Setup* sdl_setup, std::string FilePath, int *MouseX, int *MouseY);


    private:

        Environment environment;
        std::vector<Character*> characters;
};

#endif // CHARACTER_CREATOR_HPP_INCLUDED
