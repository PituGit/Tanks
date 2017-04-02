#include "../h/IA.h"

Punt::Punt()
{
	nou = true;
}

void Punt::setPunt(int i, int j)
{
	punt.x = i;
	punt.y = j;
}

bool Punt::getNou()
{
	return nou;
}

void Punt::setNou()
{
	nou = false;
}

Cami::Cami()
{
	cost = 0;

	costTotal = 0;

	distancia = 0;

}

double Cami::getDistancia()
{
	return distancia;
}

int Cami::getCost()
{
	return cost;
}

double Cami::getCostTotal()
{
	return costTotal;
}

SDL_Point Cami::getRecorregut()
{
	return recorregut[recorregut.size() - 1];
}

void Cami::setDistancia(SDL_Point actual,SDL_Point objectiu)
{
	distancia = CalculaDistancia(actual, objectiu);
}

void Cami::setRecorregut(int x, int y)
{
	recorregut.push_back(SDL_Point());
	recorregut[cost].x = x;
	recorregut[cost].y = y;
}

void Cami::setCost()
{
	cost++;
}

void Cami::setCostTotal()
{
	costTotal = sqrt(pow(distancia, 2) + pow(cost, 2));
}

double CalculaDistancia(SDL_Point actual, SDL_Point objectiu)
{
	return (sqrt(pow(actual.x - objectiu.x, 2) + pow(actual.y - objectiu.y, 2)));
}

int BuscaCami(std::vector <Cami> camins)
{
	int comptador = 1;

	//Variable que contindrà el valor de la posicio del cami més òptim
	int variable = 0;

	while (comptador < camins.size())
	{
		if (camins[variable].getCostTotal() > camins[comptador].getCostTotal())
		{
			variable = comptador;
		}

		comptador++;
	}

	return variable;
}


void GeneraCami(TankDolent tankdolent, TankJugador tank, Tile * tiles[])
{
	//Conjunt de tots els camins possibles
	std::vector <Cami> camins(0);


	int comptador = 0, comptador2 = 0;

	//Variable que ens indica si hem trobat el final
	bool trobat = false;

	//Conjut de punts que configuren tot el mapa
	Punt punts[MAX_X][MAX_Y];

	//Punt que estarem analitzant 
	SDL_Point actual;
	actual.x = tankdolent.getTankBox().x;
	actual.y = tankdolent.getTankBox().y;

	SDL_Rect actual_Box;
	actual_Box.x = actual.x;
	actual_Box.y = actual.y;
	actual_Box.w = 1;
	actual_Box.h = 1;


	//Punt objectiu en el que volem anar
	SDL_Point objectiu;
	objectiu.x = tank.getTankBox().x;
	objectiu.y = tank.getTankBox().y;

	//Comencem el recorregut en el punt del tank
	camins[0].setRecorregut(actual.x, actual.y);

	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			punts[i][j].setPunt(i, j);
		}
	}


	while(!trobat)
	{
		//Generador de camins nous possibles
		while (comptador < CAMINS_NOUS)
		{
			if (comptador == 0 && punts[actual.x - 1][actual.y].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x - 1][actual.y].setNou();
				camins.push_back(Cami());
				camins[camins.size()-1].setCost();
				camins[camins.size()-1].setRecorregut(actual.x - 1, actual.y);
				actual.x--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.x++;
				camins[camins.size() - 1].setCostTotal();
			}
			else if (comptador == 1 && punts[actual.x - 1][actual.y - 1].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x - 1][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x - 1, actual.y - 1);
				actual.x--;
				actual.y--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.x++;
				actual.y++;
				camins[camins.size() - 1].setCostTotal();
			}
			else if (comptador == 2 && punts[actual.x][actual.y - 1].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x, actual.y - 1);
				actual.y--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.y++;
				camins[camins.size() - 1].setCostTotal();
			}
			else if (comptador == 3 && punts[actual.x + 1][actual.y - 1].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x + 1][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y - 1);
				actual.y--;
				actual.x++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.y++;
				actual.x--;
				camins[camins.size() - 1].setCostTotal();
			}
			else if (comptador == 4 && punts[actual.x + 1][actual.y].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x + 1][actual.y].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y);
				actual.x++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.x--;
				camins[camins.size() - 1].setCostTotal();
			}
			else if (comptador == 5 && punts[actual.x + 1][actual.y + 1].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x + 1][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y + 1);
				actual.x++;
				actual.y++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.x--;
				actual.y--;
				camins[camins.size() - 1].setCostTotal();
			}
			else if (comptador == 6 && punts[actual.x][actual.y + 1].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x, actual.y + 1);
				actual.y++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.y--;
				camins[camins.size() - 1].setCostTotal();
			}
			else if (comptador == 7 && punts[actual.x - 1][actual.y + 1].getNou() && !touchesWall(actual_Box, tiles))
			{
				punts[actual.x - 1][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x - 1, actual.y + 1);
				actual.y++;
				actual.x--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				actual.x++;
				actual.y--;
				camins[camins.size() - 1].setCostTotal();
			}

			comptador++;
		}

		//Variable que indica quina es la posicio del cami més òptim actualment
		int variable = BuscaCami(camins);

		actual = camins[variable].getRecorregut();
		actual_Box.x = actual.x;
		actual_Box.y = actual.y;
		

	}
}


bool esVeuen(TankDolent tankdolent, TankJugador tank, Tile * tiles[])
{
	SDL_Rect CapsulaDolent = tankdolent.getTankBox();
	SDL_Rect CapsulaJugador = tank.getTankBox();

	bool esVeuen = false;

	//Capsula que encercla la posicio del jugador
	SDL_Rect Caixa;
	Caixa.w = CapsulaJugador.w + 5;
	Caixa.h = CapsulaJugador.h + 5;
	Caixa.x = CapsulaJugador.x;

	double angle = 0;

	
	if ((CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X) != 0)
		angle = atan((double(CapsulaJugador.y - CapsulaDolent.y - MEITAT_CAPSULA_Y)) / double(CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X));
		angle *= 57.3;
		if ((CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X) < 0)
		angle += 180;

	while (move(CapsulaDolent, angle, tiles))
	{

	}

	return esVeuen;
}


bool move(SDL_Rect &CapsulaDolent, double angle, Tile * tiles[])
{
	bool continuar = true;

	//Moure la capsula cap al tank del jugador
	CapsulaDolent.x = cos(angle);
	CapsulaDolent.y = sin(angle);

	if (touchesWall(CapsulaDolent, tiles))
		continuar = false;
	return continuar;
}
