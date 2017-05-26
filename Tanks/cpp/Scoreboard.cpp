#include "../h/Scoreboard.h"

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
	system("CLS");
	printf("Entra el teu nom (fins a 14 caracters):\n");

	scanf_s("%s", player.Name, 15);
	player.Value = punts;

	printf("\nResultat entrat al ranking.\n");
	Sleep(1000);
}