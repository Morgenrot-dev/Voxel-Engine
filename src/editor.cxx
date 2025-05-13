#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL_video.h>
#include <iostream>
#include <SDL3/SDL.h>
//#include <GL/glu.h>
#include <glad/glad.h>


int main()
{

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL_Init failed to initialize: " << SDL_GetError() << std::endl;
  }

  SDL_GL_LoadLibrary(NULL);

  SDL_Window* win = SDL_CreateWindow("SDL Image", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if(win == nullptr) 
  {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  SDL_GLContext glContext = SDL_GL_CreateContext(win);

  int result = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

  

  if(!result)
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    SDL_DestroyWindow(win);
    SDL_Quit();
    return -1;
  }

 
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SetSwapInterval(1);
  SDL_GL_SwapWindow(win);
  
  SDL_Event e;
  bool quit = false;

  while(!quit){
  

    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_QUIT){
        quit = true;
      }



      switch(e.type)
      {
        case SDL_EVENT_WINDOW_RESIZED:
          {
          int winWidth = 0, winHeight = 0;
          SDL_GetWindowSize(win, &winWidth, &winHeight );
          glViewport(0, 0, winWidth , winHeight);
          glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          SDL_GL_SwapWindow(win);
          break;
          }
        case SDL_EVENT_KEY_DOWN:
          
          if(e.key.key == SDLK_ESCAPE)
          {
            quit = true;
          }
          

          break;
    
        default:

          break;

      }
    }
  }
  SDL_GL_UnloadLibrary();
  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(win);
  SDL_Quit();

}
