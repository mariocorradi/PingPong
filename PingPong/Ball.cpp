#include "Ball.h"
#include <random>
#include <iostream>
using namespace std;

Ball::Ball(SDL_Renderer* renderer, int x, int y, int w, int h, int gameWIDTH, int gameHeight, int velocita)
	:LTexture(renderer, x, y, w, h, gameWIDTH, gameHeight),
	_Velocity(velocita)
{
	//Decido randomicamente la velocita della palla
	loadMedia(Score1, to_string(_PunteggioPlayer1));
	loadMedia(Score2, to_string(_PunteggioPlayer2));
	RestartGame();
	loadFromFile("Assets/ball.png");
	_ConteggioRacchetta = 0;
	leftColpito = false;
	rightColpito = false;
}


Ball::~Ball()
{
	free();
	//Da rivedere
	/*for (size_t i = 0; i < 3; i++)
	{
		if (ElementiGrafici[i].Texture != NULL)
		{
			SDL_DestroyTexture(ElementiGrafici[i].Texture);
			ElementiGrafici[i].Texture = NULL;
		}
	}*/
	TTF_CloseFont(gFont);
	gFont = NULL;
	TTF_Quit();
	_Velocity = 0;
	_VelocityOnX = 0;
	_VelocityOnY = 0;
}

void Ball::Move()
{
	if (_PositionX < 0)
	{
		/*cout << "Game Restart \n";*/
		//Restart The game
		RestartGame();
		_PunteggioPlayer2++;
		UpdatePunteggio();
		leftColpito = false;
		rightColpito = false;
	}
	if (_PositionX > _GameWidth)
	{
		RestartGame();
		_PunteggioPlayer1++;
		UpdatePunteggio();
		leftColpito = false;
		rightColpito = false;
	}
	if (_ConteggioRacchetta == 4)
	{
		_ConteggioRacchetta = 0;
		IncrementVelocity(_VelocityOnX);
		IncrementVelocity(_VelocityOnY);
	}
	_PositionY += _VelocityOnY;
	_PositionX += _VelocityOnX;
	_BallRect.y = _PositionY;
	_BallRect.x = _PositionX;

}



void Ball::CheckCollision(SDL_Rect * collisionsRect, SDL_Rect* othercollisionRect)
{
	if (_PositionY < 16 || _PositionY + _Height > _GameHeight - 16)
	{
		_VelocityOnY = -_VelocityOnY;
	}

	if (checkCollision(othercollisionRect[0])) {
		leftColpito = false;
		if (rightColpito)
		{

		}
		else {
			rightColpito = true;
			if (_VelocityOnY > 0)
			{
				_VelocityOnY = -_VelocityOnY;
			}
			else if (_VelocityOnY == 0)
			{
				_VelocityOnY = _VelocityOnX;
			}
			_VelocityOnX = -_VelocityOnX;
		}

	}
	else if (checkCollision(othercollisionRect[2]))
	{
		leftColpito = false;
		if (rightColpito)
		{

		}
		else {
			rightColpito = true;
			if (_VelocityOnX < 0)
			{
				_VelocityOnY = -_VelocityOnY;
			}
			if (_VelocityOnY == 0)
			{
				_VelocityOnY = -_VelocityOnX;
			}
			_VelocityOnX = -_VelocityOnX;
		}
	}
	else if (checkCollision(othercollisionRect[1]))
	{
		leftColpito = false;
		if (rightColpito)
		{

		}
		else {
			rightColpito = true;
			_VelocityOnX = -_VelocityOnX;
		}
	}

	if (checkCollision(collisionsRect[0])) {
		rightColpito = false;
		if (leftColpito)
		{

		}
		else {
			leftColpito = true;
			if (_VelocityOnY > 0)
			{
				_VelocityOnY = -_VelocityOnY;
			}
			else if (_VelocityOnY == 0)
			{
				_VelocityOnY = _VelocityOnX;
			}
			_VelocityOnX = -_VelocityOnX;
		}
	}
	else if (checkCollision(collisionsRect[2]))
	{
		rightColpito = false;
		if (leftColpito)
		{

		}
		else {
			leftColpito = true;
			if (_VelocityOnX < 0)
			{
				_VelocityOnY = -_VelocityOnY;
			}
			if (_VelocityOnY == 0)
			{
				_VelocityOnY = -_VelocityOnX;
			}
			_VelocityOnX = -_VelocityOnX;
		}
	}
	else if (checkCollision(collisionsRect[1]))
	{
		rightColpito = false;
		if (leftColpito);
		else {
			leftColpito = true;
			_VelocityOnX = -_VelocityOnX;
		}
	}

}

void Ball::RestartGame()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(-1, 1);

	do
	{
		_FVelocityOnX = dist(mt);
		_FVelocityOnY = dist(mt);
		_VelocityOnY = _Velocity *_FVelocityOnY;
		_VelocityOnX = _Velocity * _FVelocityOnX;
	} while (_VelocityOnY == 0 || _VelocityOnX == 0);
	_PositionX = _GameWidth / 2 - 8;
	_PositionY = _GameHeight / 2 - 8;
	_BallRect = { _PositionX,_PositionY,_Width,_Height };
}

int Ball::Direction() const
{
	if (_VelocityOnX < 0)return -1;
	else {
		return 1;
	}
}

TextureStruct* Ball::GetTextureTTF(ElementiGraficiEnum Enumeratore)
{
	return &ElementiGrafici[Enumeratore];
}

bool Ball::loadMedia(ElementiGraficiEnum enumeratore, std::string renderText)
{
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Assets/lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255, 255 };
		ElementiGrafici[enumeratore] = loadFromRenderedText(renderText, textColor);

	}

	return success;
}

void Ball::UpdatePunteggio()
{
	SDL_Color textColor = { 255, 255, 255 };
	ElementiGrafici[Score1] = loadFromRenderedText(to_string(_PunteggioPlayer1), textColor);
	ElementiGrafici[Score2] = loadFromRenderedText(to_string(_PunteggioPlayer2), textColor);

}

bool Ball::CheckIFSomeoneWin()
{
	if (_PunteggioPlayer1 == 2)
	{
		SDL_Color textColor = { 255, 255, 255 };

		ElementiGrafici[Score1] = loadFromRenderedText("Player 1 ha vinto", textColor);

		return true;
	}
	else if (_PunteggioPlayer2 == 2)
	{
		SDL_Color textColor = { 255, 255, 255 };

		ElementiGrafici[Score1] = loadFromRenderedText("Player 2 ha vinto", textColor);

		return true;
	}
	return false;
}

int Ball::GetTextWidth(ElementiGraficiEnum Enum) const
{
	return ElementiGrafici[Enum].Width;
}

int Ball::GetTextHeight(ElementiGraficiEnum Enum) const
{
	return ElementiGrafici[Enum].Height;
}

bool Ball::checkCollision(SDL_Rect collisionRect)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect Collision
	leftA = collisionRect.x;
	rightA = collisionRect.x + collisionRect.w;
	topA = collisionRect.y;
	bottomA = collisionRect.y + collisionRect.h;

	//Calculate the sides of rect Ball
	leftB = _BallRect.x;
	rightB = _BallRect.x + _BallRect.w;
	topB = _BallRect.y;
	bottomB = _BallRect.y + _BallRect.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}
	_ConteggioRacchetta++;
	return true;
}

void Ball::IncrementVelocity(int & velocity)
{
	if (velocity > 0)
		velocity++;
	else
		velocity--;
}

void Ball::RenderText(int x, int y, TextureStruct* textureStruct)
{
	SDL_Rect SrcR;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = textureStruct->Width;
	SrcR.h = textureStruct->Height;

	SDL_Rect Dest;
	Dest.x = x;
	Dest.y = y;
	Dest.w = textureStruct->Width;
	Dest.h = textureStruct->Height;


	SDL_RenderCopy(_WindowRenderer, textureStruct->Texture, &SrcR, &Dest);
}


