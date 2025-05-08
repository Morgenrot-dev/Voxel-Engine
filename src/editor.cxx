#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>


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

  SDL_GLContext glContext = SDL_GL_CreateContext(win);

  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(win);

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
