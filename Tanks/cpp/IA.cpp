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

void Cami::setDistancia(TankDolent tankdolent, TankJugador tank)
{
	distancia = sqrt(pow(tankdolent.getTankBox().x - tank.getTankBox().x, 2) + pow(tankdolent.getTankBox().y
		- tank.getTankBox().y, 2));
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


void GeneraCami(TankDolent tankdolent, TankJugador tank, Tile * tiles[])
{
	//Conjunt de tots els camins possibles
	std::vector <Cami> camins(0);


	int comptador = 0;

	//Variable que ens indica si hem trobat el final
	bool trobat = false;

	//Conjut de punts que configuren tot el mapa
	Punt punts[MAX_X][MAX_Y];

	//Punt que estarem analitzant 
	SDL_Point actual;
	actual.x = tankdolent.getTankBox().x;
	actual.y = tankdolent.getTankBox().y;

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
			if (comptador == 0 && punts[actual.x - 1][actual.y].getNou())
			{
				punts[actual.x - 1][actual.y].setNou();
				camins.push_back(Cami());
				camins[camins.size()-1].setCost();
				camins[camins.size()-1].setRecorregut(actual.x - 1, actual.y);
			}
			else if (comptador == 1 && punts[actual.x - 1][actual.y - 1].getNou())
			{
				punts[actual.x - 1][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x - 1, actual.y - 1);	
			}
			else if (comptador == 2 && punts[actual.x][actual.y - 1].getNou())
			{
				punts[actual.x][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x, actual.y - 1);
			}
			else if (comptador == 3 && punts[actual.x + 1][actual.y - 1].getNou())
			{
				punts[actual.x + 1][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y - 1);
			}
			else if (comptador == 4 && punts[actual.x + 1][actual.y].getNou())
			{
				punts[actual.x + 1][actual.y].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y);
			}
			else if (comptador == 5 && punts[actual.x + 1][actual.y + 1].getNou())
			{
				punts[actual.x + 1][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y + 1);
			}
			else if (comptador == 6 && punts[actual.x][actual.y + 1].getNou())
			{
				punts[actual.x][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x, actual.y + 1);
			}
			else if (comptador == 7 && punts[actual.x - 1][actual.y + 1].getNou())
			{
				punts[actual.x - 1][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x - 1, actual.y + 1);
			}

			comptador++;
		}


	}
}

void disparar(TankDolent tankdolent, TankJugador tank, vector<Bala>* pBala, int * pCBales, Tile * tiles[])
{
	double angle = calculAngle(tankdolent, tank, false);

	vector<Bala> bala = *pBala;
	int cBales = *pCBales;

	if (esVeuen(tankdolent, tank, tiles))
	{
		if (cBales > 0)
		{
			if (bala[cBales - 1].getTemps() > TIEMPO_DE_VIDA)
			{
				bala.push_back(Bala());
				cBales++;
				bala[cBales - 1].ObtenirDades(angle, tank);
			}
		} else
		{
			bala.push_back(Bala());
			cBales++;
			bala[cBales - 1].ObtenirDades(angle, tank);
		}
	}

	*pBala = bala;
	*pCBales = cBales;
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

	double angle = calculAngle(tankdolent,tank, tiles);

	while (move(CapsulaDolent, angle, tiles)&& !esVeuen)
	{
		if (checkCollision(Caixa,CapsulaDolent))
		{
			esVeuen = true;
		}
	}

	return esVeuen;
}


bool move(SDL_Rect CapsulaDolent, double angle, Tile * tiles[])
{
	bool continuar = true;

	//Moure la capsula cap al tank del jugador
	CapsulaDolent.x = cos(angle);
	CapsulaDolent.y = sin(angle);

	if (touchesWall(CapsulaDolent, tiles))
		continuar = false;
	return continuar;
}
