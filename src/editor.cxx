#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_time.h"
#include "SDL3/SDL_timer.h"
#include <cstddef>
#include <iostream>
#include <SDL3/SDL.h>
#include "../includes/renderer/shaders/shaders.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
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

  if(!result)
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    SDL_DestroyWindow(win);
    SDL_Quit();
    return -1;
  }

  float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
}; 

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  //Vertex Buffer Object
  //Used to load Vertex pos data onto the gpu
  unsigned int VBO;
  glGenBuffers(1,&VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0); 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);

  ShaderProgram current("resources/shader.vs", "resources/shader.fs");
  int width, height, nrChannels;
  unsigned char* data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
  glActiveTexture(GL_TEXTURE0);
  unsigned int textureID;
  if(data){
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

      }
  else 
  {
    std::cerr << "Failed to load texture" << std::endl;
    return -1;
  }
  stbi_image_free(data);
  unsigned int smileTextID;
  stbi_set_flip_vertically_on_load(true);
  data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);

  glActiveTexture(GL_TEXTURE1);
  if(data)
  {
    glGenTextures(1, &smileTextID);
    glBindTexture(GL_TEXTURE_2D, smileTextID); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    std::cerr << "Failed to load texture" << std::endl;
    return -1;
  }
  /*
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
  */

  //Sets the attributes of the vertex data
  //Meaning how the program should interpret the vertex values inputed
  /*
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
  */
  
  //The next part of the lesson is learn about Vertex Array Objects (VAOs)
  //The problem they solve is the cumbersome nature of binding configuring and executing 
  //VBO data. Instead utilizing the VAO we can save the states of the VBOs and reuse them 
  //at a later date or set them all up at once to use later.   
  
  

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  current.use();
  current.setUniformInteger("ourTexture", 0);
  current.setUniformInteger("ourTexture1", 1);
  //glUseProgram(shaderProgram);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SetSwapInterval(-1);
  SDL_GL_SwapWindow(win);
  
  SDL_Event e;
  bool quit = false;

  while(!quit){
    
    current.use();
    //glUseProgram(shaderProgram);
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(win);
    SDL_Delay(1);

  }
  SDL_GL_UnloadLibrary();
  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(win);
  SDL_Quit();

}
