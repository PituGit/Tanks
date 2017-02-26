#include "../h/Tank.h"

Tank::Tank()
{
	//Initialize the collision box
	TankBox.x = 400;
	TankBox.y = 500;
	TankBox.w = Tank_WIDTH;
	TankBox.h = Tank_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
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

void Tank::handleEvent(SDL_Event& e, SDL_Event* a, double& angle, SDL_Rect& camera, bool& shoot)
{
	shoot = false;

	//Get la posicio del mouse
	int x, y;
	SDL_GetMouseState(&x, &y);
	//Calcula l'angle de rotació, per imprimirlo apuntant al mouse
	if ((x - TankBox.x - MEITAT_CAPSULA_X) != 0)
		angle = atan((double(y - TankBox.y - MEITAT_CAPSULA_Y)) / double(x - TankBox.x - MEITAT_CAPSULA_X));
	angle *= 57.3;
	if ((x - TankBox.x - MEITAT_CAPSULA_X) < 0)
		angle += 180;

	//Si s'ha apretat el botó del ratoli
	if (a->type == SDL_MOUSEBUTTONDOWN)
	{
		shoot = true;
	}

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= TANK_VEL; break;
		case SDLK_DOWN: mVelY += TANK_VEL; break;
		case SDLK_LEFT: mVelX -= TANK_VEL; break;
		case SDLK_RIGHT: mVelX += TANK_VEL; break;
		}

		
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += TANK_VEL; break;
		case SDLK_DOWN: mVelY -= TANK_VEL; break;
		case SDLK_LEFT: mVelX += TANK_VEL; break;
		case SDLK_RIGHT: mVelX -= TANK_VEL; break;
		}
	}
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

void Tank::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (TankBox.x + Tank_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (TankBox.y + Tank_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Tank::render(double degrees, SDL_RendererFlip flipType, double angle)
{
	//Centre de rotació del tanc
	SDL_Point centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y };
	SDL_Point* center = &centre;
	//Mostra el tank
	gBaseTankTexture.render(TankBox.x, TankBox.y, NULL, degrees, center, flipType);
	//Angle en el que apunta
	degrees = angle;
	centre = { MEITAT_CAPSULA_X, MEITAT_CAPSULA_Y - 4 };
	gCapsulaTexture.render(TankBox.x, TankBox.y + 4, NULL, degrees, center, flipType);
}


void Tank::move(Tile *tiles[])
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