#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = -IC:\\mingw_dev_lib\\include\\SDL2
CFLAGS = -Wall -std=c++11
RESINC = 
LIBDIR = -LC:\\mingw_dev_lib\\lib
LIB = 
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_ttf

INC_DEBUG = $(INC) -I..\SDL-RTS-game
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\SDL-RTS-game.exe

INC_RELEASE = $(INC) -I..\SDL-RTS-game
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\SDL-RTS-game.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\menuoption.o $(OBJDIR_DEBUG)\\militia.o $(OBJDIR_DEBUG)\\orc_champion.o $(OBJDIR_DEBUG)\\orc_militia.o $(OBJDIR_DEBUG)\\orc_villager.o $(OBJDIR_DEBUG)\\rts_game.o $(OBJDIR_DEBUG)\\sdl_setup.o $(OBJDIR_DEBUG)\\sprite.o $(OBJDIR_DEBUG)\\submenu.o $(OBJDIR_DEBUG)\\text.o $(OBJDIR_DEBUG)\\villager.o $(OBJDIR_DEBUG)\\TownCenter.o $(OBJDIR_DEBUG)\\ai.o $(OBJDIR_DEBUG)\\barracks.o $(OBJDIR_DEBUG)\\building.o $(OBJDIR_DEBUG)\\champion.o $(OBJDIR_DEBUG)\\character.o $(OBJDIR_DEBUG)\\collision_rectangle.o $(OBJDIR_DEBUG)\\environment.o $(OBJDIR_DEBUG)\\gold.o $(OBJDIR_DEBUG)\\house.o $(OBJDIR_DEBUG)\\main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\menuoption.o $(OBJDIR_RELEASE)\\militia.o $(OBJDIR_RELEASE)\\orc_champion.o $(OBJDIR_RELEASE)\\orc_militia.o $(OBJDIR_RELEASE)\\orc_villager.o $(OBJDIR_RELEASE)\\rts_game.o $(OBJDIR_RELEASE)\\sdl_setup.o $(OBJDIR_RELEASE)\\sprite.o $(OBJDIR_RELEASE)\\submenu.o $(OBJDIR_RELEASE)\\text.o $(OBJDIR_RELEASE)\\villager.o $(OBJDIR_RELEASE)\\TownCenter.o $(OBJDIR_RELEASE)\\ai.o $(OBJDIR_RELEASE)\\barracks.o $(OBJDIR_RELEASE)\\building.o $(OBJDIR_RELEASE)\\champion.o $(OBJDIR_RELEASE)\\character.o $(OBJDIR_RELEASE)\\collision_rectangle.o $(OBJDIR_RELEASE)\\environment.o $(OBJDIR_RELEASE)\\gold.o $(OBJDIR_RELEASE)\\house.o $(OBJDIR_RELEASE)\\main.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG) md $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\menuoption.o: menuoption.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c menuoption.cpp -o $(OBJDIR_DEBUG)\\menuoption.o

$(OBJDIR_DEBUG)\\militia.o: militia.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c militia.cpp -o $(OBJDIR_DEBUG)\\militia.o

$(OBJDIR_DEBUG)\\orc_champion.o: orc_champion.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c orc_champion.cpp -o $(OBJDIR_DEBUG)\\orc_champion.o

$(OBJDIR_DEBUG)\\orc_militia.o: orc_militia.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c orc_militia.cpp -o $(OBJDIR_DEBUG)\\orc_militia.o

$(OBJDIR_DEBUG)\\orc_villager.o: orc_villager.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c orc_villager.cpp -o $(OBJDIR_DEBUG)\\orc_villager.o

$(OBJDIR_DEBUG)\\rts_game.o: rts_game.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c rts_game.cpp -o $(OBJDIR_DEBUG)\\rts_game.o

$(OBJDIR_DEBUG)\\sdl_setup.o: sdl_setup.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c sdl_setup.cpp -o $(OBJDIR_DEBUG)\\sdl_setup.o

$(OBJDIR_DEBUG)\\sprite.o: sprite.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c sprite.cpp -o $(OBJDIR_DEBUG)\\sprite.o

$(OBJDIR_DEBUG)\\submenu.o: submenu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c submenu.cpp -o $(OBJDIR_DEBUG)\\submenu.o

$(OBJDIR_DEBUG)\\text.o: text.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c text.cpp -o $(OBJDIR_DEBUG)\\text.o

$(OBJDIR_DEBUG)\\villager.o: villager.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c villager.cpp -o $(OBJDIR_DEBUG)\\villager.o

$(OBJDIR_DEBUG)\\TownCenter.o: TownCenter.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c TownCenter.cpp -o $(OBJDIR_DEBUG)\\TownCenter.o

$(OBJDIR_DEBUG)\\ai.o: ai.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ai.cpp -o $(OBJDIR_DEBUG)\\ai.o

$(OBJDIR_DEBUG)\\barracks.o: barracks.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c barracks.cpp -o $(OBJDIR_DEBUG)\\barracks.o

$(OBJDIR_DEBUG)\\building.o: building.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c building.cpp -o $(OBJDIR_DEBUG)\\building.o

$(OBJDIR_DEBUG)\\champion.o: champion.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c champion.cpp -o $(OBJDIR_DEBUG)\\champion.o

$(OBJDIR_DEBUG)\\character.o: character.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c character.cpp -o $(OBJDIR_DEBUG)\\character.o

$(OBJDIR_DEBUG)\\collision_rectangle.o: collision_rectangle.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c collision_rectangle.cpp -o $(OBJDIR_DEBUG)\\collision_rectangle.o

$(OBJDIR_DEBUG)\\environment.o: environment.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c environment.cpp -o $(OBJDIR_DEBUG)\\environment.o

$(OBJDIR_DEBUG)\\gold.o: gold.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c gold.cpp -o $(OBJDIR_DEBUG)\\gold.o

$(OBJDIR_DEBUG)\\house.o: house.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c house.cpp -o $(OBJDIR_DEBUG)\\house.o

$(OBJDIR_DEBUG)\\main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)\\main.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE) md $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\menuoption.o: menuoption.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c menuoption.cpp -o $(OBJDIR_RELEASE)\\menuoption.o

$(OBJDIR_RELEASE)\\militia.o: militia.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c militia.cpp -o $(OBJDIR_RELEASE)\\militia.o

$(OBJDIR_RELEASE)\\orc_champion.o: orc_champion.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c orc_champion.cpp -o $(OBJDIR_RELEASE)\\orc_champion.o

$(OBJDIR_RELEASE)\\orc_militia.o: orc_militia.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c orc_militia.cpp -o $(OBJDIR_RELEASE)\\orc_militia.o

$(OBJDIR_RELEASE)\\orc_villager.o: orc_villager.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c orc_villager.cpp -o $(OBJDIR_RELEASE)\\orc_villager.o

$(OBJDIR_RELEASE)\\rts_game.o: rts_game.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c rts_game.cpp -o $(OBJDIR_RELEASE)\\rts_game.o

$(OBJDIR_RELEASE)\\sdl_setup.o: sdl_setup.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c sdl_setup.cpp -o $(OBJDIR_RELEASE)\\sdl_setup.o

$(OBJDIR_RELEASE)\\sprite.o: sprite.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c sprite.cpp -o $(OBJDIR_RELEASE)\\sprite.o

$(OBJDIR_RELEASE)\\submenu.o: submenu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c submenu.cpp -o $(OBJDIR_RELEASE)\\submenu.o

$(OBJDIR_RELEASE)\\text.o: text.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c text.cpp -o $(OBJDIR_RELEASE)\\text.o

$(OBJDIR_RELEASE)\\villager.o: villager.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c villager.cpp -o $(OBJDIR_RELEASE)\\villager.o

$(OBJDIR_RELEASE)\\TownCenter.o: TownCenter.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c TownCenter.cpp -o $(OBJDIR_RELEASE)\\TownCenter.o

$(OBJDIR_RELEASE)\\ai.o: ai.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ai.cpp -o $(OBJDIR_RELEASE)\\ai.o

$(OBJDIR_RELEASE)\\barracks.o: barracks.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c barracks.cpp -o $(OBJDIR_RELEASE)\\barracks.o

$(OBJDIR_RELEASE)\\building.o: building.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c building.cpp -o $(OBJDIR_RELEASE)\\building.o

$(OBJDIR_RELEASE)\\champion.o: champion.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c champion.cpp -o $(OBJDIR_RELEASE)\\champion.o

$(OBJDIR_RELEASE)\\character.o: character.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c character.cpp -o $(OBJDIR_RELEASE)\\character.o

$(OBJDIR_RELEASE)\\collision_rectangle.o: collision_rectangle.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c collision_rectangle.cpp -o $(OBJDIR_RELEASE)\\collision_rectangle.o

$(OBJDIR_RELEASE)\\environment.o: environment.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c environment.cpp -o $(OBJDIR_RELEASE)\\environment.o

$(OBJDIR_RELEASE)\\gold.o: gold.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c gold.cpp -o $(OBJDIR_RELEASE)\\gold.o

$(OBJDIR_RELEASE)\\house.o: house.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c house.cpp -o $(OBJDIR_RELEASE)\\house.o

$(OBJDIR_RELEASE)\\main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)\\main.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

