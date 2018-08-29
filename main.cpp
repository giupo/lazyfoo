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

enum KeyPressSurfaces
  {
   KEY_PRESS_SURFACE_DEFAULT,
   KEY_PRESS_SURFACE_UP,
   KEY_PRESS_SURFACE_DOWN,
   KEY_PRESS_SURFACE_LEFT,
   KEY_PRESS_SURFACE_RIGHT,
   KEY_PRESS_SURFACE_TOTAL
  };

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

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

  gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

  while(!quit) {
    while(SDL_PollEvent(&e) != 0) {
      if(e.type == SDL_QUIT) {
	quit = true;
      } else if (e.type == SDL_KEYDOWN) {
	switch( e.key.keysym.sym ) {
	case SDLK_UP:
	  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
	  break;
	case SDLK_DOWN:
	  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
	  break;
	case SDLK_LEFT:
	  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
	  break;
	case SDLK_RIGHT:
	  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
	  break;
	default:
	  gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
	  break;
	}
      }
    }
    
    SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
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
  for(int i=0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    if(gKeyPressSurfaces[i] != NULL) {
      SDL_FreeSurface(gKeyPressSurfaces[i]);
      gKeyPressSurfaces[i] = NULL;
    }
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
  if( loadedSurface == NULL ) {
    std:: cerr <<  "Unable to load image " << path.c_str();
    std:: cerr << " SDL Error: "<< SDL_GetError() << std::endl;
  }
  
  return loadedSurface;
}

bool loadMedia() {
  //Load default surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "media/press.bmp" );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL ) {
    std::cerr << "Failed to load default image!" << std::endl;
    return false;
  }
  
  //Load up surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "media/up.bmp" );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL ) {
    std::cerr << "Failed to load up image!" << std::endl;
    return false;
  }
  
  //Load down surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "media/down.bmp" );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL ) {
    std::cerr << "Failed to load down image!" << std::endl;
    return false;
  }
  
  //Load left surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "media/left.bmp" );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL ) {
    std::cerr << "Failed to load left image!" << std::endl;
    return false;
  }
  
  //Load right surface
  gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "media/right.bmp" );
  if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL ) {
    std::cerr << "Failed to load right image!" << std::endl;
    return false;
  }
  
  return true;
}
