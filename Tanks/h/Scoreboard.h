#include "HUD.h"

struct score
{
	string Name;
	int Value;
};

const int MAX_SCORE_LINES = 10;
const int MAX_NAME_CHAR = 15;
const char SCB_FILE[] = "res/Scoreboard.scb";

class Scoreboard
{
public:
	Scoreboard() {};
	~Scoreboard() {};

	void retriveScoreFromFile();
	void newScore(int punts);
	bool ShowScoreboard();

private:
	score scoreArray[MAX_SCORE_LINES];

	void initScoreArray();
	void saveToFile();
	int isBestScore(int punts);
	void moveArray(int posicio);
	void fillArray(score &player, int punts);
	bool returnEvent(SDL_Event*ev);
};

const int X_RET = 585;
const int Y_RET = 690;

const int MargeX = 100;
const int MargeY = 100;

const int Y_TXT = 100;
const int Y_INPUT = 530;
const int Y_POINTS = 265;