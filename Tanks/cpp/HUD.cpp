#include "../h/HUD.h"

bool hudInit(bool success){

	if (!gVidaTexture.loadFromFile("res/hud_vida.png"))
	{
		printf("Failed to load hud_vida texture!\n");

		success = false;
	}

	return success;
}

void hudRender(int vides, int punts)
{
	gVidaTexture.render(X_VIDES, Y_VIDES);
 
	SDL_Color textColor = { 50, 0, 0 };
	string puntString = "PUNTS: " + to_string(punts);
	gTextTexture.loadFromRenderedText(puntString, textColor);
	gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, Y_VIDES);
}