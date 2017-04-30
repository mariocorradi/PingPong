#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "LTexture.h"
class Paddle :public LTexture

{
public:

	Paddle(SDL_Renderer* renderer, int x, int y, int w, int h, int gameWIDTH, int gameHeight, bool Ai,int velocity);
	~Paddle();

	void SetImage(SDL_Texture * texture);

	int GetHeight() const;
	int GetWidth() const;
	int PosY();
	int PosX();
	//Position Ball
	void Ai(int direction, int y);
	//Gestisce gli input del paddle
	void HandleInput(SDL_Event &event);
	SDL_Rect * GetCollisionPaddle();
private:
	SDL_Rect _CollisionPaddle[3];
	//Funzione per controllare se la racchetta esce sulle Y
	bool InsideScreenY();
	//Funzione per controllare se la racchetta esce sulle Y
	bool InsideScreenX();

	//Velocita su x e y
	int _VelX, _VelY;
	int _paddleWidth;
	bool _Ai;
	int PADDLE_VEL;
};

