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

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win = SDL_CreateWindow("SDL Image", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if(win == nullptr) 
  {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  int result = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

  std::cout << result << std::endl;
  /*{
    std::cout << "Failed to initialize GLAD" << std::endl;
    SDL_DestroyWindow(win);
    SDL_Quit();
    return -1;
  }*/

  SDL_GLContext glContext = SDL_GL_CreateContext(win);

  glClearColor(1,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);
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
          glClearColor(1,0,0,1);
          glClear(GL_COLOR_BUFFER_BIT);
          break;
          }


        default:

          break;

      }
    }
  }

  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(win);


}
