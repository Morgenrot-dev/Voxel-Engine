#ifndef SHADERS_HPP
#define SHADERS_HPP

#define SHADER_FILE_NOT_FOUND 1
#define SHADER_COMPILATION_ERROR 2
#define SHADER_SUCCESS 0

#include <iostream>
#include <sstream>
#include <string>
#include <GL/glew.h>

class VertexShader 
{
  public:
    VertexShader();
    VertexShader(std::string& fileDirectory);
    ~VertexShader();
    unsigned int getShaderID() const;
    short getErrorNumber() const;
  private:
    std::string shaderFile;
    short errorNumber = 0;
    unsigned int vertexShaderID;
    unsigned int numberOfShaders = 0;
};

class FragmentShader
{
  public:
    FragmentShader();
    FragmentShader(std::string& fileDirectory);
    ~FragmentShader();
    unsigned int getShaderID() const;
    short getErrorNumber() const;
  private:
    std::string shaderFile;
    short errorNumber = 0;
    unsigned int fragmentShaderID;
    unsigned int numberOfShaders = 0;
};

class ShaderProgram
{
  public:
    ShaderProgram();
    ShaderProgram(std::string& vertexShaderLocation, std::string& fragmentShaderLocation);
    ~ShaderProgram();
  unsigned int getShaderProgramID() const;
  void setUniformBool(std::string& uniformName, bool inputBool) const;
  void setUniformInteger(std::string& uniformName, int inputInteger) const;
  void setUniformFloat(std::string& uniformName, float inputFloat) const;
  void use();

  private:
  FragmentShader fileFragShader;
  VertexShader fileVertShader;
  unsigned int shaderProgramID = 0;

};

#endif
