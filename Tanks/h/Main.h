#include <stdio.h>
#include <fstream>
#include <vector>
#include <math.h>

#include "LTexture.h"
#include "Tile.h"
#include "Tank.h"
#include "Bala.h"

//Màxim de bales
const int N = 20;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(Tile* tiles[]);

//Frees media and shuts down SDL
void close(Tile* tiles[]);


//Sets tiles from tile map
bool setTiles(Tile *tiles[]);

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

LTexture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

LTexture gBaseTankTexture;
LTexture gCapsulaTexture;

LTexture gBalaTexture;