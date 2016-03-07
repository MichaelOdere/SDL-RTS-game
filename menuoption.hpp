#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP
#include "imports.hpp"

class MenuOption
{
public:
    MenuOption(int kind, int price, std::string picString, bool button);
    MenuOption();
    ~MenuOption();
    std::string getPic();
    int getType();
    int getCost();
    bool selected;
    bool isButton;

private:
    int type;
    int cost;
    std::string pic;
};


#endif // MENUOPTION_HPP
