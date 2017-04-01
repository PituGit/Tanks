#include "../h/IA.h"

Punt::Punt()
{
	nou = false;
}

Cami::Cami()
{
	cost = 0;

	distancia = 0;
}

void GeneraCami(TankDolent tankdolent, TankJugador tank, Tile* tiles[])
{
	std::vector <Cami> camins(0);

	//Si hem arribat al final
	bool trobat = false;

	while (!trobat)
	{

	}
}


//Comprova si el tank dolent i el bo es veuen, movent la caixa capsuladolent fins al jugador
bool esVeuen(TankDolent tankdolent, TankJugador tank, Tile * tiles[])
{
	SDL_Rect CapsulaDolent = tankdolent.getTankBox();
	SDL_Rect CapsulaJugador = tank.getTankBox();

	//Capsula que encercla la posicio del jugador
	SDL_Rect Caixa;
	Caixa.w = CapsulaJugador.w + 5;
	Caixa.h = CapsulaJugador.h + 5;
	Caixa.x = CapsulaJugador.x;

	double angle = 0;

	//La variable que ens dira si hem arribat a la caixa que buscavem
	bool trobat = false;

	//Calcula l'angle de rotació, per imprimirlo apuntant al mouse
	if ((CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X) != 0)
		angle = atan((double(CapsulaJugador.y - CapsulaDolent.y - MEITAT_CAPSULA_Y)) / double(CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X));
	angle *= 57.3;
	if ((CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X) < 0)
		angle += 180;


	//Condicions: que podem continuar movent i que la capsula no hagi arribat al final (dins de la capsula del jugador)
	while (move(CapsulaDolent, angle, tiles) && !trobat)
	{
		if ((CapsulaDolent.x < CapsulaJugador.x || CapsulaDolent.x>
			(CapsulaJugador.x + CapsulaJugador.w)) && (CapsulaDolent.y < CapsulaJugador.y || CapsulaDolent.y >
			(CapsulaJugador.y + CapsulaJugador.h)))
			trobat = true;

	}

	//Retornara true si es veuen
	return trobat;
}

//Mou la capsula dolent en la direccio que es troba el tank del jugador
bool move(SDL_Rect &CapsulaDolent, double angle, Tile * tiles[])
{
	//Ens indica si hem de continuar movent la caixa o bé hem topat amb una paret
	bool continuar = true;

	//Moure la capsula cap al tank del jugador
	CapsulaDolent.x = cos(angle);
	CapsulaDolent.y = sin(angle);

	if (touchesWall(CapsulaDolent, tiles))
		continuar = false;

	return continuar;
}


