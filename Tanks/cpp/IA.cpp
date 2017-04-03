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

SDL_Point Cami::getUltimPunt()
{
	return recorregut[recorregut.size() - 1];
}

std::vector <SDL_Point> Cami::getRecorregut()
{
	return recorregut;
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

	//Variable que contindr� el valor de la posicio del cami m�s �ptim
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


Cami GeneraCami(TankDolent tankdolent, TankJugador tank, Tile * tiles[])
{
	//Conjunt de tots els camins possibles
	std::vector <Cami> camins(0);

	//Ens indica en quina posicio esta el cami m�s �ptim
	int variable = 0;


	int comptador = 0, comptador2 = 0;

	//Variable que ens indica si hem trobat el final
	bool trobat = false;

	//Conjut de punts que configuren tot el mapa
	Punt punts[MAX_X][MAX_Y];

	//Punt que estarem analitzant 
	SDL_Point actual;
	actual.x = tankdolent.getTankBox().x;
	actual.y = tankdolent.getTankBox().y;

	//Capsa de 1x1 al voltant del punt actual, simplement per poder fer servir la funcio toucheswall
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
			if (comptador == 0 && punts[actual.x - 1][actual.y].getNou())
			{
				punts[actual.x - 1][actual.y].setNou();
				camins.push_back(Cami());
				camins[camins.size()-1].setCost();
				camins[camins.size()-1].setRecorregut(actual.x - 1, actual.y);
				actual.x--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.x++;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}
			else if (comptador == 1 && punts[actual.x - 1][actual.y - 1].getNou())
			{
				punts[actual.x - 1][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x - 1, actual.y - 1);
				actual.x--;
				actual.y--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.x++;
				actual.y++;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}
			else if (comptador == 2 && punts[actual.x][actual.y - 1].getNou())
			{
				punts[actual.x][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x, actual.y - 1);
				actual.y--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.y++;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}
			else if (comptador == 3 && punts[actual.x + 1][actual.y - 1].getNou())
			{
				punts[actual.x + 1][actual.y - 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y - 1);
				actual.y--;
				actual.x++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.y++;
				actual.x--;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}
			else if (comptador == 4 && punts[actual.x + 1][actual.y].getNou())
			{
				punts[actual.x + 1][actual.y].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y);
				actual.x++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.x--;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}
			else if (comptador == 5 && punts[actual.x + 1][actual.y + 1].getNou())
			{
				punts[actual.x + 1][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x + 1, actual.y + 1);
				actual.x++;
				actual.y++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.x--;
				actual.y--;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}
			else if (comptador == 6 && punts[actual.x][actual.y + 1].getNou())
			{
				punts[actual.x][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x, actual.y + 1);
				actual.y++;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.y--;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}
			else if (comptador == 7 && punts[actual.x - 1][actual.y + 1].getNou())
			{
				punts[actual.x - 1][actual.y + 1].setNou();
				camins.push_back(Cami());
				camins[camins.size() - 1].setCost();
				camins[camins.size() - 1].setRecorregut(actual.x - 1, actual.y + 1);
				actual.y++;
				actual.x--;
				camins[camins.size() - 1].setDistancia(actual, objectiu);
				camins[camins.size() - 1].setCostTotal();
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
				if (touchesWall(actual_Box, tiles))
				{
					camins.pop_back();
				}
				actual.x++;
				actual.y--;
				actual_Box.x = actual.x;
				actual_Box.y = actual.y;
			}

			comptador++;
		}
		comptador = 0;

		//Variable que indica quina es la posicio del cami m�s �ptim actualment
		variable = BuscaCami(camins);

		actual = camins[variable].getUltimPunt();
		actual_Box.x = actual.x;
		actual_Box.y = actual.y;
	}

	return camins[variable];
}


void moveTankEnemic(TankDolent tankdolent, TankJugador tank, Tile * tiles[])
{
	Cami cami = GeneraCami(tankdolent, tank, tiles);

	std::vector <SDL_Point> recorregut = cami.getRecorregut();

	tankdolent.setPosicio(recorregut[1].x, recorregut[1].y);
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
				bala.push_back(Bala(ID_DOLENT));
				cBales++;
				bala[cBales - 1].ObtenirDades(angle, tankdolent);
			}

		}

  else

		{
			bala.push_back(Bala(ID_DOLENT));
			cBales++;
			bala[cBales - 1].ObtenirDades(angle, tankdolent);
		}

		*pBala = bala;
		*pCBales = cBales;
	}
}

bool esVeuen(TankDolent tankdolent, TankJugador tank, Tile * tiles[])
{
	SDL_Rect capsulaDolent = tankdolent.getTankBox();
	SDL_Rect capsulaJugador = tank.getTankBox();

	bool esVeuen = false;

	//Capsula que encercla la posicio del jugador
	SDL_Rect Caixa;
	Caixa.w = capsulaJugador.w + 5;
	Caixa.h = capsulaJugador.h + 5;
	Caixa.x = capsulaJugador.x - 5;
	Caixa.y = capsulaJugador.y - 5;

	double angle = calculAngle(tankdolent, tank, false);

	while (move(capsulaDolent, angle, tiles)&& !esVeuen)
	{
		if (checkCollision(Caixa,capsulaDolent))

		{
			esVeuen = true;
			capsulaDolent = tankdolent.getTankBox();
		}
	}

	return esVeuen;
}


bool move(SDL_Rect &capsulaDolent, double angle, Tile * tiles[])
{
	//Continuem movent la capsa
	bool continuar = true;
	
	int movX = 10 * cos(angle);
	int movY = 10 * sin(angle);
	
	capsulaDolent.x += movX;
	capsulaDolent.y += movY;


	//printf("%d %d : %f : %f (int %d), %f (int %d) / ", capsula.x, capsula.y, angle, cos(angle), movX, sin(angle), movY);
  if (touchesWall(capsulaDolent, tiles)) 
  {
		continuar = false;
	}

	return continuar;
}
