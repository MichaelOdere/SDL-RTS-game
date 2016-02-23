
#ifndef MENUOPTION_HPP_INCLUDED
#define MENUOPTION_HPP_INCLUDED
#include "imports.hpp"

class MenuOption
{
public:
    MenuOption(int kind, int price, std::string picString);
    MenuOption();
    ~MenuOption();

    std::string getPic();
    int getType();
    int getCost();
    
    bool selected;

private:

    int type;
    int cost;

    std::string pic;


};


#endif 
