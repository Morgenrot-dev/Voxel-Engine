#include "../../includes/renderer/shaders/shaders.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__) 

VertexShader::VertexShader()
{
  
}

VertexShader::VertexShader(const std::string &fileDirectory)
{
  char tempbuff[512];
  getcwd(tempbuff, 512); 
  std::string tempbuffstr(tempbuff);
  std::string newfileDirectory = tempbuffstr + "/" + fileDirectory;
  std::ifstream vertexShaderFile(newfileDirectory);

  if(!vertexShaderFile.is_open()){
    std::cerr << "Error: Unable to open selected shader file" << std::endl;
    errorNumber = SHADER_FILE_NOT_FOUND;
    return;
  }

  std::stringstream vertexShaderStream;

  vertexShaderStream << vertexShaderFile.rdbuf();

  std::string vertexShaderCode = vertexShaderStream.str();

  const char* vertexShaderCodeCstring = vertexShaderCode.c_str();

  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  glCheckError();

  glShaderSource(vertexShaderID, numberOfShaders, &vertexShaderCodeCstring, NULL);
  glCheckError();

  glCompileShader(vertexShaderID);
  glCheckError();

 {
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
  } 
    

}

unsigned int VertexShader::getShaderID() const
{

  return vertexShaderID;
  
}

short VertexShader::getErrorNumber() const
{
  return errorNumber;
}
void VertexShader::deleteShader()
{
  glDeleteShader(vertexShaderID);
}
VertexShader::~VertexShader()
{
  
}

//------------------------------------------------ Fragment Shader Class start ------------------------------------------------

FragmentShader::FragmentShader()
{

}

FragmentShader::FragmentShader(const std::string &fileDirectory)
{
  char tempbuff[512];
  getcwd(tempbuff, 512);
  std::string tempbuffstr(tempbuff);
  std::string newfileDirectory = tempbuffstr + "/" + fileDirectory;
  std::ifstream fragmentShaderFile(newfileDirectory);

  if(!fragmentShaderFile.is_open())
  {
    std::cerr << "Error: Unable to open selected shader file" << std::endl;
    errorNumber = SHADER_FILE_NOT_FOUND;
    return;
  }

  std::stringstream fragmentShaderStream;

  fragmentShaderStream << fragmentShaderFile.rdbuf();

  std::string fragmentShaderString = fragmentShaderStream.str();

  const char* fragmentShaderCodeCstring = fragmentShaderString.c_str();

  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  glCheckError();

  glShaderSource(fragmentShaderID, numberOfShaders, &fragmentShaderCodeCstring, NULL);
  glCheckError();

  glCompileShader(fragmentShaderID);
  glCheckError();
  
  {
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
  } 

}

unsigned int FragmentShader::getShaderID() const
{
  return fragmentShaderID;
}

short FragmentShader::getErrorNumber() const
{
  return errorNumber;
}

void FragmentShader::deleteShader()
{
  glDeleteShader(fragmentShaderID);
}

FragmentShader::~FragmentShader()
{
  
}

//------------------------------------------------------ Shader Class Start -----------------------------------------------------------------

ShaderProgram::ShaderProgram()
{
  
}

ShaderProgram::ShaderProgram(const std::string &vertexShaderLocation, const std::string &fragmentShaderLocation)
{

  fileFragShader = FragmentShader(fragmentShaderLocation);
  fileVertShader = VertexShader(vertexShaderLocation);

  shaderProgramID = glCreateProgram();
  glCheckError();

  if(!fileVertShader.getErrorNumber() && !fileFragShader.getErrorNumber())
  {
    glAttachShader(shaderProgramID, fileFragShader.getShaderID());
    glCheckError();
    glAttachShader(shaderProgramID, fileVertShader.getShaderID());
    glCheckError();

    glLinkProgram(shaderProgramID);
    glCheckError();
    int success;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if(!success)
    {
      char infoLog[512];
      glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
  
    
  }
  else 
  {

    std::cerr << "One or More of the shader programs have failed to compile please try again" << std::endl;

  }
  
}

void ShaderProgram::setUniformBool(const std::string& uniformName, bool value) const
{
  glUniform1i(glGetUniformLocation(shaderProgramID, uniformName.c_str()), value);
}

void ShaderProgram::setUniformInteger(const std::string& uniformName, int value) const
{
  glUniform1i(glGetUniformLocation(shaderProgramID, uniformName.c_str()), value);
}

void ShaderProgram::setUniformFloat(const std::string& uniformName, float value) const
{
  glUniform1f(glGetUniformLocation(shaderProgramID, uniformName.c_str()), value);
}

void ShaderProgram::setUniformVec3(const std::string& uniformName, glm::vec3 vector)
{
  glUniform3fv(glGetUniformLocation(shaderProgramID, uniformName.c_str()), 1, glm::value_ptr(vector));
}

ShaderProgram::~ShaderProgram()
{
 

  fileVertShader.deleteShader();
  fileFragShader.deleteShader();

}

void ShaderProgram::use()
{
  glUseProgram(shaderProgramID);
}

unsigned int ShaderProgram::getShaderProgramID() const
{
  return shaderProgramID;
}

short ShaderProgram::getError() const 
{
  return errorNumber;
}

