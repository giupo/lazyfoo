/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;


int main( int argc, char* args[] ){
  if(!init()) {
    close();
    return 1;
  }

  if (!loadMedia()) {
    close();
    return 2;
  }


  SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
  SDL_UpdateWindowSurface(gWindow);
  SDL_Delay(5000);
  
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

bool loadMedia() {
  std::string image_path("media/hello_world.bmp");
  gHelloWorld = SDL_LoadBMP(image_path.c_str());  
  if(gHelloWorld == NULL) {
    std::cerr << "Unable to load image " << image_path.c_str() << ", ";
    std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void close() {
  if(gHelloWorld != NULL) {
    SDL_FreeSurface(gHelloWorld);
  }

  if(gWindow != NULL) {
    SDL_DestroyWindow(gWindow);
  }

  SDL_Quit();
}
