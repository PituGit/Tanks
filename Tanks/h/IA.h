#include "Tank.h"
#include "Bala.h"

bool esVeuen(TankDolent tankdolent, TankJugador tank, Tile * tiles[]);

bool move(SDL_Rect CapsulaDolent, double angle, Tile * tiles[]);

void GeneraCami(TankDolent tankdolent, TankJugador tank, Tile * tiles[]);

void disparar(TankDolent tankdolent, TankJugador tank, vector <Bala>* pBala, int* cBales, Tile * tiles[]);

const int MAX_X = 1280;
const int MAX_Y = 960;

const int CAMINS_NOUS = 8;

class Punt
{
public:
	Punt();

	void setPunt(int i, int j);

	bool getNou();

	void setNou();
	
private:
	bool nou;

	SDL_Point punt;
};

class Cami
{
public:
	Cami();

	double getDistancia();

	double getCostTotal();

	int getCost();

	void setDistancia(TankDolent tankdolent, TankJugador tank);

	void setRecorregut(int x, int y);

	void setCost();

private:
	int cost;

	double distancia;

	double costTotal;

	std::vector <SDL_Point> recorregut;

};