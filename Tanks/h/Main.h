#include "LTexture.h"
#include "Tile.h"
#include "Bala.h"

bool joc();


//Loads media
bool loadMedia(Tile* tiles[]);

//Frees media and shuts down SDL
void close(Tile* tiles[]);

//Sets tiles from tile map
bool setTiles(Tile *tiles[]);

//Retallar la tile d'explosions i imprimirles
void renderExplosio(int x, int y, int imatge);

int setTanks(std::vector <int> &ID, std::vector <int> &x, std::vector <int> &y);