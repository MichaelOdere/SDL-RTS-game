#ifndef BUILDING_HPP_INCLUDED
#define BUILDING_HPP_INCLUDED
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"

class Building
{
    public:
        Building(SDL_Setup* sdl_setup, std::string FilePath, int x, int y);
        ~Building();

        void DrawBuilding();

        int getStructureX();
        int getStructureY();
        int getStructureW();
        int getStructureH();
    
        void Select();

        Sprite* GetBuilding() { return Structure; }
    
        bool selected;

        void setSelected() { selected = true; }
        void unSelect() { selected = false; }

        void Update();

        bool selected;

    private:
        Sprite* Structure;
};

#endif // BUILDING_HPP_INCLUDED
