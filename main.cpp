/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gPNG_Surface = NULL;

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

    SDL_BlitSurface(gPNG_Surface, NULL, gScreenSurface, NULL);
    SDL_UpdateWindowSurface(gWindow);
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
  } else {
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface( gWindow );
  }
  
  return true;
}

void close() {
  if(gPNG_Surface == NULL) {
    SDL_FreeSurface(gPNG_Surface);
  }
  
  if(gWindow != NULL) {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
  }

  SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if (loadedSurface == NULL) {
    std:: cerr <<  "Unable to load image " << path.c_str();
    std:: cerr << " SDL Error: "<< IMG_GetError() << std::endl;
    return NULL;
  }

  SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface,
						     gScreenSurface->format,
						     NULL);

  if (optimizedSurface == NULL) {
    std::cerr << "Unable to optimize image " << path.c_str();
    std::cerr << " SDL Error: " << SDL_GetError();
  }

  SDL_FreeSurface(loadedSurface);
  
  return optimizedSurface;
}

bool loadMedia() {
  gPNG_Surface = loadSurface("media/loaded.png");
  if(gPNG_Surface == NULL) {
    std::cerr << "Failed to load PNG image!" << std::endl;
    return false;
  }

  return true;
}
