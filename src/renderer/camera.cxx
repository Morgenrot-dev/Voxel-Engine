#include "../../includes/renderer/camera/camera.hpp"
#include <glm/ext/matrix_transform.hpp>
using namespace glm;
Camera::Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 lookat = vec3(0.0f, 0.0f, 1.0f), vec3 upVector = vec3(0.0f, 1.0f, 0.0f)) 
{

  this->position = position;
  this->lookat = lookat;
  this->upvector = upVector;

  transformation_matrix = glm::lookAt(this->position, this->position + this->lookat, this->upvector);


}

mat4 Camera::getTransformationMatrix()
{
  return transformation_matrix;
}

void Camera::setPosition(vec3 Position)
{
  this->position = Position;
  this->transformation_matrix = lookAt(this->position,this->position + this->lookat, this->upvector);
}

void Camera::setLookat(vec3 lookat)
{
  this->lookat = normalize(lookat);
  this->transformation_matrix = lookAt(this->position, this->position + this->lookat, this->upvector);
}

void Camera::setLookat(float pitch, float yaw)
{

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  this->setLookat(glm::normalize(direction));

  this->transformation_matrix = lookAt(this->position, this->position + this->lookat, this->upvector);



}

vec3 Camera::getLookat()
{
  return this->lookat;
}

void Camera::setSpeed(float speed)
{
  this->speed = speed;
}

float Camera::getSpeed()
{
  return this->speed;
}

void Camera::moveCamera(vec3 direction, float timeDelta)
{

   position += direction * timeDelta * this->speed;

}
