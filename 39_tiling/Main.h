#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>


//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

const int Meitat_CapsulaX = 21;
const int Meitat_CapsulaY = 23;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Màxim de bales
const int N = 20;

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType);

	//Shows the tile
	void render(SDL_Rect& camera);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

private:
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
};

class Tank
{
public:
	//The dimensions of the dot
	static const int Tank_WIDTH = 55;
	static const int Tank_HEIGHT = 45;

	//Maximum axis velocity of the dot
	static const int Tank_VEL = 5;

	//Initializes the variables
	Tank();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e, SDL_Event* a, double& angle, SDL_Rect& camera, bool& shoot);

	//Moves the dot and check collision against tiles
	void move(Tile *tiles[]);

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);

	//Shows the dot on the screen
	void render(float degrees, SDL_RendererFlip flipType, double angle);

	//Obté dades del tanc
	int getVelocitatX();
	int getVelocitatY();

	SDL_Rect getTankBox();

private:
	//The X and Y offsets of the tank
	int mPosX, mPosY;

	//The velocity of the tank
	int mVelX, mVelY;

	SDL_Rect TankBox;
};

class Bala
{
public:
	//en realitat es 10 (amplada) x7 (altura)
	static const int Bala_WIDTH = 10;
	static const int Bala_HEIGHT = 10;

	Bala();

	void move(Tile *tiles[]);

	void render(float degrees, SDL_RendererFlip flipType, double angle);

private:
	//The X and Y offsets of the bala
	int mPosX, mPosY;

	//The velocity of the bala
	int Vel;

	//Temps de la bala
	float Temps, TempsFinal;

	SDL_Rect BalaBox;

};


SDL_Renderer* gRenderer = NULL;

LTexture gBalaTexture;
LTexture gBaseTankTexture;
LTexture gCapsulaTexture;
LTexture gTileTexture;