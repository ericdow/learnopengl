#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

// Defines several possible options for camera movement. 
// Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

// Default camera values
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;

class Camera {
 public:
  // Camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;
  // Camera options
  GLfloat MovementSpeed;
  GLfloat MouseSensitivity;
  GLfloat Zoom;

  // Constructor with vectors
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : 
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), 
    MouseSensitivity(SENSITIVTY), Zoom(ZOOM) {
    this->Position = position;
    this->WorldUp = up;
    this->updateCameraVectors(0.0, {0.0, 0.0, 0.0});
  }
  // Constructor with scalar values
  Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, 
    GLfloat upZ) : 
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), 
    MouseSensitivity(SENSITIVTY), Zoom(ZOOM) {
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->updateCameraVectors(0.0, {0.0, 0.0, 0.0});
  }

  // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
  glm::mat4 GetViewMatrix() {
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
  }

  // Processes input received from any keyboard-like input system. Accepts input 
  // parameter in the form of camera defined ENUM (to abstract it from windowing 
  // systems)
  void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
    GLfloat velocity = this->MovementSpeed * deltaTime;
    if (direction == FORWARD)
      this->Position += this->Front * velocity;
    if (direction == BACKWARD)
      this->Position -= this->Front * velocity;
    if (direction == LEFT)
      this->Position -= this->Right * velocity;
    if (direction == RIGHT)
      this->Position += this->Right * velocity;
  }

  // Processes input received from a mouse input system. Expects the offset 
  // value in both the x and y direction.
  void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, 
    GLboolean constrainPitch = true) {
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    // TODO
    // if (constrainPitch) {
    //   if (this->Pitch > 89.0f)
    //     this->Pitch = 89.0f;
    //   if (this->Pitch < -89.0f)
    //     this->Pitch = -89.0f;
    // }

    glm::vec3 axis = glm::cross(Front - Position, Up);
    axis = glm::normalize(axis);

    // Update Front, Right and Up Vectors using the updated Eular angles
    updateCameraVectors(glm::radians(yoffset), axis);
    updateCameraVectors(glm::radians(-xoffset), {0.0, 1.0, 0.0});
  }

  // Processes input received from a mouse scroll-wheel event. Only requires 
  // input on the vertical wheel-axis
  void ProcessMouseScroll(GLfloat yoffset) {
    if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
      this->Zoom -= yoffset;
    if (this->Zoom <= 1.0f)
      this->Zoom = 1.0f;
    if (this->Zoom >= 45.0f)
      this->Zoom = 45.0f;
  }

 private:
  // Calculates the front vector from the Camera's (updated) Eular Angles
  void updateCameraVectors(GLfloat angle, glm::vec3 axis) {
    glm::quat tmp, quat_view, result;
    tmp.x = axis.x * sin(angle/2);
    tmp.y = axis.y * sin(angle/2);
    tmp.z = axis.z * sin(angle/2);
    tmp.w = cos(angle/2);

    quat_view.x = Front.x;
    quat_view.y = Front.y;
    quat_view.z = Front.z;
    quat_view.w = 0.0;
  
    result = tmp * quat_view * glm::conjugate(tmp);
  
    Front.x = result.x;
    Front.y = result.y;
    Front.z = result.z;
     
    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you
    // look up or down which results in slower movement.
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  
    this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
  }
};
