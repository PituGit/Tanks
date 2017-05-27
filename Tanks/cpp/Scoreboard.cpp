#include "../h/Scoreboard.h"

bool Scoreboard::returnEvent(SDL_Event * ev)
{
	bool click = false;
	bool inside = false;

	if (ev->type == SDL_MOUSEMOTION || ev->type == SDL_MOUSEBUTTONDOWN || ev->type == SDL_MOUSEBUTTONUP)
	{
		//Obte la posicio del mouse
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x < (X_RET + MargeX) && x >(X_RET))
		{
			if (y < (Y_RET + MargeY) && y >(Y_RET))
			{
				inside = true;
			}
		}

		if (inside)
		{
			if (ev->type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_PlayChannel(-1, gClick, 0);
				click = true;
			}
		}
	}
	return click;
}

void Scoreboard::initScoreArray() {
	for (int i = 0; i < MAX_SCORE_LINES; i++)
	{
		scoreArray[i].Name = "EmptyName";
		scoreArray[i].Value = 0;
	}
}

void Scoreboard::retriveScoreFromFile() {
	ifstream scoreboard(SCB_FILE);

	if (scoreboard.fail())
	{
		printf("Error al carregar Scoreboard.scb. Inicialitzant puntuacions...\n");
		initScoreArray();
		saveToFile();
	}
	else
	{
		for (int i = 0; i < MAX_SCORE_LINES; i++)
		{
			scoreboard >> scoreArray[i].Name >> scoreArray[i].Value;
		}
	}	
}

void Scoreboard::saveToFile() {
	ofstream scoreboard;
	scoreboard.open(SCB_FILE, ofstream::trunc);

	for (int i = 0; i < MAX_SCORE_LINES; i++)
	{
		scoreboard << scoreArray[i].Name << " " << scoreArray[i].Value << endl;
	}
}

void Scoreboard::newScore(int punts) {
	int posicio = isBestScore(punts);
	if (posicio >= 0)
	{
		moveArray(posicio);
		fillArray(scoreArray[posicio], punts);

		saveToFile();
	}
}

//Comprova la posició de la puntuació introduïda en l'array del ranking
int Scoreboard::isBestScore(int punts) {
	int i = 0;
	int trobat = 0;
	do
	{
		if (punts > scoreArray[i].Value) {
			trobat = 1;
		}
		i++;
	} while ((i != MAX_SCORE_LINES) && (!trobat));
	if (trobat)
		return (i - 1); //Si està al ranking, retorna la posició
	else
		return -1; //Sinó, retorna -1
}

//Mou la resta de valors de l'array del ranking a la posició directament inferior, per tal de deixar espai a la nova puntuació
void Scoreboard::moveArray(int posicio) {
	for (int i = MAX_SCORE_LINES - 1; i > posicio; i--)
	{
		scoreArray[i].Name = scoreArray[i - 1].Name;
		scoreArray[i].Value = scoreArray[i - 1].Value;
	}
}

//Demana el nom a l'usuari per omplir el ranking amb la nova puntuació
void Scoreboard::fillArray(score &player, int punts) {
	//Event handler
	SDL_Event e;

	bool intro = false;

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 0xFF };

	//The current input text.
	std::string inputText = "Some Text";
	gTextTexture.loadFromRenderedText(inputText.c_str(), textColor);

	//Enable text input
	SDL_StartTextInput();

	while (!intro)
	{
		//The rerender text flag
		bool renderText = false;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//Special key input
			if (e.type == SDL_KEYDOWN)
			{
				//Handle backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					//lop off character
					inputText.pop_back();
					renderText = true;
				}
				//Handle copy
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				//Handle paste
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					inputText = SDL_GetClipboardText();
					renderText = true;
				}
			}
			//Special text input event
			else if (e.type == SDL_TEXTINPUT)
			{
				//Not copy or pasting
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{
					if (e.text.text[0] != ' ')
					{
						inputText += e.text.text;
						renderText = true;
					}
				}
			}
		}

		//Rerender text if needed
		if (renderText)
		{
			//Text is not empty
			if (inputText != "")
			{
				//Render new text
				gTextTexture.loadFromRenderedText(inputText.c_str(), textColor);
			}
			//Text is empty
			else
			{
				//Render space texture
				gTextTexture.loadFromRenderedText(" ", textColor);
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gNewHighScoreRenderTexture.render(0, 0);

		//Render text textures
		gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, Y_TXT);

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	//Disable text input
	SDL_StopTextInput();
}

bool Scoreboard::ShowScoreboard() {
	SDL_Event ev;
	bool returnEvent = false;
	bool quit = false;

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gScoreboardRenderTexture.render(0, 0);

	SDL_Color textColor;
	for (int i = 0; i < MAX_SCORE_LINES; i++)
	{
		switch (i)
		{
		case 0:
			textColor = { 255, 215, 0 };

			break;

		case 1:
			textColor = { 192, 192, 192 };

			break;

		case 2:
			textColor = { 205, 127, 50 };

			break;

		default:
			textColor = { 50, 0, 0 };

			break;
		}

		string puntString = scoreArray[i].Name + "  ---->  " + to_string(scoreArray[i].Value);
		gTextTexture.loadFromRenderedText(puntString, textColor);
		gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, Y_TXT + gTextTexture.getHeight()*i);
	}

	gOK_buttonTexture.render(X_RET, Y_RET);

	SDL_RenderPresent(gRenderer);

	while (!returnEvent && !quit) {
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT) {
				quit = true;
			}

			returnEvent = this->returnEvent(&ev);
		}
	}
	return quit;
}