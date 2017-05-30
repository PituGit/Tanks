#include "Bala.h"


bool esVeuen(TankDolent &tankdolent, TankJugador tank, Tile * tiles[]);

bool move(SDL_Rect &CapsulaDolent, double angle, Tile * tiles[]);

void disparar(TankDolent &tankdolent, TankJugador tank, vector <Bala> &pBala, int* cBales, Tile * tiles[]);

const int MAX_X = 1280;
const int MAX_Y = 960;

void moveTankEnemic(TankDolent tankdolent, TankJugador tank, Tile * tiles[]);

void moveTankRandom(TankDolent &tankdolent, Tile * tiles[], Uint32 &tempsmoviment);

