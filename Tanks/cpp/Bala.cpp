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
}

void Bala::ObtenirDades( double angle, Tank tank)
{
	SDL_Point centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y - 4 };
	SDL_Point* center = &centre;

	Angle_Direccio = angle;
	SDL_Rect PosicioT = tank.getTankBox();

	if (cos(Angle_Direccio) < 0)
		signeX = -1;
	if (sin(Angle_Direccio) > 0)
		signeY = -1;

	//Velocitats cartesianes de la bala
	VelX = double(Vel) * cos(Angle_Direccio * PI / 180) * signeX;
	VelY = double(Vel) * sin(Angle_Direccio * PI / 180) * signeY;

	//Calcul de la posicio de la punta del cano = Posicio de la bala quan es dispara
	BalaBox.x = PosicioT.x + centre.x;
	BalaBox.y = PosicioT.y + centre.y;
}

void Bala::renderBala(double degrees, SDL_RendererFlip flipType, double angle, Tank tank)
{
	gBalaTexture.render(BalaBox.x, BalaBox.y);
}

void Bala::moveBala(Tile *tiles[])
{
	//Move the bala left or right
	BalaBox.x += VelX;

	//If the bala went too far to the left or right or touched a wall
	if ((BalaBox.x < 0) || (BalaBox.x + BALA_WIDTH > LEVEL_WIDTH) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.x -= VelX;
		signeX = -signeX;
		VelX *= signeX;
	}

	//Move the bala up or down
	BalaBox.y += VelY;

	//If the bala went too far up or down or touched a wall
	if ((BalaBox.y < 0) || (BalaBox.y + BALA_HEIGHT > LEVEL_HEIGHT) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.y -= VelY;
		signeY = -signeY;
		VelY *= signeY;
	}
}
