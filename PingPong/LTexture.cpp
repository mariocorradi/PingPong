#include "LTexture.h"



LTexture::LTexture(SDL_Renderer* renderer, int x, int y, int w, int h, int gameWIDTH, int gameHeight) :
	_WindowRenderer(renderer),
	_PositionX(x),
	_PositionY(y),
	_Width(w),
	_Height(h),
	_GameWidth(gameWIDTH),
	_GameHeight(gameHeight)
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		
	}
}


LTexture::~LTexture()
{
	SDL_DestroyTexture(_Texture);
	_Texture = NULL;
	_Width = 0;
	_Height = 0;
	_PositionX = 0;
	_PositionY = 0;
	//Quit SDL subsystems
	IMG_Quit();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture


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
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(_WindowRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_Width = loadedSurface->w;
			_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	_Texture = newTexture;
	return _Texture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (_Texture != NULL)
	{
		SDL_DestroyTexture(_Texture);
		_Texture = NULL;
		_Width = 0;
		_Height = 0;
	}
}




TextureStruct LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	TextureStruct result;
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		result.Texture = SDL_CreateTextureFromSurface(_WindowRenderer, textSurface);
		if (_TextTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			result.Width = textSurface->w;
			result.Height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return result;
}

int LTexture::GetWidth() const
{
	return _Width;
}

int LTexture::GetHeight() const
{
	return _Height;
}

int LTexture::GetTextWidth() const
{
	return _TextWidth;
}

int LTexture::GetTextHeight() const
{
	return _TextHeight;
}

int LTexture::PosY() const
{
	return _PositionY;
}

int LTexture::PosX() const
{
	return _PositionX;
}

SDL_Rect LTexture::GetCollisionRect()
{
	return SDL_Rect{ _PositionX,_PositionY,_Width,_Height };
}

void LTexture::Render(int x, int y)
{
	SDL_Rect SrcR;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = _Width;
	SrcR.h = _Height;

	SDL_Rect Dest;
	Dest.x = x;
	Dest.y = y;
	Dest.w = _Width;
	Dest.h = _Height;


	SDL_RenderCopy(_WindowRenderer, _Texture, &SrcR, &Dest);
}


