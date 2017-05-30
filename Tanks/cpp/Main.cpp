#include "../h/Main.h"

void CalcularGraus(double &degrees, Tank tank)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (tank.getVelocitatX() != 0)
	{
		degrees = atan(tank.getVelocitatY() / tank.getVelocitatX());
		degrees = degrees*57.3;
		if (tank.getVelocitatX()<0)
		{
			degrees += 180;
		}
	}
	else
	{
		if (currentKeyStates[SDL_SCANCODE_UP])
			degrees = 270;
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
			degrees = 90;
	}
}

//Ens ajuda a renderitzar la explosió quan n'hi ha hagut una 
void GestionaColisio(LlistaTank &tankdolent, TankJugador tank, int &cBalesE, int &cBalesJ, int &cTanks,
	std::vector <Bala> &balesenemigues, std::vector <Bala> &balajugador, bool &primercop, SDL_Point Lloc_Explosio,
	int &frame, bool &colisio, bool &colisio2, int &punts)
{

	SDL_Point Explosio = Lloc_Explosio;

	//El primer cop que s'executa necessitem eliminar tank i bala
	if (primercop)
	{
		Mix_PlayChannel(-1, gExplosion, 0);

		bool trobat = false;

		IteradorNodeTank anterior(NULL);
		IteradorNodeTank actual = tankdolent.getInici();
		//Busquem quin tank hem tocat i posteriorment l'eliminarem
		while (!trobat)
		{
			if ((actual.getElement().getTankBox().x + actual.getElement().getTankBox().w + 10) >= Explosio.x
				&& (actual.getElement().getTankBox().y + actual.getElement().getTankBox().h + 10) >= Explosio.y
				&& (actual.getElement().getTankBox().x - 10) < Explosio.x
				&& (actual.getElement().getTankBox().y - 10) <= Explosio.y) {

				trobat = true;
			}

			if (!trobat) {
				anterior = actual;
				actual.seguent();
			}
		}

		if (colisio)
		{
			balesenemigues.erase(balesenemigues.begin() + (cBalesE - 1));
			cBalesE--;

			punts += actual.getElement().punts;
			actual = tankdolent.eliminaNext(anterior);
			cTanks--;
		}

		else if (colisio2)
		{
			balajugador.erase(balajugador.begin() + (cBalesJ - 1));
			cBalesJ--;

			punts += actual.getElement().punts;
			actual = tankdolent.eliminaNext(anterior);
			cTanks--;
		}

	}


	primercop = false;

	renderExplosio(Explosio.x, Explosio.y, frame);

	frame++;

	if (frame / 4 >= 24)
	{
		frame = 0;
		colisio = false;
		colisio2 = false;
		primercop = true;
	}

}

//Carrega els arxius, png's...
bool loadMedia(Tile* tiles[])
{
	//Loading success flag
	bool success = true;

	gFont = TTF_OpenFont("res/font.ttf", 40);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	gInGameSong = Mix_LoadMUS("res/InGameSong.wav");
	if (gInGameSong == NULL)
	{
		printf("Failed to load InGame music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gClick = Mix_LoadWAV("res/Click.wav");
	if (gClick == NULL)
	{
		printf("Failed to load Click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gExplosion = Mix_LoadWAV("res/Explosion.wav");
	if (gExplosion == NULL)
	{
		printf("Failed to load Explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load dot texture
	if (!gBaseTankJugadorTexture.loadFromFile("res/Base_tank_Jugador.png"))
	{
		printf("Failed to load tank_jugador texture!\n");

		success = false;
	}

	if (!gCapsulaJugadorTexture.loadFromFile("res/CapsulaCano_tank_Jugador.png"))
	{
		printf("Failed to load capsula_jugador texture!\n");
		success = false;
	}

	if (!gBaseTankDolentTexture.loadFromFile("res/Base_tank_Dolent.png"))
	{
		printf("Failed to load tank_jugador texture!\n");

		success = false;
	}

	if (!gCapsulaDolentTexture.loadFromFile("res/CapsulaCano_tank_Dolent.png"))
	{
		printf("Failed to load capsula_jugador texture!\n");
		success = false;
	}

	if (!gExplosioTexture.loadFromFile("res/Explosio.png"))
	{
		printf("Failed to load explosio texture!\n");
		success = false;
	}

	if (!gBalaTexture.loadFromFile("res/Bala.png"))
	{
		printf("Failed to load bala texture!\n");
		success = false;
	}

	//Load tile texture
	if (!gTileTexture.loadFromFile("res/tiles.png"))
	{
		printf("Failed to load tile set texture!\n");
		success = false;
	}

	//Load HUD texture
	hudInit(success);

	//Load tile map
	if (!setTiles(tiles))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}

//Tanca els arxius
void close(Tile* tiles[])
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tiles[i] == NULL)
		{
			delete tiles[i];
			tiles[i] = NULL;
		}
	}

	//Free loaded images
	gTileTexture.free();
	gBaseTankJugadorTexture.free();
	gCapsulaJugadorTexture.free();
	gBaseTankDolentTexture.free();
	gCapsulaDolentTexture.free();
	gBalaTexture.free();
	gExplosioTexture.free();
	gVidaTexture.free();
	gTextTexture.free();

	Mix_FreeChunk(gClick);
	gClick = NULL;
	Mix_FreeChunk(gExplosion);
	gExplosion = NULL;

}

//Renderitza l'explosió
void renderExplosio(int x, int y, int imatge)
{
	//Ajusta l'imatge a on esta la bala
	x -= 32;
	y -= 32;

	//Cada 4 frames actualitzarem l'imatge
	int comptadorX = 0;
	int comptadorY = 0;
	int frame = imatge / 2;

	//Serveix per retallar l'imatge de les explosions
	SDL_Rect Caixa_Explosions;

	Caixa_Explosions.w = EXPLOSIO_WIDTH;
	Caixa_Explosions.h = EXPLOSIO_HEIGHT;

	//Divideix per saber quina imatge necessitem
	while (frame >= 0 && frame % 3 != 0)
	{
		comptadorX++;
		frame--;
	}
	
	while (frame > 0)
	{
		comptadorY++;
		frame -= 4;
	}
	
	//Indica quina posicio esta l'imatge
	Caixa_Explosions.x = (192 - comptadorX * 64);
	Caixa_Explosions.y = (192 - comptadorY * 64);

	//Renderitzem
	gExplosioTexture.render(x , y, &Caixa_Explosions);
}

//Inicialitza els tanks
int setTanks(std::vector <int> &ID, std::vector <int> &x, std::vector <int> &y, int nTanks)
{

	//Comptador per el while
	int comptador = 0;
	int i = -1;

	//Obrir l'arxiu de les dades del nivell
	std::ifstream DadesNivell("res/DadesNivell.map");

	if (DadesNivell.fail())
	{
		printf("Error al carregar DadesNivell: Unexpected end of file!\n");
	}

	while (i<nTanks)
	{
		//Obte l'id del tank
		DadesNivell >> ID[comptador];

		//Obte la posicio x i y del tank
		DadesNivell >> x[comptador];
		DadesNivell >> y[comptador];

		comptador++;
		i++;

		if (i<nTanks)
		{
			ID.push_back(int());
			x.push_back(int());
			y.push_back(int());
		}

	}

	DadesNivell.close();

	return nTanks;
}

//Inicialitza el mapa
bool setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("res/lazy.map");

	//Initialize the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//Determines what kind of tile will be made
		int tileType = -1;

		//Read tile from map file
		map >> tileType;

		//If the was a problem in reading the map
		if (map.fail())
		{
			//Stop loading map
			printf("Error loading map: Unexpected end of file!\n");
			tilesLoaded = false;
			break;
		}

		//If the number is a valid tile number
		if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
		{
			tiles[i] = new Tile(x, y, tileType);
		}
		//If we don't recognize the tile type
		else
		{
			//Stop loading map
			printf("Error loading map: Invalid tile type at %d!\n", i);
			tilesLoaded = false;
			break;
		}

		//Move to next tile spot
		x += TILE_WIDTH;

		//If we've gone too far
		if (x >= LEVEL_WIDTH)
		{
			//Move back
			x = 0;

			//Move to the next row
			y += TILE_HEIGHT;
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips[TILE_FLOOR].x = 0;
			gTileClips[TILE_FLOOR].y = 0;
			gTileClips[TILE_FLOOR].w = TILE_WIDTH;
			gTileClips[TILE_FLOOR].h = TILE_HEIGHT;

			gTileClips[TILE_GREEN].x = 0;
			gTileClips[TILE_GREEN].y = 80;
			gTileClips[TILE_GREEN].w = TILE_WIDTH;
			gTileClips[TILE_GREEN].h = TILE_HEIGHT;

			gTileClips[TILE_BLUE].x = 0;
			gTileClips[TILE_BLUE].y = 160;
			gTileClips[TILE_BLUE].w = TILE_WIDTH;
			gTileClips[TILE_BLUE].h = TILE_HEIGHT;

			gTileClips[TILE_TOPLEFT].x = 80;
			gTileClips[TILE_TOPLEFT].y = 0;
			gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
			gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_LEFT].x = 80;
			gTileClips[TILE_LEFT].y = 80;
			gTileClips[TILE_LEFT].w = TILE_WIDTH;
			gTileClips[TILE_LEFT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMLEFT].x = 80;
			gTileClips[TILE_BOTTOMLEFT].y = 160;
			gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

			gTileClips[TILE_TOP].x = 160;
			gTileClips[TILE_TOP].y = 0;
			gTileClips[TILE_TOP].w = TILE_WIDTH;
			gTileClips[TILE_TOP].h = TILE_HEIGHT;

			gTileClips[TILE_CENTER].x = 160;
			gTileClips[TILE_CENTER].y = 80;
			gTileClips[TILE_CENTER].w = TILE_WIDTH;
			gTileClips[TILE_CENTER].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOM].x = 160;
			gTileClips[TILE_BOTTOM].y = 160;
			gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

			gTileClips[TILE_TOPRIGHT].x = 240;
			gTileClips[TILE_TOPRIGHT].y = 0;
			gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_RIGHT].x = 240;
			gTileClips[TILE_RIGHT].y = 80;
			gTileClips[TILE_RIGHT].w = TILE_WIDTH;
			gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_BOTTOMRIGHT].x = 240;
			gTileClips[TILE_BOTTOMRIGHT].y = 160;
			gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
			gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

//Funció principal, on hi ha el bucle principal en el qual s'executa el joc
bool joc(bool &quit, int vides, int &punts, int nTanks)
{
	//si sha superat el nivell
	bool superat = true;

	//Si el tank del jugador ha explotat
	bool mort = false;

	bool primercop = true;

	//Temps per controlar la renderitzacio de l'explosio
	UINT32 temps = 0, tempsinicial = 0;

	//Lloc on explota la bala
	SDL_Point Lloc_Explosio;

	//The level tiles
	Tile* tileSet[TOTAL_TILES];

	//Load media
	if (!loadMedia(tileSet))
	{
		printf("Failed to load media!\n");
	}
	else
	{
		Mix_PlayMusic(gInGameSong, -1);

		//Event handler
		SDL_Event e;

		//tanks i bales que exploten
		int Bala_que_explota = 0;
		int numerotank = 0;

		int frame = 0;

		//Angle de rotació
		double degrees = 0, angle = 0;

		//tipus de rotacio
		SDL_RendererFlip flipType = SDL_FLIP_NONE;

		//Les bales que es pintaran per pantalla
		std::vector <Bala> balesenemigues(0);
		std::vector <Bala> balajugador(0);

		//The tank that will be moving around on the screen
		TankJugador tank;
		LlistaTank tankdolent;

		//Vectors de les dades a llegir del fitxer 
		std::vector<int> ID(1);
		std::vector<int> x(1);
		std::vector<int> y(1);

		//Obtenim el numero de tanks enemics
		int cTanks = setTanks(ID, x, y, nTanks);

		//Variable que controla cada quan canvia la direccio dels tanks enemics
		std::vector <Uint32> tempsmoviment(cTanks);
		for (int i = 0; i < cTanks; i++)
		{
			tempsmoviment[i] = SDL_GetTicks() - 500;
		}
		

		tank.InicialitzaDades(ID[0], x[0], y[0]);

		IteradorNodeTank anterior(NULL);
		IteradorNodeTank actual = tankdolent.getInici();
		for (int i = 0; i < cTanks; i++)
		{
			TankDolent t;
			t.InicialitzaDades(ID[i + 1], x[i + 1], y[i + 1]);

			anterior = actual;

			actual = tankdolent.insereixNext(t, anterior); // actual seguent es el problema
	
		}


		//Variable per saber si s'ha disparat
		bool shoot = false;

		//La variable que indica si han colisionat
		bool colisio = false;
		bool colisio2 = false;

		//Numero de bales que te
		int cBalesE = 0;
		int cBalesJ = 0;

		//Level camera
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		//While application is running
		while (!mort && !quit && cTanks>0)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				//Gestiona les dades introduides
				tank.handleEvent(e, &e, angle, camera, shoot);
			}
			CalcularGraus(degrees, tank);

			//Eliminem bales si es necessari
			for (int i = 0; i < cBalesE; i++)
			{
				if (balesenemigues[i].ControlaBales())
				{
					for (int j = i; j < cBalesE - 1; j++)
					{
						balesenemigues[j] = balesenemigues[j + 1];
					}
					balesenemigues.erase(balesenemigues.begin() + (cBalesE - 1));
					cBalesE--;
				}
			}
			for (int i = 0; i < cBalesJ; i++)
			{
				if (balajugador[i].ControlaBales())
				{
					for (int j = i; j < cBalesJ - 1; j++)
					{
						balajugador[j] = balajugador[j + 1];
					}
					balajugador.erase(balajugador.begin() + (cBalesJ - 1));
					cBalesJ--;
				}
			}

			//Mou el tank
			//tank.AjustarVelocitat();
			tank.move(tileSet);

			actual = tankdolent.getInici();
			for (int i = 0; i < cTanks; i++)
			{
				moveTankRandom(actual.getElement(), tileSet, tempsmoviment[i]); //potser canvi
				actual.seguent();
			}

			//Movem els dos vectors de bales
			for (int i = 0; i < cBalesE; i++)
			{
				if (balesenemigues[i].moveBala(tileSet, tank, tankdolent, mort, cTanks, numerotank)) //Potser s'ha de canviar
				{
					colisio = true;
					Lloc_Explosio.x = balesenemigues[i].getBalaBox().x;
					Lloc_Explosio.y = balesenemigues[i].getBalaBox().y;
					Bala_que_explota = i;
				}
			}
			for (int i = 0; i < cBalesJ; i++)
			{
				if (balajugador[i].moveBala(tileSet, tank, tankdolent, mort, cTanks, numerotank)) //Potser s'ha de canviar
				{
					colisio2 = true;
					Lloc_Explosio.x = balajugador[i].getBalaBox().x;
					Lloc_Explosio.y = balajugador[i].getBalaBox().y;
					Bala_que_explota = i;
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);


			//Render level
			for (int i = 0; i < TOTAL_TILES; ++i)
			{
				tileSet[i]->render(camera);
			}

			actual = tankdolent.getInici();
			for (int i = 0; i < cTanks; i++)
			{		
				disparar(actual.getElement(), tank, balesenemigues, &cBalesE, tileSet);

				actual.seguent();
			}

			//Render el tank
			tank.render(degrees, flipType, angle);

			//Renderitza el tank enemic
			actual = tankdolent.getInici();
			for (int i = 0; i < cTanks; i++)
			{
				actual.getElement().render(0, flipType, tank);
				actual.seguent();
			}


			//si es dispara augmentem el vector i el numero de bales (cBales)
			if (shoot)
			{
				if (cBalesJ > 0)
				{
					if (balajugador[cBalesJ - 1].getTemps() > TIEMPO_DE_VIDA)
					{
						Mix_PlayChannel(-1, gClick, 0);

						balajugador.push_back(Bala());
						cBalesJ++;
						balajugador[cBalesJ - 1].ObtenirDades(angle, tank);
					}
				}
				else
				{
					Mix_PlayChannel(-1, gClick, 0);

					balajugador.push_back(Bala());
					cBalesJ++;
					balajugador[cBalesJ - 1].ObtenirDades(angle, tank);
				}

			}

			//Renderitza totes les bales
			for (int i = 0; i < cBalesE; i++) {
				balesenemigues[i].renderBala(degrees, flipType, angle, tank);
			}
				
			for (int i = 0; i < cBalesJ; i++) {
				balajugador[i].renderBala(degrees, flipType, angle, tank);
			}

			//Renderitza i elimina bales/tanks
			if ((colisio || colisio2) && !mort)
			{
				GestionaColisio(tankdolent, tank, cBalesE, cBalesJ, cTanks, balesenemigues,
					balajugador, primercop, Lloc_Explosio, frame, colisio, colisio2, punts);
			}

			//Renderitza l'HUD
			hudRender(vides, punts);

			//Update screen
			SDL_RenderPresent(gRenderer);
		}
		if ((colisio || colisio2) && !mort)
		{
			while (colisio || colisio2)
			{
				GestionaColisio(tankdolent, tank, cBalesE, cBalesJ, cTanks, balesenemigues,
					balajugador, primercop, Lloc_Explosio, frame, colisio, colisio2, punts);
				//Update screen
				SDL_RenderPresent(gRenderer);

			}
			return superat;
		}
		
		
		

		if (colisio || colisio2)
		{
			Mix_PlayChannel(-1, gExplosion, 0);

			while (colisio || colisio2)
			{
				renderExplosio(tank.getTankBox().x + MEITAT_CAPSULA_X, tank.getTankBox().y + MEITAT_CAPSULA_Y, frame);

				frame++;

				if (frame / 4 >= 24)
				{

					Mix_HaltMusic();

					frame = 0;
					colisio = false;
					colisio2 = false;
					primercop = true;
					superat = false;
				}

				//Update screen
				SDL_RenderPresent(gRenderer);

			}
		}
			
		Sleep(1500);
	}

	//Free resources
	close(tileSet);

	return superat;
}