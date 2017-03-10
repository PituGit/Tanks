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

void Bala::renderExplosio(Tank tank)
{

	SDL_Rect TankBox = tank.getTankBox();
	for (int frame = 0; frame < 10; frame++)
	{
		if (frame < 2)
		{
			gExplosioATexture.render(TankBox.x, TankBox.y);
			Sleep(30);
		}

		else if (frame < 4)
		{
			gExplosioBTexture.render(TankBox.x, TankBox.y);
			Sleep(30);
		}

		else if (frame < 6)
		{
			gExplosioCTexture.render(TankBox.x, TankBox.y);
			Sleep(30);
		}

		else if (frame < 8)
		{
			gExplosioDTexture.render(TankBox.x, TankBox.y);
			Sleep(30);
		}

		else if (frame < 10)
		{
			gExplosioETexture.render(TankBox.x, TankBox.y);
			Sleep(30);
		}
		SDL_RenderPresent(gRenderer);
	}
	Sleep(1500);
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

Uint32 Bala::getTemps()
{
	return (SDL_GetTicks() - Temps);
}

bool Bala::moveBala(Tile *tiles[], Tank tank)
{
	//La variable que indica si colisiona
	bool colisio = false;

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

	//Si la bala colisiona amb el tank
	if (checkCollision(BalaBox, tank.getTankBox()))
	{
		colisio = true;
	}
	return colisio;
}