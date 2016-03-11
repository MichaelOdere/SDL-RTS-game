#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "imports.hpp"
#include <vector>
#include <list>
#include "sprite.hpp"
#include "sdl_setup.hpp"
#include "gold.hpp"
#include "building.hpp"
#include "submenu.hpp"
#include "collision_rectangle.hpp"
#include "ai.hpp"
#include <math.h>
#include "text.hpp"
#include "main.hpp"

class Character; //avoids error because Environment includes Character and vice versa
class Building;
class AI;
class Main;

class Environment
{
    public:
        Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, SubMenu* passed_menu, AI* passed_ai, Main* passed_main);
        ~Environment();

        void DrawBack();
        void Update();
        int getMenuType();
        void updateWhatToMake(int what);
        void updateCost(int n);
        bool shouldMenu();
        std::vector<Building*> getBuildings() { return buildings; }
        std::vector<Gold*> getGoldMines() { return goldMines; }
        std::list<Character*> getCharacters() { return characters; }
        void AddResources(int i);
        void PrintResources() { std::cout << resources << std::endl; } //prints to command line, for testing only
        Character* Combat(Sprite* attacker, int attacker_team);
        Building* CombatBuilding(Sprite* attacker, int attacker_team);
        void KillCharacter(Sprite* passed_dead);
        Character* FindTarget(int x, int y);
        float resources;
        float orcResources;
        Character* selectedCharacter;
        Building* selectedBuilding;
        Gold* selectedGold;
        bool buildingConstructionCollision(int x, int y);
        void decreasePop(int team);
        void increasePop(int team);
        int getOrcPop() { return orcPop; }
        int getOrcMaxPop() { return orcMaxPop; }
        int getOrcResources() { return orcResources; }
        void notBuildingHouse();
        void notBuildingBarracks();
        void addVillager();
        void addMilitia();
        void addChampion();
        void removeVillager();
        void removeMilitia();
        void removeChampion();
        void goldMineDepleted(int gold_x, int gold_y);
        void buildingNotConstructing(int structure_x, int structure_y);
        void removeCharacter(int team);
        void inEnemyTerritory(Character* enemy);
        void createHouse(int x, int y);
        void createBarracks(int x, int y);
        void barracksDestroyed();
        void setOrcResources(int passed_orcResources) {orcResources = passed_orcResources; }
        void createVillager(Building* passed_building, int unit);
        void createMilitia(Building* passed_building, int unit);
        void createChampion(Building* passed_building, int unit);
        void alertInsufficientFunds();
        void alertNoHousing();
        void alertCreating();
        void changeImage(Sprite* building, int type);
        void setCollisionImage(Sprite* building);
        std::string timeHandler(int time);
        void displayHealthBar(Sprite* item, float health_percent);
        void endGame(int loser);

    private:

        SubMenu* optionsMenu;
        CollisionRectangle collision_rect;
        int *MouseX;
        int *MouseY;
        int menuType;
        int whatToMake;
        bool showMenu;
        bool broke;
        bool overpopulated;
        bool alreadyCreating;
        int startTime;
        int brokeTime;
        int brokeCost;
        int humanPop;
        int orcPop;
        int humanMaxPop;
        int orcMaxPop;
        int maxMaxPop;
        int team;
        TextMessage* goldText;
        TextMessage* populationText;
        TextMessage* timeText;
        TextMessage* insufficientFunds;
        TextMessage* noHousing;
        TextMessage* busyBuilding;
        Character* dead;
        SDL_Setup* sdl_setup;
        std::vector<Gold*> goldMines;
        std::vector<Building*> buildings;
        std::list<Character*> characters;
        AI* ai;
        Main* main;
        SDL_Texture* collisionImage20;
        SDL_Texture* collisionImage19;
        SDL_Texture* collisionImage18;
        SDL_Texture* collisionImage17;
        SDL_Texture* collisionImage16;
        SDL_Texture* collisionImage15;
        SDL_Texture* collisionImage14;
        SDL_Texture* collisionImage13;
        SDL_Texture* collisionImage12;
        SDL_Texture* collisionImage11;
        SDL_Texture* collisionImage10;
        SDL_Texture* collisionImage9;
        SDL_Texture* collisionImage8;
        SDL_Texture* collisionImage7;
        SDL_Texture* collisionImage6;
        SDL_Texture* collisionImage5;
        SDL_Texture* collisionImage4;
        SDL_Texture* collisionImage3;
        SDL_Texture* collisionImage2;
        SDL_Texture* collisionImage1;
        SDL_Texture* villagerImage;
        SDL_Texture* militiaImage;
        SDL_Texture* championImage;
        SDL_Texture* orcVillagerImage;
        SDL_Texture* orcMilitiaImage;
        SDL_Texture* orcChampionImage;
        SDL_Texture* houseImage;
        SDL_Texture* barracksImage;
        SDL_Texture* barracksImage1;
        SDL_Texture* townCenterImage;
        SDL_Texture* goldImage;
        SDL_Texture* constructionImage;
};

#endif // ENVIRONMENT_HPP
