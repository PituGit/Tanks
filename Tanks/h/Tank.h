#pragma once

#include "Tile.h"

enum TANK_ID
{
	ID_JUGADOR,
	ID_DOLENT,
};

class Tank
{
public:
	//Les dimensions del tank
	const int Tank_WIDTH = 45;
	const int Tank_HEIGHT = 45;

	//Maximum axis velocity of the dot
	static const int TANK_VEL = 5;

	//Ajusta la velocitat perque no vagi mes rapid en diagonal
	//void AjustarVelocitat();

	//Initializes the variables
	Tank(int tankId);

	Tank(const Tank &Tank2);

	void InicialitzaDades(int x, int y, int tankId);

	//Obté dades del tanc
	float getVelocitatX();
	float getVelocitatY();

	SDL_Rect getTankBox();

protected:

	//The velocity of the tank
	float mVelX, mVelY;

	SDL_Rect TankBox;

	int mTankId;
};

class TankJugador : public Tank 
{
public:	
	TankJugador() : Tank(ID_JUGADOR) {};

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e, SDL_Event* a, double& angle, SDL_Rect& camera, bool &shoot);

	//Moves the tank and check collision against tiles
	void move(Tile *tiles[]);

	void render(double degrees, SDL_RendererFlip flipType, double angle);

};

class TankDolent : public Tank 
{
public:
	TankDolent() : Tank(ID_DOLENT) {};
	void render(double degrees, SDL_RendererFlip flipType, double angle, TankJugador tankJugador);
};