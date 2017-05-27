#include "Texture.hpp"

Texture::Texture(SDL_Texture* texture, int w, int h, SDL_Renderer* renderer) {
    gRenderer = renderer;
    mTexture = texture;
    mWidth = w;
    mHeight = h;
}

Texture::~Texture() {
    free(); //Deallocate
}

void Texture::free() {
    //Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue); //Modulate texture rgb
}

void Texture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending); //Set blending function
}

void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha); //Modulate texture alpha
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight}; //Set rendering space
    if (clip != NULL) {
        renderQuad.w = clip->w; //Set clip rendering dimensions
        renderQuad.h = clip->h; //
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip); //Render to screen
}

/*void Texture::render(int x, int y) {
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}*/

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}