#include "Paddle.h"
#include <stdio.h>
using namespace std;

/*
x sarebbe la posizione e y
w e h la grandezza
*/
Paddle::Paddle(SDL_Renderer* renderer, int x, int y, int w, int h, int gameWIDTH, int gameHeight, bool Ai, int velocity) :
	LTexture(renderer, x, y, w, h, gameWIDTH, gameHeight),
	_VelX(0),
	_VelY(0),
	_paddleWidth(w),
	_Ai(Ai),
	PADDLE_VEL(velocity)
{

	_VelY = PADDLE_VEL;
	loadFromFile("Assets/paddle.png");
}

//Da rivedere
Paddle::~Paddle()
{
	free();
	_VelY = 0;
	PADDLE_VEL = 0;
}

void Paddle::SetImage(SDL_Texture *texture)
{
	_Texture = texture;
}

int Paddle::GetHeight() const
{
	return LTexture::GetHeight();
}

int Paddle::GetWidth() const
{
	return LTexture::GetWidth();
}

int Paddle::PosY()
{
	return LTexture::PosY();
}

int Paddle::PosX()
{
	return LTexture::PosX();
}

void Paddle::Ai(int direction, int y)
{
	if (direction < 0)
	{
		if (_PositionY > _GameHeight / 2 - _Height / 2)
			_PositionY -= _VelY;
		else if (_PositionY < _GameHeight / 2 - _Height / 2)
		{
			_PositionY += _VelY;
		}
	}
	else {
		if (_PositionY > y)
		{
			_PositionY -= _VelY;
		}
		else if (_PositionY < y)
		{
			_PositionY += _VelY;
		}
	}
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
			/*cout << "Posizione Y Prima Up" << _PositionY << "\n";*/
			_PositionY -= _VelY;
			/*cout << "Posizione Y" << _PositionY << "\n";*/
			if (!InsideScreenY())
				_PositionY += _VelY;
			break;
		case SDLK_DOWN:
			_PositionY += _VelY;
			if (!InsideScreenY())
				_PositionY -= _VelY;
			break;
			/*	case SDLK_LEFT:
					_PositionX -= PADDLE_VEL;
					if (!InsideScreenX())
						_PositionX += PADDLE_VEL;
					break;
				case SDLK_RIGHT:
					_PositionX += PADDLE_VEL;
					if (!InsideScreenX())
						_PositionX -= PADDLE_VEL;
					break;*/
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

SDL_Rect * Paddle::GetCollisionPaddle()
{
	_CollisionPaddle[0] = { _PositionX,_PositionY,_paddleWidth,_Height / 3 };
	_CollisionPaddle[1] = { _PositionX,_PositionY + _Height / 3,_paddleWidth,_Height / 3 };
	_CollisionPaddle[2] = { _PositionX,_PositionY + (_Height / 3) * 2,_paddleWidth,_Height / 3 };
	return _CollisionPaddle;
}

bool Paddle::InsideScreenY()
{

	if (_PositionY<16 || _PositionY + _Height > _GameHeight - 16)
		return false;
	return true;
}

bool Paddle::InsideScreenX()
{
	if (_PositionX<0 || _PositionX + _Width > _GameWidth / 2)
		return false;
	return true;
}
