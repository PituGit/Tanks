#include "LTexture.h"
#include "Tile.h"
#include "Tank.h"
#include "Bala.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(Tile* tiles[]);

//Frees media and shuts down SDL
void close(Tile* tiles[]);

//Sets tiles from tile map
bool setTiles(Tile *tiles[]);