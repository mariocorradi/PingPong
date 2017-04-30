#include "Game.h"

using namespace std;


Game::Game(int screen_Width, int screen_Height)
	: SCREEN_WIDTH(screen_Width)
	, SCREEN_HEIGHT(screen_Height)

{
	_Window = NULL;
	_WindowRenderer = NULL;
	Start();

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
		_Window = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (_Window == NULL)
		{
			cout << "Errore nella CreateWindow: " << SDL_GetError();
		}
		else
		{
			//Per il Sync 
			_WindowRenderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
			//Setto il backGround
			_Background = loadTexture("Assets/background.png");
			//16 sarebbe il top del background
			_playerPaddle = make_shared<Paddle>(_WindowRenderer, 0, 160 - 30, 12, 60, SCREEN_WIDTH, SCREEN_HEIGHT, false, 4);
			_AiPaddle = make_shared<Paddle>(_WindowRenderer, SCREEN_WIDTH - 16, 160 - 30, 12, 60, SCREEN_WIDTH, SCREEN_HEIGHT, true, 2);

			_Ball = make_shared<Ball>(_WindowRenderer, SCREEN_WIDTH / 2 - 8, SCREEN_HEIGHT / 2 - 8, 14, 14, SCREEN_WIDTH, SCREEN_HEIGHT, 5);
		}
	}
	catch (const std::exception&)
	{
		cout << "Errore nella initVideo: " << SDL_GetError();
	}
}

SDL_Texture * Game::loadTexture(std::string path)
{

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(_WindowRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;

}

bool Game::Run()
{
	bool quit = false;
	bool win = false;
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
			_playerPaddle->HandleInput(e);
		}
		if (!win || quit)
		{

			//Move the paddle

			//Move the ball
			//_Ball->CheckCollision(_playerPaddle->GetCollisionRect());
			_Ball->CheckCollision(_playerPaddle->GetCollisionPaddle(), _AiPaddle->GetCollisionPaddle());

			_Ball->Move();
			_AiPaddle->Ai(_Ball->Direction(), _Ball->PosY());
			//Clear screen
			SDL_RenderClear(_WindowRenderer);
			//Render del background
			//Render texture to screen
			SDL_Rect SrcR;
			SDL_Rect DestR;

			SrcR.x = 0;
			SrcR.y = 0;
			SrcR.w = SCREEN_WIDTH;
			SrcR.h = SCREEN_HEIGHT;

			DestR.x = 0;
			DestR.y = 0;
			DestR.w = SCREEN_WIDTH;
			DestR.h = SCREEN_HEIGHT;

			SDL_RenderCopy(_WindowRenderer, _Background, &SrcR, &DestR);
			//Ball Render
			_Ball->Render(_Ball->PosX(), _Ball->PosY());

			//Player Render 
			_playerPaddle->Render(_playerPaddle->PosX(), _playerPaddle->PosY());
			_AiPaddle->Render(_AiPaddle->PosX(), _AiPaddle->PosY());
			win = _Ball->CheckIFSomeoneWin();
			if (win)
			{
				_Ball->RenderText(SCREEN_WIDTH / 2 - _Ball->GetTextWidth(_Ball->Score1) / 2, SCREEN_HEIGHT / 2 - _Ball->GetTextHeight(_Ball->Score1) / 2, _Ball->GetTextureTTF(_Ball->Score1));
			}
			else {

				_Ball->RenderText(0, 16, _Ball->GetTextureTTF(_Ball->Score1));
				_Ball->RenderText(SCREEN_WIDTH - 16, 16, _Ball->GetTextureTTF(_Ball->Score2));
			}
			//Update screen
			SDL_RenderPresent(_WindowRenderer);
			//Cursore non si vede
		}


		//std::getchar();
	}

	return quit;
}