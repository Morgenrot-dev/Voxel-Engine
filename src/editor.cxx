#include <glad/glad.h>
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_time.h"
#include "SDL3/SDL_timer.h"
#include <cstddef>
#include <iostream>
#include <SDL3/SDL.h>
//#include <GL/glu.h>
#include <cmath>

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

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

  if(!result)
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    SDL_DestroyWindow(win);
    SDL_Quit();
    return -1;
  }

  float vertices[] = {
     0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
    0.0f, 0.5f, 0.0f,  0.0, 0.0f, 1.0f// bottom left 
  };

  
  
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  //Vertex Buffer Object
  //Used to load Vertex pos data onto the gpu
  unsigned int VBO;
  glGenBuffers(1,&VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  
  //GPU program in charge of the pixel positions
  const char * vertexShaderSource = "#version 450 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos, 1.0);\n"
    " ourColor = aColor;"
    "}\0";

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  {
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
  }

  const char * fragmentShaderSource = "#version 450 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(ourColor, 1.0);\n"
    "}\0";

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  {
    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success){
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
  }
  
  

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  //Sets the attributes of the vertex data
  //Meaning how the program should interpret the vertex values inputed
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0); 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  {
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILURE" << infoLog << std::endl;
    }
  }

  
  //The next part of the lesson is learn about Vertex Array Objects (VAOs)
  //The problem they solve is the cumbersome nature of binding configuring and executing 
  //VBO data. Instead utilizing the VAO we can save the states of the VBOs and reuse them 
  //at a later date or set them all up at once to use later. 
  


  

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glUseProgram(shaderProgram);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  SDL_GL_SetSwapInterval(-1);
  SDL_GL_SwapWindow(win);
  
  SDL_Event e;
  bool quit = false;

  while(!quit){
    
    glUseProgram(shaderProgram);
    int winWidth = 0, winHeight = 0;
    SDL_GetWindowSize(win, &winWidth, &winHeight );
    glViewport(0, 0, winWidth , winHeight);
    glClearColor(1,0,0,1);

    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_QUIT){
        quit = true;
      }
      
      
      
      

      switch(e.type)
      {
        case SDL_EVENT_WINDOW_RESIZED:
          {
          
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

    glBindVertexArray(VAO);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(win);
    SDL_Delay(1);

  }
  SDL_GL_UnloadLibrary();
  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(win);
  SDL_Quit();

}
