#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include "AI.h"

class GameManager {

public:
	//Screen dimension constants
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;
	const int FRAME_RATE = 60;

	//Starts up SDL and creates window
	bool init();

	//Frees media and shuts down SDL
	void close();

	static GameManager* Instance();
	//Handle SDLEvents
	void pollEvents();

	void Render();

	bool quit;


private:

	static GameManager* sInstance;

	GameManager();
	~GameManager();

	Timer* mTimer;

	Player* mPlayer1;
	Player* mPlayer2;

	AI* mAI;

	Ball* mBall;

	SDL_Texture* mTexture;
	TTF_Font* gFont = NULL;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	SDL_Renderer* gRenderer = NULL;

	const Uint8* currentKeyStates;

	//Loads image at specified path
	bool loadFromFile(std::string textureText, SDL_Color textColor);

	//Renders texture at given point
	void textRender(int x, int y);
	//Renders All textures and Geometry
	void CreateRect();
};