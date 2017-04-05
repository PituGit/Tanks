#include "IA.h"

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

void GestionaColisio(std::vector <TankDolent> &tankdolent, TankJugador tank, int &cBalesE, int &cBalesJ, int &cTanks,
	std::vector <Bala> &balesenemigues, std::vector <Bala> &balajugador, bool &primercop, SDL_Point Lloc_Explosio,
	int &frame, bool &colisio, bool &colisio2);