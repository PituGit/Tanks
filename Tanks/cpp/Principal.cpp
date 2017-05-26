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
		gWindow = SDL_CreateWindow("The TANKS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

				//Initialize SDL_mixer
				if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	
	//Icona de la finestra
	SDL_Surface *icon; 
	icon = IMG_Load("res/Icon32.png");
	SDL_SetWindowIcon(gWindow, icon);
	SDL_FreeSurface(icon);

	//Cursor personalitzat
	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);

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

	gMenuSong = Mix_LoadMUS("res/MenuSong.wav");
	if (gMenuSong == NULL)
	{
		printf("Failed to load Menu music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gClick = Mix_LoadWAV("res/Click.wav");
	if (gClick == NULL)
	{
		printf("Failed to load Click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
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

	//Free the sound effects
	Mix_FreeChunk(gClick);
	gClick = NULL;
	
	//Free the music
	Mix_FreeMusic(gMenuSong);
	gMenuSong = NULL;

	//Quit SDL subsystems
	Mix_Quit();
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
			if (e->type == SDL_MOUSEBUTTONDOWN) {
				Mix_HaltMusic();
				Mix_PlayChannel(-1, gClick, 0);
				jugar = true;
			}
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

	Scoreboard scoreboard;
	scoreboard.retriveScoreFromFile();

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
			Mix_PlayMusic(gMenuSong, -1);

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
					Sleep(500);
					while (vides > 0 && !quit)
					{
						superat = joc(quit, vides, punts);
						scoreboard.newScore(punts);
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