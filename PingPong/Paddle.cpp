#include "Paddle.h"
/*
x sarebbe la posizione e y
w e h la grandezza
*/
Paddle::Paddle(SDL_Renderer* renderer, int x, int y, int w, int h, int gameWIDTH, int gameHeight) :
	_WindowRenderer(renderer),
	_positionX(x),
	_positionY(y),
	_width(w),
	_height(h),
	_VelX(0),
	_VelY(0),
	_GameWidth(gameWIDTH),
	_GameHeight(gameHeight)
{
	Init();

	_Texture = loadTexture("Assets/paddle.png");
}

//Da rivedere
Paddle::~Paddle()
{

	SDL_DestroyTexture(_Texture);
	_Texture = NULL;
	_width = 0;
	_height = 0;
	//Quit SDL subsystems
	IMG_Quit();

}

void Paddle::SetImage(SDL_Texture *texture)
{
	_Texture = texture;
}

void Paddle::Render(int x, int y)
{
	SDL_Rect SrcR;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = _width;
	SrcR.h = _height;

	SDL_Rect Dest;
	Dest.x = x;
	Dest.y = y;
	Dest.w = _width;
	Dest.h = _height;


	SDL_RenderCopy(_WindowRenderer, _Texture, &SrcR, &Dest);
}

int Paddle::GetHeight()
{
	return _height;
}

int Paddle::GetWidth()
{
	return _width;
}

int Paddle::PosY()
{
	return _positionY;
}

int Paddle::PosX()
{
	return _positionX;
}

void Paddle::HandleInput(SDL_Event &event)
{
	//If a key was pressed
	if (event.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			_positionY -= PADDLE_VEL;
			if(!InsideScreenY())
				_positionY += PADDLE_VEL;
			break;
		case SDLK_DOWN:
			_positionY += PADDLE_VEL;
			if (!InsideScreenY())
				_positionY -= PADDLE_VEL;
			break;
		case SDLK_LEFT:
			_positionX -= PADDLE_VEL;
			if (!InsideScreenX())
				_positionX += PADDLE_VEL;
			break;
		case SDLK_RIGHT:
			_positionX += PADDLE_VEL;
			if (!InsideScreenX())
				_positionX -= PADDLE_VEL;
			break;
		}
	}

	/*
	Andra implementata con i frame
	*/

	////If a key was released
	//else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	//{
	//	//Adjust the velocity
	//	switch (event.key.keysym.sym)
	//	{
	//	case SDLK_UP: _VelY += PADDLE_VEL; break;
	//	case SDLK_DOWN: _VelY -= PADDLE_VEL; break;
	//	case SDLK_LEFT: _VelX += PADDLE_VEL; break;
	//	case SDLK_RIGHT: _VelX -= PADDLE_VEL; break;
	//	}
	//}
}

void Paddle::Move()
{
	//Muovo la racchetta X
	_positionX += _VelX;
	if ((_positionX < 0) || _positionX + _width > _GameWidth)
	{
		_positionX -= _VelX;
	}

	//Muovo la racchetta Y
	_positionY -= _VelY;
	if ((_positionY < 16) || (_positionY + _height) > (_GameHeight - _height / 2))
	{
		_positionY -= _VelY;
	}
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

bool Paddle::InsideScreenY()
{

	if (_positionY<16 || _positionY + _height > _GameHeight-16)
		return false;
	return true;
}

bool Paddle::InsideScreenX()
{
	if (_positionX<0 || _positionX + _width > _GameWidth/2)
		return false;
	return true;
}
