/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

//Scrxoeen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

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

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer ); 
    //Render red filled quad
    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );        
    SDL_RenderFillRect( gRenderer, &fillRect );

    //Draw blue horizontal line
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
    SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 ) {
      SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
    }

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
  return true;
}
