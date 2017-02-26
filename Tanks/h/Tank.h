#pragma once

#include "Tile.h"

class Tank
{
public:
	//The dimensions of the dot
	static const int Tank_WIDTH = 55;
	static const int Tank_HEIGHT = 45;

	//Maximum axis velocity of the dot
	static const int TANK_VEL = 5;

	//Initializes the variables
	Tank();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e, SDL_Event* a, double& angle, SDL_Rect& camera, bool& shoot);

	//Moves the dot and check collision against tiles
	void move(Tile *tiles[]);

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);

	//Mostra el tank en pantalla
	void render(double degrees, SDL_RendererFlip flipType, double angle);

	//Obté dades del tanc
	int getVelocitatX();
	int getVelocitatY();

	SDL_Rect getTankBox();

private:
	//The X and Y offsets of the tank
	int mPosX, mPosY;

	//The velocity of the tank
	int mVelX, mVelY;

	SDL_Rect TankBox;
};