#include "../h/Bala.h"

Bala::Bala()
{
	//Initialize the collision box
	BalaBox.x = 400;
	BalaBox.y = 500;
	BalaBox.w = Bala_WIDTH;
	BalaBox.h = Bala_HEIGHT;

	//Initialize the velocity
	Vel = 10;
}

void Bala::render(float degrees, SDL_RendererFlip flipType, double angle)
{
	degrees = angle;
	gBalaTexture.render(mPosX, mPosY, NULL, degrees, NULL, flipType);
}

void Bala::move(Tile *tiles[])
{
	//Move the dot left or right
	BalaBox.x += cos(Vel);

	//If the dot went too far to the left or right or touched a wall
	if ((BalaBox.x < 0) || (BalaBox.x + Bala_WIDTH > LEVEL_WIDTH) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.x -= cos(Vel);
	}

	//Move the dot up or down
	BalaBox.y += sin(Vel);

	//If the dot went too far up or down or touched a wall
	if ((BalaBox.y < 0) || (BalaBox.y + Bala_HEIGHT > LEVEL_HEIGHT) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.y -= sin(Vel);
	}
}
