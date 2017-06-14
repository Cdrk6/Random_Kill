#include "Texture.hpp"

Texture::Texture(SDL_Texture* texture, int w, int h, SDL_Renderer* renderer) {
    gRenderer = renderer;
    mTexture = texture;
    mWidth = w;
    mHeight = h;
}

Texture::Texture(int x, int y, string txt, TTF_Font* font, SDL_Renderer* renderer) {
    gRenderer = renderer;
    gFont = font;
    mTexture = NULL;
    setText(txt);
    render(x, y);
}

Texture::~Texture() {
    free(); //Deallocate
}

//Free texture if it exists

void Texture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::setText(string txt) {
    free(); //Get rid of preexisting texture

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, txt.c_str(), {0, 0, 0}); //Render text surface
    if (textSurface != NULL) {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface); //Create texture from surface pixels
        if (mTexture == NULL)
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
        else {
            mWidth = textSurface->w; //Get image dimensions
            mHeight = textSurface->h; //
        }
        SDL_FreeSurface(textSurface); //Get rid of old surface
    } else {
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
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

void Texture::render(int x, int y, int x2, int y2, int w2, int h2) {
    SDL_Rect renderQuad = getRect(x, y, w2, h2); //Set rendering space and render to screen SDL_Rect 
    SDL_Rect clip = getRect(x2, y2, w2, h2); //Set clip rendering dimensions
    SDL_RenderCopy(gRenderer, mTexture, &clip, &renderQuad); //Render to screen 
}

void Texture::render(int x, int y) {
    SDL_Rect renderQuad = getRect(x, y, mWidth, mHeight);
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad); //Render to screen 
}

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}

SDL_Rect Texture::getRect(int x, int y, int w, int h) {
    SDL_Rect rekt = {x, y, w, h};
    return rekt;
}