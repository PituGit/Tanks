#include "../h/Principal.h"

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	if (!gPlay_game_buttonTexture.loadFromFile("res/Play_game_button.png"))
	{
		printf("Failed to load Play_game_button texture!\n");

		success = false;
	}

	if (!gGame_OverTexture.loadFromFile("res/Game_Over.png"))
	{
		printf("Failed to load Game Over texture!\n");

		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gTextTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool HandleEvent(SDL_Event* e)
{
	bool jugar = false;
	bool inside = false;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Obte la posicio del mouse
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x<(PosicioXBoto + MargeX) && x>(PosicioXBoto))
		{
			if (y<(PosicioYBoto + MargeY) && y>(PosicioYBoto))
			{
				inside = true;
			}
		}
		if (inside)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
				jugar = true;
		}
	}
	return jugar;
}

int main(int argc, char* args[])
{
	//vides amb les que es comença
	int vides = 3;

	//Punts inicials
	int punts = 0;

	//Si se supera el nivell
	bool superat;

	//Si es vol començar a jugar
	bool jugar = false;

	//Tancar l'aplicacio
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Faile to load media");
		}
		else
		{
			while (!quit && vides>0)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
						quit = true;

					jugar=HandleEvent(&e);

				}

				if (jugar)
				{
					while (vides > 0 && !quit)
					{
						superat = joc(quit, vides, punts);
						if (!superat)
							vides--;
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
								quit = true;
							
						}
					}
					
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gPlay_game_buttonTexture.render(PosicioXBoto, PosicioYBoto);

				SDL_RenderPresent(gRenderer);
			}

			if (vides == 0)
			{
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gGame_OverTexture.render(LEVEL_WIDTH / 4, LEVEL_HEIGHT / 4);

				SDL_RenderPresent(gRenderer);

				Sleep(2000);
			}
		}
		
	}
	close();
	return 0;
}