#include "Bala.h"

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

void Bala::move(Tile *tileSet[])
{

}

void Bala::render(float degrees, SDL_RendererFlip flipType, double angle)
{
	degrees = angle;
	gBalaTexture.render(mPosX, mPosY, NULL, degrees, NULL, flipType);
}