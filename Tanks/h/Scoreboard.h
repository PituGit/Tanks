#include "HUD.h"

struct score
{
	string Name;
	int Value;
};

const int MAX_SCORE_LINES = 5;
const char SCB_FILE[] = "res/Scoreboard.scb";

class Scoreboard
{
public:
	Scoreboard() {};
	~Scoreboard() {};

	void retriveScoreFromFile();
	void newScore(int punts);

private:
	score scoreArray[MAX_SCORE_LINES];

	void initScoreArray();
	void saveToFile();
	int isBestScore(int punts);
	void moveArray(int posicio);
	void fillArray(score &player, int punts);

};