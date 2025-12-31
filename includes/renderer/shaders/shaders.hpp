#ifndef SHADERS_HPP
#define SHADERS_HPP


#define SHADER_FILE_NOT_FOUND 1
#define SHADER_COMPILATION_ERROR 2
#define SHADER_FAILURE 3
#define SHADER_SUCCESS 0

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <unistd.h>
#include <glm/glm.hpp>

class VertexShader 
{
  public:
    VertexShader();
    VertexShader(const std::string& fileDirectory);
    ~VertexShader(); 
    unsigned int getShaderID() const;
    short getErrorNumber() const;
    void deleteShader();
  private:
    std::string shaderFile;
    short errorNumber = 0;
    unsigned int vertexShaderID = 0;
    unsigned int numberOfShaders = 1;
};

class FragmentShader
{
  public:
    FragmentShader();
    FragmentShader(const std::string& fileDirectory);
    ~FragmentShader();  
    unsigned int getShaderID() const;
    short getErrorNumber() const;
    void deleteShader();
  private:
    std::string shaderFile;
    short errorNumber = 0;
    unsigned int fragmentShaderID = 0;
    unsigned int numberOfShaders = 1;
};

class ShaderProgram
{
  public:
    ShaderProgram();
    ShaderProgram(const std::string& vertexShaderLocation, const std::string& fragmentShaderLocation);
    ~ShaderProgram();
  unsigned int getShaderProgramID() const;
  void setUniformBool(const std::string& uniformName, bool inputBool) const;
  void setUniformInteger(const std::string& uniformName, int inputInteger) const;
  void setUniformFloat(const std::string& uniformName, float inputFloat) const;
  void setUniformVec3(const std::string& uniformName, glm::vec3 vector);
  short getError() const;
  void use();

  private:
  short errorNumber = SHADER_SUCCESS;
  FragmentShader fileFragShader;
  VertexShader fileVertShader;
  unsigned int shaderProgramID = 0;

};

#endif
