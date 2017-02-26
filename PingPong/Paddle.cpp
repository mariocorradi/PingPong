#include "Paddle.h"

Paddle::Paddle(SDL_Renderer* renderer, int x, int y, int w, int h) :
	_WindowRenderer(renderer),
	_positionX(x),
	_positionY(y),
	_width(w),
	_height(h)
{
	Init();
	_position = { _positionX,_positionY,_width,_height };
	_Texture = loadTexture("Assets/paddle.png");
}

//Da rivedere
Paddle::~Paddle()
{

	SDL_DestroyTexture(_Texture);
	_Texture = NULL;
	//Quit SDL subsystems
	IMG_Quit();

}

void Paddle::SetImage(SDL_Texture *texture)
{
	_Texture = texture;
}

void Paddle::Render()
{
	SDL_RenderCopy(_WindowRenderer, _Texture,NULL, &_position);
}

SDL_Texture * Paddle::loadTexture(std::string path)
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

void Paddle::Init()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();

	}
}
