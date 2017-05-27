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

	gFont = TTF_OpenFont("res/font.ttf", 40);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	if (!gPlay_game_buttonTexture.loadFromFile("res/Play_game_button.png"))
	{
		printf("Failed to load Play_game_button texture!\n");

		success = false;
	}

	if (!gMenuRenderTexture.loadFromFile("res/MenuRender.png"))
	{
		printf("Failed to load MenuRender texture!\n");

		success = false;
	}

	if (!gScoreboard_buttonTexture.loadFromFile("res/Scoreboard_button.png"))
	{
		printf("Failed to load Scoreboard_button texture!\n");

		success = false;
	}

	if (!gOK_buttonTexture.loadFromFile("res/OK_button.png"))
	{
		printf("Failed to load OK_button texture!\n");

		success = false;
	}

	if (!gGameOverRenderTexture.loadFromFile("res/GameOverRender.png"))
	{
		printf("Failed to load GameOverRender texture!\n");

		success = false;
	}

	if (!gScoreboardRenderTexture.loadFromFile("res/ScoreboardRender.png"))
	{
		printf("Failed to load ScoreboardRender texture!\n");

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

	gMenuRenderTexture.free();
	gPlay_game_buttonTexture.free();
	gScoreboard_buttonTexture.free();
	gOK_buttonTexture.free();
	gGameOverRenderTexture.free();
	gScoreboardRenderTexture.free();

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

int HandleEvent(SDL_Event* e)
{
	int boto = CAP;
	int inside = CAP;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Obte la posicio del mouse
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x < (X_PLAY + MargeX) && x > (X_PLAY))
		{
			if (y < (Y_PLAY + MargeY) && y > (Y_PLAY))
			{
				inside = PLAY;
			}
		}

		if (x < (X_SCB + MargeX) && x > (X_SCB))
		{
			if (y < (Y_SCB + MargeY) && y > (Y_SCB))
			{
				inside = SCORE;
			}
		}

		switch (inside)
		{
		case PLAY:
			if (e->type == SDL_MOUSEBUTTONDOWN) {
				Mix_HaltMusic();
				Mix_PlayChannel(-1, gClick, 0);
				boto = PLAY;
			}

			break;

		case SCORE:
			if (e->type == SDL_MOUSEBUTTONDOWN) {
				Mix_PlayChannel(-1, gClick, 0);
				boto = SCORE;
			}
			break;

		default:
			break;
		}
	}
	return boto;
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
	int boto = CAP;

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
					boto = HandleEvent(&e);

					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				switch (boto)
				{
				case PLAY:
					Sleep(500);
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

					break;

				case SCORE:
					quit = scoreboard.ShowScoreboard();
					Sleep(100);

					break;

				default:
					break;
				}


				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gMenuRenderTexture.render(0, 0);
				gPlay_game_buttonTexture.render(X_PLAY, Y_PLAY);
				gScoreboard_buttonTexture.render(X_SCB, Y_SCB);

				SDL_RenderPresent(gRenderer);
			}

			if (vides == 0)
			{
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gGameOverRenderTexture.render(0,0);

				SDL_RenderPresent(gRenderer);

				scoreboard.newScore(punts);

				//Sleep(2000);
			}

		}
		
	}
	close();
	return 0;
}