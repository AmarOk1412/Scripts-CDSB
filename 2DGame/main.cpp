#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Perso.h"


void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

int startSDL()
{
  int rv = EXIT_SUCCESS;
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    logSDLError(std::cout, "SDL_Init");
    rv = EXIT_FAILURE;
  }  
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
    logSDLError(std::cout, "IMG_Init");
    rv = EXIT_FAILURE;
  }
  return rv;
}


int main( int argc, char* args[] )
{  
  int rv = EXIT_SUCCESS;
  //Start SDL
  rv = startSDL();
  if(rv != EXIT_SUCCESS)
    return EXIT_FAILURE;
  
  //create window
  SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (window == nullptr){
    logSDLError(std::cout, "SDL_CreateWindow");
    rv = EXIT_FAILURE;
  }
  
  //create renderer
  SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr){
    logSDLError(std::cout, "SDL_CreateRenderer");
    rv = EXIT_FAILURE;
  }
  
  //create Perso
  Perso perso(ren);
  
  SDL_Event e;
  bool quit = false;
  
  while(!quit)
  {
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT)
        quit = true;
      if(e.type == SDL_KEYDOWN)
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = true;
            break;
          case SDLK_LEFT:
            perso.moveRight(false);
            break;
          case SDLK_RIGHT:
            perso.moveRight(true);
            break;
          case SDLK_UP:
            perso.setJumpTrue();
            break;
          case SDLK_DOWN:
            perso.moveDown();
            break;
        }
    }
    perso.jump();
    SDL_RenderClear(ren);
    perso.render();
    SDL_RenderPresent(ren);
  }
  
  perso.~Perso();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return rv;
}
