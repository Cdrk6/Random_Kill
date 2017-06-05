#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Texture {
  public:
	Texture(SDL_Texture*, int, int, SDL_Renderer*); //Image based texture
	Texture(string, TTF_Font*, SDL_Renderer*); //Text based texture
	~Texture();
	void free(); //Deallocates texture
        void setText(string);
	void setColor(Uint8, Uint8, Uint8); //Set color modulation (RGB)
	void setBlendMode(SDL_BlendMode); //Set blending
	void setAlpha(Uint8); //Set alpha modulation
	void render(int, int, SDL_Rect*, double, SDL_Point*, SDL_RendererFlip rf = SDL_FLIP_NONE); //Renders texture at given point
	void render(int, int, SDL_Rect* = NULL);
	int getWidth(); //Gets image width
	int getHeight(); //Gets image height

  private:
	SDL_Renderer* gRenderer;
	SDL_Texture* mTexture; //The hardware texture
	TTF_Font *gFont;
	int mWidth; //Largeur image
	int mHeight; //Hauteur image
};

#endif /* TEXTURE_HPP */
