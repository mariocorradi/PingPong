#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class Paddle
{
public:

	Paddle(SDL_Renderer* renderer, int x, int y, int w, int h,int gameWIDTH,int gameHeight);
	~Paddle();
	void SetImage(SDL_Texture * texture);
	void Render(int x, int y);
	int GetHeight();
	int GetWidth();
	int PosY();
	int PosX();
	
	//Gestisce gli input del paddle
	void HandleInput(SDL_Event &event);
	void Move();

private:
	SDL_Texture* loadTexture(std::string path);
	//Windows renderer
	SDL_Renderer* _WindowRenderer;
	//Texture per il paddle
	SDL_Texture* _Texture;


	//Per le inizializzazioni
	void Init();
	//Funzione per controllare se la racchetta esce sulle Y
	bool InsideScreenY();
	//Funzione per controllare se la racchetta esce sulle Y
	bool InsideScreenX();
	//Position
	int _positionX, _positionY;
	//Sprite altezza larghezza
	int _width, _height;
	//Velocita su x e y
	int _VelX, _VelY;

	int _GameWidth, _GameHeight;

	static const int PADDLE_VEL = 10;
};

