#pragma once

#include "Tank.h"

class Bala
{
public:
	//en realitat es 10 (amplada) x7 (altura)
	static const int BALA_WIDTH = 10;
	static const int BALA_HEIGHT = 10;

	Bala();

	void moveBala(Tile *tiles[]);

	void ObtenirDades( SDL_RendererFlip flipType, double angle, Tank tank);

	void renderBala(double degrees, SDL_RendererFlip flipType, double angle, Tank tank);

private:
	//The X and Y offsets of the bala
	int mPosX, mPosY;

	//The velocity of the bala, els signes de la velocitat i la velocitat en cartesianes
	int Vel, signeX, signeY;
	float VelX, VelY;

	//Temps de la bala
	float Temps, TempsFinal;

	//L'angle en el qual est� anant la bala
	float Angle_Direccio;

	SDL_Rect BalaBox;

};