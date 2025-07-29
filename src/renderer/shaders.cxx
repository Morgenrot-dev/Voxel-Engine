#include "../../includes/renderer/shaders.hpp"



VertexShader::VertexShader()
{
  
}

VertexShader::VertexShader(std::string& fileDirectory)
{
  
  std::ifstream vertexShaderFile(fileDirectory);

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

  glShaderSource(vertexShaderID, numberOfShaders, &vertexShaderCodeCstring, NULL);

  glCompileShader(vertexShaderID);

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

VertexShader::~VertexShader()
{
  glDeleteShader(vertexShaderID);
}

//------------------------------------------------ Fragment Shader Class start ------------------------------------------------

FragmentShader::FragmentShader()
{

}

FragmentShader::FragmentShader(std::string& fileDirectory)
{

  std::ifstream fragmentShaderFile(fileDirectory);

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

  glShaderSource(fragmentShaderID, numberOfShaders, &fragmentShaderCodeCstring, NULL);

  glCompileShader(fragmentShaderID);
  
  {
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
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

FragmentShader::~FragmentShader()
{
  glDeleteShader(fragmentShaderID);
}

//------------------------------------------------------ Shader Class Start -----------------------------------------------------------------

ShaderProgram::ShaderProgram()
{
  
}

ShaderProgram::ShaderProgram(std::string &vertexShaderLocation, std::string &fragmentShaderLocation)
{

  fileFragShader = FragmentShader(fragmentShaderLocation);
  fileVertShader = VertexShader(vertexShaderLocation);

  shaderProgramID = glCreateProgram();
    
  
}

unsigned int ShaderProgram::getShaderProgramID() const
{
  return shaderProgramID;
}

void ShaderProgram::setUniformBool(std::string& uniformName, bool inputBool) const
{

  glUniform1i(glGetUniformLocation(shaderProgramID, uniformName.c_str()), (int)inputBool);

}

void ShaderProgram::setUniformInteger(std::string& uniformName, int inputInterger) const
{

  glUniform1i(glGetUniformLocation(shaderProgramID, uniformName.c_str()), inputInterger);

}

void ShaderProgram::setUniformFloat(std::string& uniformName, float inputFloat) const
{

  glUniform1f(glGetUniformLoaction(shaderProgramID, uniformName.c_str()), inputFloat);

}
void ShaderProgram::use()
{
  glUseProgram(shaderProgramID);
}
