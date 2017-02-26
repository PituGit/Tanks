/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, strings, and file streams

#include "Main.h"


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Scene textures

SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}


#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


void Tile::render(SDL_Rect& camera)
{
	//If the tile is on screen
	if (checkCollision(camera, mBox))
	{
		//Show the tile
		gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
	}
}

Tile::Tile(int x, int y, int tileType)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}


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

Tank::Tank()
{
	//Initialize the collision box
	TankBox.x = 400;
	TankBox.y = 500;
	TankBox.w = Tank_WIDTH;
	TankBox.h = Tank_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

int Tank::getVelocitatX()
{
	return mVelX;
}

int Tank::getVelocitatY()
{
	return mVelY;
}

SDL_Rect Tank::getTankBox()
{
	return TankBox;
}

void Tank::handleEvent(SDL_Event& e, SDL_Event* a, double& angle, SDL_Rect& camera, bool& shoot)
{
	//Si hi ha algun envent del mouse

	//Get la posicio del mouse
	int x, y;
	SDL_GetMouseState(&x, &y);
	//Calcula l'angle de rotació, per imprimirlo apuntant al mouse
	if ((x - TankBox.x) != 0)
		angle = atan((double(y - TankBox.y)) / double(x - TankBox.x));
	angle *= 57.3;
	if ((x - TankBox.x) < 0)
		angle += 180;

	//Si s'ha apretat el botó del ratoli
	if (a->type == SDL_MOUSEBUTTONDOWN)
	{
		shoot = true;
	}

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= Tank_VEL; break;
		case SDLK_DOWN: mVelY += Tank_VEL; break;
		case SDLK_LEFT: mVelX -= Tank_VEL; break;
		case SDLK_RIGHT: mVelX += Tank_VEL; break;
		}

	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += Tank_VEL; break;
		case SDLK_DOWN: mVelY -= Tank_VEL; break;
		case SDLK_LEFT: mVelX += Tank_VEL; break;
		case SDLK_RIGHT: mVelX -= Tank_VEL; break;
		}
	}

}


void Tank::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (TankBox.x + Tank_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (TankBox.y + Tank_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Tank::render(float degrees, SDL_RendererFlip flipType, double angle)
{
	//Centre de rotació del tanc
	SDL_Point centre = { Meitat_CapsulaX, Meitat_CapsulaY };
	SDL_Point* center = &centre;
	//Mostra el tank
	gBaseTankTexture.render(TankBox.x, TankBox.y, NULL, degrees, center, flipType);
	//Angle en el que apunta
	degrees = angle;
	centre = { Meitat_CapsulaX, Meitat_CapsulaY - 4 };
	gCapsulaTexture.render(TankBox.x, TankBox.y + 4, NULL, degrees, center, flipType);
}


void Tank::move( Tile *tiles[] )
{
    //Move the dot left or right
    TankBox.x += mVelX;

    //If the dot went too far to the left or right or touched a wall
    if( ( TankBox.x < 0 ) || ( TankBox.x + Tank_WIDTH > LEVEL_WIDTH ) || touchesWall( TankBox, tiles ) )
    {
        //move back
        TankBox.x -= mVelX;
    }

    //Move the dot up or down
    TankBox.y += mVelY;

    //If the dot went too far up or down or touched a wall
    if( ( TankBox.y < 0 ) || ( TankBox.y + Tank_HEIGHT > LEVEL_HEIGHT ) || touchesWall( TankBox, tiles ) )
    {
        //move back
        TankBox.y -= mVelY;
    }
}

Bala::Bala()
{
	//Initialize the collision box
	BalaBox.x = 400;
	BalaBox.y = 500;
	BalaBox.w = Bala_WIDTH;
	BalaBox.h = Bala_HEIGHT;

	//Initialize the velocity
	Vel = 10;
}

void Bala::render(float degrees, SDL_RendererFlip flipType, double angle)
{
	degrees = angle;
	gBalaTexture.render(mPosX, mPosY, NULL, degrees, NULL, flipType);
}

void Bala::move(Tile *tiles[])
{
	//Move the dot left or right
	BalaBox.x += cos(Vel);

	//If the dot went too far to the left or right or touched a wall
	if ((BalaBox.x < 0) || (BalaBox.x + Bala_WIDTH > LEVEL_WIDTH) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.x -= cos(Vel);
	}

	//Move the dot up or down
	BalaBox.y += sin(Vel);

	//If the dot went too far up or down or touched a wall
	if ((BalaBox.y < 0) || (BalaBox.y + Bala_HEIGHT > LEVEL_HEIGHT) || touchesWall(BalaBox, tiles))
	{
		//move back
		BalaBox.y -= sin(Vel);
	}
}



bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia( Tile* tiles[] )
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gBaseTankTexture.loadFromFile( "39_tiling/Base_tank.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	
	if (!gCapsulaTexture.loadFromFile("39_tiling/Capsula&Cano_tank.png"))
	{
		printf("Failed to load capsula texture!\n");
		success = false;
	}

	if (!gBalaTexture.loadFromFile("39_tiling/Bala.png"))
	{
		printf("Failed to load capsula texture!\n");
		success = false;
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile( "39_tiling/tiles.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	return success;
}

void close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] == NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

	//Free loaded images
	gBaseTankTexture.free();
	gTileTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool setTiles( Tile* tiles[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "39_tiling/lazy.map" );

	//Initialize the tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		//Determines what kind of tile will be made
		int tileType = -1;

		//Read tile from map file
		map >> tileType;

		//If the was a problem in reading the map
		if( map.fail() )
		{
			//Stop loading map
			printf( "Error loading map: Unexpected end of file!\n" );
			tilesLoaded = false;
			break;
		}

		//If the number is a valid tile number
		if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
		{
			tiles[ i ] = new Tile( x, y, tileType );
		}
		//If we don't recognize the tile type
		else
		{
			//Stop loading map
			printf( "Error loading map: Invalid tile type at %d!\n", i );
			tilesLoaded = false;
			break;
		}

		//Move to next tile spot
		x += TILE_WIDTH;

		//If we've gone too far
		if( x >= LEVEL_WIDTH )
		{
			//Move back
			x = 0;

			//Move to the next row
			y += TILE_HEIGHT;
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_RED ].x = 0;
			gTileClips[ TILE_RED ].y = 0;
			gTileClips[ TILE_RED ].w = TILE_WIDTH;
			gTileClips[ TILE_RED ].h = TILE_HEIGHT;

			gTileClips[ TILE_GREEN ].x = 0;
			gTileClips[ TILE_GREEN ].y = 80;
			gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
			gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

			gTileClips[ TILE_BLUE ].x = 0;
			gTileClips[ TILE_BLUE ].y = 160;
			gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
			gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPLEFT ].x = 80;
			gTileClips[ TILE_TOPLEFT ].y = 0;
			gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_LEFT ].x = 80;
			gTileClips[ TILE_LEFT ].y = 80;
			gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMLEFT ].x = 80;
			gTileClips[ TILE_BOTTOMLEFT ].y = 160;
			gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOP ].x = 160;
			gTileClips[ TILE_TOP ].y = 0;
			gTileClips[ TILE_TOP ].w = TILE_WIDTH;
			gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

			gTileClips[ TILE_CENTER ].x = 160;
			gTileClips[ TILE_CENTER ].y = 80;
			gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
			gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOM ].x = 160;
			gTileClips[ TILE_BOTTOM ].y = 160;
			gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPRIGHT ].x = 240;
			gTileClips[ TILE_TOPRIGHT ].y = 0;
			gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_RIGHT ].x = 240;
			gTileClips[ TILE_RIGHT ].y = 80;
			gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
			gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
			gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= TILE_CENTER ) && ( tiles[ i ]->getType() <= TILE_TOPLEFT ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];

		//Load media
		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
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

			//The tank that will be moving around on the screen
			Tank tank;

			//Les bales que es pintaran per pantalla
			std::vector <Bala> bala(N);

			//Variable per saber si s'ha disparat
			bool shoot = false;

			//Numero de bales
			int cBales = 0;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Gestiona les dades introduides
					tank.handleEvent( e, &e, angle, camera, shoot);
				}
				CalcularGraus(degrees, tank);

				//Mou el tank i camera
				tank.move( tileSet);
				tank.setCamera( camera );

				if (shoot)
				{
					cBales++;

				}
					

				//Mou cada una de les bales
				for (int i = 0; i < cBales; i++)
				{
					bala[i].move(tileSet);
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}
				//Render tank
				tank.render( degrees, flipType, angle);


				//Renderitza totes les bales
				for(int i=0; i<cBales; i++)
					bala[i].render(degrees, flipType, angle);
				
				
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
		
		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}