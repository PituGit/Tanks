#include "../h/Bala.h"

Bala::Bala()
{
	//Initialize the collision box
	BalaBox.w = BALA_WIDTH;
	BalaBox.h = BALA_HEIGHT;

	//Initialize the velocity
	Vel = 10;
	signeX = 1;
	signeY = 1;
	VelX = 0;
	VelY = 0;
	Angle_Direccio = 0;

	//Temps
	Temps = SDL_GetTicks();

}

Bala::Bala(int id)
{
	//Initialize the collision box
	BalaBox.w = BALA_WIDTH;
	BalaBox.h = BALA_HEIGHT;

	//Initialize the velocity
	Vel = 10;
	signeX = 1;
	signeY = 1;
	VelX = 0;
	VelY = 0;
	Angle_Direccio = 0;

	//Temps
	Temps = SDL_GetTicks();

	shooterId = id;
}

void Bala::ObtenirDades( double angle, Tank tank)
{
	SDL_Point centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y - 4 };
	SDL_Point* center = &centre;

	Angle_Direccio = angle;
	SDL_Rect PosicioT = tank.getTankBox();

	if (Angle_Direccio < 90 && Angle_Direccio > 270)
		signeX = -1;
	if (Angle_Direccio < 0 && Angle_Direccio > 180)
		signeY = -1;
	
	//Velocitats cartesianes de la bala
	VelX = double(Vel) * cos(Angle_Direccio * PI / 180) * signeX;
	VelY = double(Vel) * sin(Angle_Direccio * PI / 180) * signeY;

	//Calcul de la posicio de la punta del cano = Posicio de la bala quan es dispara
	BalaBox.x = PosicioT.x + centre.x + LONGITUD_TOTAL_DEL_CANO * cos(Angle_Direccio * PI / 180) - 5;
	BalaBox.y = PosicioT.y + centre.y + LONGITUD_TOTAL_DEL_CANO * sin(Angle_Direccio * PI / 180);
}

void Bala::renderBala(double degrees, SDL_RendererFlip flipType, double angle, Tank tank)
{
	gBalaTexture.render(BalaBox.x, BalaBox.y);
}

bool Bala::ControlaBales()
{
	bool trobat = false;
	if ((SDL_GetTicks() - Temps) > 2000)
	{
		trobat = true;
	}
	return trobat;
}

//Retorna el temps que ha estat viva la bala
Uint32 Bala::getTemps()
{
	return (SDL_GetTicks() - Temps);
}

//Retorna la capsula de colisio de la bala
SDL_Rect Bala::getBalaBox()
{
	return BalaBox;
}

bool Bala::moveBala(Tile *tiles[], TankJugador tank, LlistaTank &tankdolent, 
	bool& mort, int cTanks, int &numerotank)
{
	//La variable que indica si colisiona
	bool colisio = false;

	//Mout la bala esquerra o dreta
	BalaBox.x += VelX;

	//Si la bala ha anat massa cap a la dreta o esquerra o ha tocat una paret
	if ((BalaBox.x < 0) || (BalaBox.x + BALA_WIDTH > LEVEL_WIDTH) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.x -= VelX;
		signeX = -signeX;
		VelX *= signeX;
	}

	//Mou la bala amunt o aball
	BalaBox.y += VelY;

	//Si ha hanat massa amunt o avall o ha tocat una paret
	if ((BalaBox.y < 0) || (BalaBox.y + BALA_HEIGHT > LEVEL_HEIGHT) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.y -= VelY;
		signeY = -signeY;
		VelY *= signeY;
	}

	//Si la bala colisiona amb el tank
	if (checkCollision(BalaBox, tank.getTankBox()))
	{
		colisio = true;
		mort = true;
	}

	int i = 0;
	IteradorNodeTank actual = tankdolent.getInici();

	while(!colisio && i<cTanks)
	{

		SDL_Rect tankBox = actual.getElement().getTankBox();
		if (checkCollision(BalaBox, tankBox))
		{
			colisio = true;
			numerotank = i - 1;
		}

	
		i++;
		actual.seguent();
	}
	
	return colisio;
}
