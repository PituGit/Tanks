#include "Main.h"

//Inicialitza SDL
bool init();

//Gestiona l'input
int HandleEvent(SDL_Event*e);

//Carrega les imatges
bool LoadMedia();

bool SeguentNivell(bool &quit, int vides, int &punts, int nTanks);

const int X_PLAY = 425;
const int Y_PLAY = 500;

const int X_SCB = 750;
const int Y_SCB = 500;

const int X_RETRY = 550;
const int Y_RETRY = 800;

enum BOTO
{
	CAP,
	PLAY,
	SCORE,
	RETRY
};