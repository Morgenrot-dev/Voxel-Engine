#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_scancode.h"
#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
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
//One ought to remember about c++ scripting through the use of dll/so loading

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

  

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), 640.0f/480.0f , 0.1f , 100.0f);
  
  view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f ), glm::vec3(0.0f, 0.0f, 0.0f ), glm::vec3(0.0f, 1.0f, 0.0f));

  float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0); 
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  
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
  int modelLoc = glGetUniformLocation(current.getShaderProgramID(), "model");
  
  int viewLoc = glGetUniformLocation(current.getShaderProgramID(), "view");

  int projectionLoc = glGetUniformLocation(current.getShaderProgramID(), "projection");

  const float radius = 10.0f;

  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE , glm::value_ptr(projection));
  glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    //glUseProgram(shaderProgram);
  glEnable(GL_DEPTH_TEST);
  
  SDL_GL_SetSwapInterval(-1);
  SDL_GL_SwapWindow(win);
  
  SDL_Event e;
  bool quit = false;
  double deltaTime = 0.0f;
  double lastFrame = 0.0f;
  double currentFrame = 0.0f;
  
  float yaw = 0;
  float pitch = -90.0f;
  const float sensitivity = 0.05f;
  SDL_SetWindowRelativeMouseMode(win, true);

  while(!quit){
    
    current.use();
    //glUseProgram(shaderProgram);
    int winWidth = 0, winHeight = 0;
    SDL_GetWindowSize(win, &winWidth, &winHeight );
    glViewport(0, 0, winWidth , winHeight);
    glClearColor(1,0,0,1);
    currentFrame = SDL_GetPerformanceCounter(); 

    deltaTime = (double)(currentFrame - lastFrame) / (double) SDL_GetPerformanceFrequency();

    lastFrame = currentFrame;
  
    float cameraSpeed = 2.5f * deltaTime;

    const bool* keystate = SDL_GetKeyboardState(NULL);
    if(keystate != NULL)
    {
      if(keystate[SDL_SCANCODE_W])
      {
        cameraPos += cameraSpeed * cameraFront;
      }
      if(keystate[SDL_SCANCODE_S])
      {
        cameraPos -= cameraSpeed * cameraFront;
      }
      if(keystate[SDL_SCANCODE_A])
      {
        
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
      }
      if(keystate[SDL_SCANCODE_D])
      {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
      }
    }

    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_QUIT){
        quit = true;
      }
      
      
      
      float xoffset = 0.0f;
      float yoffset = 0.0f;

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
        case SDL_EVENT_MOUSE_MOTION:
          xoffset = e.motion.xrel;
          yoffset = -e.motion.yrel;
          xoffset *= sensitivity;
          yoffset *= sensitivity;

          yaw += xoffset;
          pitch += yoffset;

          if(pitch > 89.0f)
            pitch = 89.0f;
          if(pitch < -89.0f)
            pitch = -89.0f;

          std::cout << xoffset << '\n' << yoffset << '\n' << yaw << '\n' << pitch << '\n' << std::endl;

  
          break;
    
        default:

          break;

      }
    
      

    }
    
    glBindVertexArray(VAO);
    SDL_GL_SwapWindow(win);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);     
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE , glm::value_ptr(view));
    for(int i = 0; i < 10; i++){
    glm::mat4 new_model = glm::mat4(1.0f);
    new_model = glm::translate(new_model, cubePositions[i]);
    float angle = 20.0f * i;
    new_model = glm::rotate(new_model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(new_model));
    glDrawArrays(GL_TRIANGLES, 0, 36); 
    }
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
    
    
    SDL_Delay(16);
    
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  SDL_GL_UnloadLibrary();
  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(win);
  SDL_Quit();

}
