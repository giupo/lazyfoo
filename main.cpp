/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
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
SDL_Surface* gStretchedSurface = NULL;

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

    SDL_Rect stretchedRect;
    stretchedRect.x = 0;
    stretchedRect.y = 0;
    stretchedRect.w = SCREEN_WIDTH;
    stretchedRect.h = SCREEN_HEIGHT;

    SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchedRect);
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
  if(gStretchedSurface == NULL) {
    SDL_FreeSurface(gStretchedSurface);
  }
  
  if(gWindow != NULL) {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
  }

  SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
  //Load image at specified path
  SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
  if (loadedSurface == NULL) {
    std:: cerr <<  "Unable to load image " << path.c_str();
    std:: cerr << " SDL Error: "<< SDL_GetError() << std::endl;
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
  gStretchedSurface = loadSurface("media/stretch.bmp");
  if(gStretchedSurface == NULL) {
    std::cerr << "Failed to load stretching image!" << std::endl;
    return false;
  }

  return true;
}
