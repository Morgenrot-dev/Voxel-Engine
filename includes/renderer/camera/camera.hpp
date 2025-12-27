#pragma once
#include <glm/glm.hpp>
using namespace glm;
class Camera {
public:
  Camera(vec3 position, vec3 lookat, vec3 upvector);
  mat4 getTransformationMatrix();
  void setPosition(vec3 position);
  void setLookat(vec3 lookat);
  void setLookat(float pitch, float yaw);
private:
  glm::vec3 position;
  glm::vec3 lookat;
  glm::mat4 transformation_matrix;
};

