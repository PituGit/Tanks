#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <math.h>

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

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

const double PI = 3.14159265;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Màxim de bales
const int MAX_BALES = 1;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern SDL_Rect gTileClips[TOTAL_TILE_SPRITES];