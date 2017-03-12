#include "../h/Tank.h"

Tank::Tank(int x, int y, int tankId)
{
	//Initialize the collision box
	TankBox.x = x;
	TankBox.y = y;
	TankBox.w = Tank_WIDTH;
	TankBox.h = Tank_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	mTankId = tankId;
}

float Tank::getVelocitatX()
{
	return mVelX;
}

float Tank::getVelocitatY()
{
	return mVelY;
}

SDL_Rect Tank::getTankBox()
{
	return TankBox;
}

/*
void Tank::AjustarVelocitat()
{
	//Ajusta la velocitat perque no vagi mes rapid en diagonal
	if (mVelX != 0 && mVelY != 0)
	{
		if (mVelX > 0 && mVelY > 0)
		{
			mVelX = TANK_VEL * cos( 7 * PI / 4 );
			mVelY = TANK_VEL * sin( 7 * PI / 4 );
		}
		else if (mVelX > 0 && mVelY < 0)
		{
			mVelX = TANK_VEL * cos( PI / 4);
			mVelY = TANK_VEL * sin( PI / 4);
		}
		else if (mVelX < 0 && mVelY > 0)
		{ 
			mVelX = TANK_VEL * cos( 3 * PI / 4);
			mVelY = TANK_VEL * sin( 3 * PI / 4);
		}
		else if (mVelX < 0 && mVelY < 0)
		{
			mVelX = TANK_VEL * cos( 5 * PI / 4);
			mVelY = TANK_VEL * sin( 5 * PI / 4);
		}
	}
}
*/

void TankJugador::handleEvent(SDL_Event & e, SDL_Event * a, double & angle, SDL_Rect & camera, bool & shoot)
{
	shoot = false;

	//Get la posicio del mouse
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Calcula l'angle de rotació, per imprimirlo apuntant al mouse
	if ((x - TankBox.x - MEITAT_CAPSULA_X) != 0)
		angle = atan(double(y - TankBox.y - MEITAT_CAPSULA_Y) / double(x - TankBox.x - MEITAT_CAPSULA_X+1));

	angle *= 57.2957795;

	if ((x - TankBox.x - MEITAT_CAPSULA_X) < 0)
		angle += 180;

	if (a->type == SDL_MOUSEBUTTONDOWN)
		shoot = true;

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		case SDLK_w: mVelY -= TANK_VEL; break;

		case SDLK_DOWN:
		case SDLK_s: mVelY += TANK_VEL; break;

		case SDLK_LEFT:
		case SDLK_a: mVelX -= TANK_VEL; break;

		case SDLK_RIGHT:
		case SDLK_d: mVelX += TANK_VEL; break;
		}


	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		case SDLK_w: mVelY += TANK_VEL; break;
		case SDLK_DOWN:
		case SDLK_s: mVelY -= TANK_VEL; break;
		case SDLK_LEFT:
		case SDLK_a: mVelX += TANK_VEL; break;
		case SDLK_RIGHT:
		case SDLK_d: mVelX -= TANK_VEL; break;
		}
	}
}

void TankJugador::move(Tile * tiles[])
{
	//Move the dot left or right
	TankBox.x += mVelX;

	//If the dot went too far to the left or right or touched a wall
	if ((TankBox.x < 0) || (TankBox.x + Tank_WIDTH > LEVEL_WIDTH) || touchesWall(TankBox, tiles))
	{
		//move back
		TankBox.x -= mVelX;
	}

	//Move the dot up or down
	TankBox.y += mVelY;

	//If the dot went too far up or down or touched a wall
	if ((TankBox.y < 0) || (TankBox.y + Tank_HEIGHT > LEVEL_HEIGHT) || touchesWall(TankBox, tiles))
	{
		//move back
		TankBox.y -= mVelY;
	}
}

void TankJugador::render(double degrees, SDL_RendererFlip flipType, double angle)
{
	//Centre de rotació del tanc
	SDL_Point centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y };
	SDL_Point* center = &centre;

	//Mostra el tank
	gBaseTankJugadorTexture.render(TankBox.x, TankBox.y, NULL, degrees, center, flipType);
	//Angle en el que apunta
	degrees = angle;
	centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y - 4 };

	gCapsulaJugadorTexture.render(TankBox.x, TankBox.y + 4, NULL, degrees, center, flipType);
}

void TankDolent::render(double degrees, SDL_RendererFlip flipType, double angle, TankJugador tankJugador)
{
	SDL_Rect jugador;
	jugador = tankJugador.getTankBox();

	//Calcula l'angle de rotació, per imprimirlo apuntant al mouse
	if ((jugador.x - TankBox.x - MEITAT_CAPSULA_X) != 0)
		angle = atan((double(jugador.y - TankBox.y - MEITAT_CAPSULA_Y)) / double(jugador.x - TankBox.x - MEITAT_CAPSULA_X));
	angle *= 57.3;
	if ((jugador.x - TankBox.x - MEITAT_CAPSULA_X) < 0)
		angle += 180;

	//Centre de rotació del tanc
	SDL_Point centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y };
	SDL_Point* center = &centre;

	//Mostra el tank
	gBaseTankDolentTexture.render(TankBox.x, TankBox.y, NULL, degrees, center, flipType);
	//Angle en el que apunta
	degrees = angle;
	centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y - 4 };

	gCapsulaDolentTexture.render(TankBox.x, TankBox.y + 4, NULL, degrees, center, flipType);
}
