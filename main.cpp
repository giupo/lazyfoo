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

SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;


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
 
    SDL_RenderClear( gRenderer );
    //Render texture to screen
    SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
    //Update screen
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


SDL_Texture* loadTexture(std::string path) {
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  if(loadedSurface == NULL) {
    std::cerr << "Unable to load image: " << path.c_str();
    std::cerr << ", SDL Error: " << SDL_GetError() << std::endl;
    return NULL;
  }

  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
  if (newTexture == NULL) {
    std::cerr << "Unable to create texture from " << path.c_str();
    std::cerr << ", SDL Error: " << SDL_GetError() << std::endl;
  }

  SDL_FreeSurface(loadedSurface);
  return newTexture;
}

void close() {
  if(gTexture != NULL) {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
  }

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
  gTexture = loadTexture("media/texture.png");
  if(gTexture == NULL) {
    std::cerr << "Failed to load PNG image!" << std::endl;
    std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}
