#pragma once
#include "paddle.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>
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

	SDL_Texture* _Background;
	
	std::shared_ptr<Paddle> _playerPaddle;
};

