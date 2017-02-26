#pragma once

#include "Tile.h"

class Bala
{
public:
	//en realitat es 10 (amplada) x7 (altura)
	static const int Bala_WIDTH = 10;
	static const int Bala_HEIGHT = 10;

	Bala();

	void move(Tile *tiles[]);

	void render(float degrees, SDL_RendererFlip flipType, double angle);

private:
	//The X and Y offsets of the bala
	int mPosX, mPosY;

	//The velocity of the bala
	int Vel;

	//Temps de la bala
	float Temps, TempsFinal;

	SDL_Rect BalaBox;

};

LTexture gBalaTexture;