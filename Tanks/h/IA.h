#include "Tank.h"

bool esVeuen(TankDolent tankdolent, TankJugador tank, Tile * tiles[]);

bool move(SDL_Rect &CapsulaDolent, double angle, Tile * tiles[]);

void GeneraCami(TankDolent tankdolent, TankJugador tank, Tile * tiles[]);

int BuscaCami(std::vector <Cami> camins);

double CalculaDistancia(SDL_Point actual, SDL_Point objectiu);

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

	SDL_Point getRecorregut();

	void setDistancia(SDL_Point actual, SDL_Point objectiu);

	void setRecorregut(int x, int y);

	void setCost();

	void setCostTotal();

private:
	int cost;

	double distancia;

	double costTotal;

	std::vector <SDL_Point> recorregut;

};