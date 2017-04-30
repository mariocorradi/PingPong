#pragma once
#include "LTexture.h"
#include <string>
class Ball :
	public LTexture
{

public:
	enum ElementiGraficiEnum
	{
		Score1 = 1,
		Score2 = 2,
		Message = 3
	};

	Ball(SDL_Renderer* renderer, int x, int y, int w, int h, int gameWIDTH, int gameHeight, int velocita);
	~Ball();
	void Move();

	void CheckCollision(SDL_Rect* collisionsRect, SDL_Rect* othercollisionRect);
	void RestartGame();
	int Direction() const;
	TextureStruct* GetTextureTTF(ElementiGraficiEnum Enumeratore);
	void RenderText(int x, int y, TextureStruct* textureStruct);
	bool CheckIFSomeoneWin();
	int GetTextWidth(ElementiGraficiEnum Enum) const;
	int GetTextHeight(ElementiGraficiEnum Enum) const;
private:
	bool loadMedia(ElementiGraficiEnum Enum, std::string renderText);
	void UpdatePunteggio();
	bool checkCollision(SDL_Rect collisionRect);
	void IncrementVelocity(int& velocity);
	bool leftColpito, rightColpito;
	//Collisione palla
	//Velocita
	int _Velocity;
	//Velocita Su X
	int _VelocityOnX;
	//Velocita Su Y
	int _VelocityOnY;
	//If this number get to 5 the ball will move faster
	int _ConteggioRacchetta;

	float _FVelocityOnX;
	//Velocita Su Y
	float _FVelocityOnY;
	//

	int _PunteggioPlayer1 = 0;

	int _PunteggioPlayer2 = 0;

	SDL_Rect _BallRect;


	TextureStruct ElementiGrafici[3];


};

