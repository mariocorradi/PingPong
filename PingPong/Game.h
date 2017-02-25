#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class Game
{
public:
	Game(int screen_Width, int screen_Height);
	virtual ~Game();
	bool Run();
private:
	void Start();
	SDL_Texture* loadTexture(std::string path);

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	
	//La finestra dove faro il rendering
	SDL_Window* _Window;

	SDL_Renderer* _WindowRenderer;

	SDL_Texture* cursoreMouse=nullptr;
	SDL_Texture* cursoriMouse[8];
};

