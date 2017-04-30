#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
struct TextureStruct {
	SDL_Texture* Texture;
	int Width;
	int Height;
};

class LTexture
{
	

public:

	LTexture(SDL_Renderer* renderer, int x, int y, int w, int h, int gameWIDTH, int gameHeight);
	~LTexture();
	//Loads image at specified path
	bool loadFromFile(std::string path);
	
	//Deallocates texture
	void free();
	
	TextureStruct loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Gets image dimensions
	int GetWidth() const;
	int GetHeight() const;
	int GetTextWidth() const;
	int GetTextHeight() const;
	int PosY() const;
	int PosX() const;
	SDL_Rect GetCollisionRect();
	void Render(int x, int y);
protected:
	TTF_Font *gFont = NULL;
	SDL_Texture* _Texture;
	SDL_Texture* _TextTexture;
	SDL_Renderer* _WindowRenderer;
	//Image dimensions
	int _Width, _Height;
	//Text dimensions
	int _TextWidth, _TextHeight;
	//Position
	int _PositionX, _PositionY;
	//Game Grandezza
	int _GameWidth, _GameHeight;

};

