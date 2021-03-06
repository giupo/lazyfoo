#ifndef __TEXTURE__
#define __TEXTURE__

#include <SDL2/SDL.h>
#include <string>

extern SDL_Renderer* gRenderer;

class LTexture
{
public:
  //Initializes variables
  LTexture();

  //Deallocates memory
  ~LTexture();

  //Loads image at specified path
  bool loadFromFile( std::string path );

  //Deallocates texture
  void free();

  //Renders texture at given point
  void render( int x, int y );

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture* mTexture;

  //Image dimensions
  int mWidth;
  int mHeight;
};

#endif
