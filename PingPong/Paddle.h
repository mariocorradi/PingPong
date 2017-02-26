#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class Paddle
{
public:
	Paddle(SDL_Renderer* renderer,int x, int y, int w, int h);
	~Paddle();
	void SetImage(SDL_Texture * texture);
	void Render();
private:
	SDL_Texture* loadTexture(std::string path);
	//Windows renderer
	SDL_Renderer* _WindowRenderer;
	//Texture per il paddle
	SDL_Texture* _Texture;
	SDL_Rect _position;
	
	//Per le inizializzazioni
	void Init();

	//Position
	int _positionX, _positionY;
	//Sprite altezza larghezza
	int _width, _height;
};

