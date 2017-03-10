#include "LTexture.h"
#include "Tile.h"
#include "Tank.h"
#include "Bala.h"

bool joc();


//Loads media
bool loadMedia(Tile* tiles[]);

//Frees media and shuts down SDL
void close(Tile* tiles[]);

//Sets tiles from tile map
bool setTiles(Tile *tiles[]);

//Retallar la tile d'explosions i imprimirles
void setExplosions(int x, int y);
void renderExplosio(int x, int y, SDL_Rect Caixa_Explosions);