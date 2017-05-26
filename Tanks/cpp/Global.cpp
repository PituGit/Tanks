#include "../h/Global.h"

 SDL_Window* gWindow = NULL;
 SDL_Renderer* gRenderer = NULL;
 
 SDL_Rect gTileClips[TOTAL_TILE_SPRITES] = {};

 SDL_Rect gExplosioClips[TOTAL_SPRITES_EXPLOSIONS] = {};

Mix_Music *gMenuSong = NULL;

Mix_Chunk *gClick = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;