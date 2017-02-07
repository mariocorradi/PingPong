#include "Game.h"
using namespace std;


Game::Game(int screen_Width, int screen_Height)
	: SCREEN_WIDTH(screen_Width)
	, SCREEN_HEIGHT(screen_Height)
{
	_Window = NULL;
	_WindowRenderer = NULL;
}

Game::~Game()
{
	//Destroy window	
	SDL_DestroyRenderer(_WindowRenderer);
	SDL_DestroyWindow(_Window);
	_Window = NULL;
	_WindowRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}

void Game::Start()
{
	try
	{
		SDL_Init(SDL_INIT_VIDEO);
		_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (_Window == NULL)
		{
			cout << "Errore nella CreateWindow: " << SDL_GetError();
		}
		else
		{
			_WindowRenderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_ACCELERATED);
			if (_WindowRenderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error:" << SDL_GetError();

			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(_WindowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();

				}
			}
		}
	}
	catch (const std::exception&)
	{
		cout << "Errore nella initVideo: " << SDL_GetError();
	}
}

bool Game::Run()
{
	bool quit = false;
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_RenderClear(_WindowRenderer);

		//Render texture to screen
		//SDL_RenderCopy(_WindowRenderer, gTexture, NULL, NULL);

		//Update screen
		SDL_RenderPresent(_WindowRenderer);
		//std::getchar();
	}

	return quit;
}