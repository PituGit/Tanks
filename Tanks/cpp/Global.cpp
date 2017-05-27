#include "../h/Global.h"

 SDL_Window* gWindow = NULL;
 SDL_Renderer* gRenderer = NULL;
 
 SDL_Rect gTileClips[TOTAL_TILE_SPRITES] = {};

 SDL_Rect gExplosioClips[TOTAL_SPRITES_EXPLOSIONS] = {};

Mix_Music *gMenuSong = NULL;
Mix_Music *gInGameSong = NULL;

Mix_Chunk *gClick = NULL;
Mix_Chunk *gType = NULL;
Mix_Chunk *gBackspace = NULL;
Mix_Chunk *gReturn = NULL;
Mix_Chunk *gGameOverSound = NULL;
Mix_Chunk *gExplosion = NULL;