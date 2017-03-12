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

bool loadMedia(Tile* tiles[])
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gBaseTankJugadorTexture.loadFromFile("res/Base_tank_Jugador.png"))
	{
		printf( "Failed to load tank_jugador texture!\n" );

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

	//Load tile map
	if (!setTiles(tiles))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}

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
}

void renderExplosio(int x, int y, SDL_Rect Caixa_Explosions)
{
	gExplosioTexture.render(x , y, &Caixa_Explosions);
	SDL_RenderPresent(gRenderer);
	Sleep(10);
}

void setExplosions(int x, int y)
{
	SDL_Rect Caixa_Explosions;

	Caixa_Explosions.w = EXPLOSIO_WIDTH;
	Caixa_Explosions.h = EXPLOSIO_HEIGHT;

	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			Caixa_Explosions.x = j*64;
			Caixa_Explosions.y = i*64;

			renderExplosio(x, y, Caixa_Explosions);
		}
	}

}



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


bool joc()
{
	//si sha superat el nivell
	bool superat = true;

	//The level tiles
	Tile* tileSet[TOTAL_TILES];

	//Load media
	if (!loadMedia(tileSet))
	{
		printf("Failed to load media!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Angle de rotació
		double degrees = 0, angle = 0;

		//tipus de rotacio
		SDL_RendererFlip flipType = SDL_FLIP_NONE;

		//Les bales que es pintaran per pantalla
		std::vector <Bala> bala(MAX_BALES);
		bala.erase(bala.begin());

		//The tank that will be moving around on the screen
		TankJugador tank(400,500);
		TankDolent dolentProva(800,500);

		//Variable per saber si s'ha disparat
		bool shoot = false;

		//La variable que indica si han colisionat
		bool colisio = false;

		//Numero de bales que te
		int cBales = 0;

		//Level camera
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		//While application is running
		while (!colisio)
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

			//Mou el tank
			//tank.AjustarVelocitat();
			tank.move(tileSet);


			for (int i = 0; i < cBales; i++)
			{
				if (bala[i].moveBala(tileSet, tank))
					colisio = true;
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);


			//Render level
			for (int i = 0; i < TOTAL_TILES; ++i)
			{
				tileSet[i]->render(camera);
			}

			//Render el tank
			tank.render(degrees, flipType, angle);
			dolentProva.render(0, flipType, 180, tank);


			if (shoot)
			{
				if (cBales > 0)
				{
					if (bala[cBales - 1].getTemps() > TIEMPO_DE_VIDA)
					{
						bala.push_back(Bala());
						cBales++;
						bala[cBales - 1].ObtenirDades(angle, tank);
					}
				}
				else
				{

					bala.push_back(Bala());
					cBales++;
					bala[cBales - 1].ObtenirDades(angle, tank);
				}
				
			}

			for (int i = 0; i < cBales; i++)
			{
				if (bala[i].ControlaBales())
				{
					for (int j = i; j < cBales - 1; j++)
					{
						bala[j] = bala[j + 1];
					}
					bala.erase(bala.begin() + (cBales-1));
					cBales--;
				}
			}

			//Renderitza totes les bales
			for (int i = 0; i<cBales; i++)
				bala[i].renderBala(degrees, flipType, angle, tank);



			//Update screen
			SDL_RenderPresent(gRenderer);
		}
		//bala[0].renderExplosio(tank);
		setExplosions(tank.getTankBox().x, tank.getTankBox().y);
		Sleep(1500);
	}

	//Free resources
	close(tileSet);

	return superat;
}