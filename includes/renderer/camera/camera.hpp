#pragma once
#include <glm/glm.hpp>
using namespace glm;
class Camera {
public:
  Camera(vec3 position, vec3 lookat, vec3 upvector);
  mat4 getTransformationMatrix();
  void setPosition(vec3 position);
  void moveCamera(vec3 moveVector, float delta);
  void setSpeed(float speedSet);
  void setLookat(vec3 lookat);
  void setLookat(float pitch, float yaw);
  vec3 getLookat();
  vec3 getPosition();
  float getSpeed();
private:
  float speed = 1.0f;
  glm::vec3 position;
  glm::vec3 lookat;
  glm::vec3 upvector;
  glm::mat4 transformation_matrix;
};

