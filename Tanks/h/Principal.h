#include "Main.h"

//Inicialitza SDL
bool init();

//Gestiona l'input
bool HandleEvent(SDL_Event*e);

//Carrega les imatges
bool LoadMedia();

const int PosicioXBoto = 500;
const int PosicioYBoto = 500;

const int MargeX = 100;
const int MargeY = 100;