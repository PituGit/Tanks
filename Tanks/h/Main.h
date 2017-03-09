#include "LTexture.h"
#include "Tile.h"
#include "Tank.h"
#include "Bala.h"

int joc(int vides);


//Loads media
bool loadMedia(Tile* tiles[]);

//Frees media and shuts down SDL
void close(Tile* tiles[]);

//Sets tiles from tile map
bool setTiles(Tile *tiles[]);