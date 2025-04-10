#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include <iostream>
#include <SDL3/SDL.h>
int main()
{

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win = SDL_CreateWindow("SDL Image", 640, 480, 0);
  if(win == nullptr) 
  {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer* ren = SDL_CreateRenderer(win, NULL);
  if(ren == nullptr)
  {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(win);
    return 1;
  }

  SDL_Surface* bmp = SDL_LoadBMP("Lettuce.bmp");
  if(bmp == nullptr)
  {
    std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;
  }

  SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
  SDL_DestroySurface(bmp);

  if(tex == nullptr)
  {
    std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;

  }

  SDL_Event e;
  bool quit = false;

  while(!quit){
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_QUIT){
        quit = true;
      }
    }
  }




}
