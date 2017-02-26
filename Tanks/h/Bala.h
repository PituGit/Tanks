#pragma once

#include "Tank.h"

class Bala
{
public:
	//es 8 (amplada) x8 (altura)
	static const int BALA_WIDTH = 8;
	static const int BALA_HEIGHT = 8;

	Bala();

	void moveBala(Tile *tiles[]);

	void ObtenirDades( double angle, Tank tank);

	void renderBala(double degrees, SDL_RendererFlip flipType, double angle, Tank tank);

	bool ControlaBales();

private:
	//The X and Y offsets of the bala
	int mPosX, mPosY;

	//The velocity of the bala, els signes de la velocitat i la velocitat en cartesianes
	int Vel, signeX, signeY;
	double VelX, VelY;

	//Temps de la bala
	Uint32 Temps, TempsFinal;

	//L'angle en el qual està anant la bala
	double Angle_Direccio;

	SDL_Rect BalaBox;

};