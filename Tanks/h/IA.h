#include "Tank.h"


bool esVeuen(TankDolent tankdolent, TankJugador tank, Tile * tiles[]);

bool move(SDL_Rect &CapsulaDolent, double angle, Tile * tiles[]);

void GeneraCami(TankDolent tankdolent, TankJugador tank, Tile* tiles[]);

const int MAX_X = 5000;

class Punt
{
public:

	Punt();

private:
	bool nou;
};

class Cami
{
public: 

	Cami();


private:
	int cost;
	
	int distancia;

	Punt Pos[MAX_X][MAX_X];

};

