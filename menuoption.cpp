#include "menuoption.hpp"
#include "main.hpp"

MenuOption::MenuOption(int kind, int price, std::string picString) //Constructor
{
    pic = picString;
    type = kind;
    cost = price;
}

MenuOption::MenuOption(){
    //it yelled at me for not having a default constructor and i don't have wifi to google why
}

MenuOption::~MenuOption() //Destructor
{
    
}

std::string MenuOption::getPic(){
    return pic;
}

int MenuOption::getType(){
    return type;
}

int MenuOption::getCost(){
    return cost;
}