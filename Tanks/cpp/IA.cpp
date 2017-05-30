#include "../h/IA.h"

//Funcio que ens mou els tanks enemics de forma random cada 1 segon
void moveTankRandom(TankDolent &tankdolent, Tile * tiles[], Uint32 &tempsmoviment)
{
	int mVelX = tankdolent.getVelocitatX();
	int mVelY = tankdolent.getVelocitatY();
	if (tempsmoviment + 1000 < SDL_GetTicks())
	{
		mVelX = rand() % 3;
		if (mVelX == 2)
			mVelX = -1;
		mVelX *= 3;

		tankdolent.setVelocitatX(mVelX);

		mVelY = rand() % 3;
		if (mVelY == 2)
			mVelY = -1;
		mVelY *= 3;

		tankdolent.setVelocitatY(mVelY);

		tempsmoviment = SDL_GetTicks();
	}

	tankdolent.setPosicio(mVelX, 0);

	//si toca la paret el tirem enrera i generem de nou una nova velocitat
	if (touchesWall(tankdolent.getTankBox(), tiles))
	{

		mVelX = -mVelX;
		tankdolent.setPosicio(mVelX, 0);

		mVelX = rand() % 3;
		if (mVelX == 2)
			mVelX = -1;
		mVelX *= 3;

		tankdolent.setVelocitatX(mVelX);
	}

	tankdolent.setPosicio(0, mVelY);

	if (touchesWall(tankdolent.getTankBox(), tiles))
	{
		
		mVelY = -mVelY;
		tankdolent.setPosicio(0, mVelY);

		mVelY = rand() % 3;
		if (mVelY == 2)
			mVelY = -1;
		mVelY *= 3;

		tankdolent.setVelocitatY(mVelY);
	}


}
	
//Funcio que fa disparar els tanks enemics
void disparar(TankDolent &tankdolent, TankJugador tank, vector<Bala> &pBala, int * pCBales, Tile * tiles[])
{

	double angle = calculAngle(tankdolent, tank, false);

	vector<Bala> bala = pBala;
	int cBales = *pCBales;

	if (esVeuen(tankdolent, tank, tiles))
	{
		if (cBales > 0)
		{
			if (bala[cBales - 1].getTemps() > TIEMPO_DE_VIDA)
			{
				Mix_PlayChannel(-1, gClick, 0);

				bala.push_back(Bala(ID_DOLENT));
				cBales++;
				bala[cBales - 1].ObtenirDades(angle, tankdolent);
			}

		}

	else

		{
			Mix_PlayChannel(-1, gClick, 0);

			bala.push_back(Bala(ID_DOLENT));
			cBales++;
			bala[cBales - 1].ObtenirDades(angle, tankdolent);
		}

		pBala = bala;
		*pCBales = cBales;
	}
}

//Funcio que comprovoa si el tank enemic i el jugador es veuen, es a dir, no hi ha cap paret entremig
bool esVeuen(TankDolent &tankdolent, TankJugador tank, Tile * tiles[])
{
	SDL_Rect capsulaDolent = tankdolent.getTankBox();
	SDL_Rect capsulaJugador = tank.getTankBox();

	bool seVen = false;

	//Capsula que encercla la posicio del jugador
	SDL_Rect Caixa;
	Caixa.w = capsulaJugador.w + 5;
	Caixa.h = capsulaJugador.h + 5;
	Caixa.x = capsulaJugador.x - 5;
	Caixa.y = capsulaJugador.y - 5;

	double angle = calculAngle(tankdolent, tank, false);

	while (move(capsulaDolent, angle, tiles)&& !seVen)
	{
		if (checkCollision(Caixa,capsulaDolent))

		{
			seVen = true;
			capsulaDolent = tankdolent.getTankBox();
		}
	}

	return seVen;
}

/*Ajuda a la funcio esVeuen a moure la capsa del tank enemic fins a la del tank del jugador (nomes per comprovar si hi 
ha alguna paret entre mig*/
bool move(SDL_Rect &capsulaDolent, double angle, Tile * tiles[])
{
	//Continuem movent la capsa
	bool continuar = true;
	
	int movX = 10 * cos(angle);
	int movY = 10 * sin(angle);
	
	capsulaDolent.x += movX;
	capsulaDolent.y += movY;
  
	//printf("%d %d : %f : %f (int %d), %f (int %d) / ", capsula.x, capsula.y, angle, cos(angle), movX, sin(angle), movY);

	if (touchesWall(capsulaDolent, tiles)) 
	{
		continuar = false;
	}

	return continuar;
}


