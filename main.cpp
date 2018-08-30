/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


#include "texture.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gFooTexture;
LTexture gBackgroundTexture;

int main( int argc, char* args[] ){
  if(!init()) {
    close();
    return 1;
  }

  if (!loadMedia()) {
    close();
    return 2;
  }
  
  bool quit = false;
  SDL_Event e;

  while(!quit) {
    while(SDL_PollEvent(&e) != 0) {
      if(e.type == SDL_QUIT) {
	quit = true;
      }
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear( gRenderer );

    gBackgroundTexture.render(0, 0);
    gFooTexture.render(240, 190);
    
    SDL_RenderPresent( gRenderer );
  }
  
  close();
  return 0;
}

bool init() {
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
    std::cerr << "SDL_image could not initialize!";
    std::cerr << " SDL_image Error: %s\n" << IMG_GetError() << std::endl;
    return false;
  }
  //Create window
  gWindow = SDL_CreateWindow("SDL Tutorial",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     SCREEN_WIDTH,
			     SCREEN_HEIGHT,
			     SDL_WINDOW_SHOWN);

  if( gWindow == NULL ) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if(gRenderer == NULL) {
    std::cerr << "Renderer could not be created!";
    std::cerr << " SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }
  
  return true;
}



void close() {

  gFooTexture.free();
  gBackgroundTexture.free();
  
  if(gRenderer != NULL) {
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
  }
  
  if(gWindow != NULL) {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
  }
  
  IMG_Quit();
  SDL_Quit();
}


/**
 * Carica i media
 * \brief Loads media
 * \sa loadTexture
 */

bool loadMedia() {
  //Loading success flag
  bool success = true;

  //Load Foo' texture
  if( !gFooTexture.loadFromFile( "10_color_keying/foo.png" ) ) {
    std::cerr << "Failed to load Foo' texture image!" << std::endl;
    success = false;
  }
    
  //Load background texture
  if( !gBackgroundTexture.loadFromFile( "10_color_keying/background.png" ) ) {
    std::cerr << "Failed to load background texture image!" << std::endl;
    success = false;
  }
  return success;
}
