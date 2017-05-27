#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../SDL_mixer.h"
#include <string>
#include <stdio.h>
#include <iostream> //Temporal
#include <fstream>
#include <vector>
#include <math.h>
#include <Windows.h>
using namespace std;

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

const int EXPLOSIO_WIDTH = 64;
const int EXPLOSIO_HEIGHT = 64;
const int TOTAL_SPRITES_EXPLOSIONS = 16;

const int TEMPS_ENTRE_EXPLOSIONS = 1000;

//The different tile sprites
enum TILE
{
	TILE_FLOOR,
	TILE_GREEN,
	TILE_BLUE,
	TILE_CENTER,
	TILE_TOP,
	TILE_TOPRIGHT,
	TILE_RIGHT,
	TILE_BOTTOMRIGHT,
	TILE_BOTTOM,
	TILE_BOTTOMLEFT,
	TILE_LEFT,
	TILE_TOPLEFT,

};

const int MEITAT_CAPSULA_X = 21;
const int MEITAT_CAPSULA_Y = 23;

const int LONGITUD_TOTAL_DEL_CANO = 53;

const double PI = 3.14159265;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Màxim de bales
const int MAX_BALES = 0;

const Uint32 TIEMPO_DE_VIDA = 1000;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
extern SDL_Rect gExplosioClips[TOTAL_SPRITES_EXPLOSIONS];

extern Mix_Music *gMenuSong;
extern Mix_Music *gInGameSong;

extern Mix_Chunk *gClick;
extern Mix_Chunk *gType;
extern Mix_Chunk *gBackspace;
extern Mix_Chunk *gReturn;
extern Mix_Chunk *gGameOverSound;
extern Mix_Chunk *gExplosion;