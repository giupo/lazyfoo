#include "texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

LTexture::LTexture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
  free();
}

bool LTexture::loadFromFile(std::string path) {
  SDL_Texture* newTexture = NULL;
  SDK_Surface* loadedSurface = IMG_Load(path.c_str());
  if( NULL == loadedSurface ) {
    std::cerr << "Unable to load image " << path.c_str();
    std::cerr << ", SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }
  SDL_SetColorKey( loadedSurface, SDL_TRUE,
		   SDL_MapRGP( loadedSurface->format, 0, 0xFF, 0xFF));
  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

  if (NULL == newTexture) {
    std::cerr << "Unable to create texture from " << path.c_ptr();
    std::cerr << ", SDL Error: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(loadedSurface);
    return false;
  }

  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);

  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::free() {
  if (NULL != mTexture) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::render(int x, int y) {
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth(){
  return mWidth;
}

int LTexture::getHeight() {
  return mHeight;
}
