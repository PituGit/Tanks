#include "../h/IA.h"

/*
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

	//Calcula l'angle de rotaci�, per imprimirlo apuntant al mouse
	if ((CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X) != 0)
		angle = atan((double(CapsulaJugador.y - CapsulaDolent.y - MEITAT_CAPSULA_Y)) / double(CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X));
	angle *= 57.3;
	if ((CapsulaJugador.x - CapsulaDolent.x - MEITAT_CAPSULA_X) < 0)
		angle += 180;



	while (move(CapsulaDolent, angle, tiles))
	{

	}


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

*/