#include <iostream>
#include <memory>
#include <string>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL.h"
// GLM Mathematics
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"

// Initialize camera defintion (yay global variables...)
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f); // Camera position
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Target position
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f); // Up vector

// bool array of which keys are currently being pushed
bool keys[1024];

GLfloat deltaTime = 0.0f; // Time between current frame and last frame
GLfloat lastFrame = 0.0f;   // Time of last frame

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void do_movement();

// Window dimensions
const GLuint WIDTH = 1200, HEIGHT = 800;

// Size of the world
const float world_size = 10;

// Flag for if warp drive is engaged
bool warping = false;

// Time since warp was engaged/disengaged
float warp_start_time = 100.0f;
float warp_stop_time = -100.0f;

// FOV angles at different speeds
float fov;
const float fov_normal = 60.0f;
const float fov_warp = 160.0f;
const float fov_inc_rate = 0.8f; // rate of increase while warping

// Starting position for the mouse cursor
GLfloat lastX = WIDTH/2, lastY = HEIGHT/2;
GLfloat yaw = -90.0f, pitch = 0.0f;

std::shared_ptr<Shader> boxShader, boxShaderPhong, boxShaderGouraud;

// The MAIN function, from here we start the application and run the game loop
int main(int argc, char* argv[]) {
  // Init GLFW
  glfwInit();
  
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);

  // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
  glewExperimental = GL_TRUE;
  // Initialize GLEW to setup the OpenGL Function pointers
  glewInit();

  // Define the viewport dimensions
  glViewport(0, 0, WIDTH, HEIGHT);

  // Displacements to generate a periodic view of cubes
  int n_rep = 3; // (2*n_rep + 1)^2 total repetitions
  std::vector<glm::vec3> periodic_displacements;
  for (int i = -n_rep; i <= n_rep; i++) {
    for (int j = -n_rep; j <= n_rep; j++) {
      for (int k = -n_rep; k <= n_rep; k++) {
        periodic_displacements.push_back(
          world_size * glm::vec3(i, j, k));
      }
    }
  }

  // Set up vertex data (and buffer(s)) and attribute pointers
  GLfloat vertices[] = {
       // Positions         // Normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
  };
 
  // Set up a VBO with box coordinate data 
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Set up VAO for boxes
  GLuint boxVAO;
  glGenVertexArrays(1, &boxVAO);
  glBindVertexArray(boxVAO);
  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(1);
  glBindVertexArray(0); // Unbind VAO
  
  // Specify positions to render multiple cubes
  std::vector<glm::vec3> cubePositions = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -10.0f), 
    glm::vec3(-4.5f, -2.2f, -2.5f),  
    glm::vec3(-5.8f, -6.0f, -8.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f,  7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 7.5f,  7.0f, -5.5f), 
    glm::vec3( 3.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  4.0f,  4.5f)};

  // Set up VAO for light
	GLuint lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  // We only need to bind to the VBO, since the VBO data already contains the correct data.
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Set the vertex attributes (only position data for our light)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0); 

  // Build and compile our shader programs
  boxShaderPhong = std::make_shared<Shader>("box.vs", "box.frag");
  boxShaderGouraud = std::make_shared<Shader>("box_gouraud.vs", "box_gouraud.frag");
  boxShader = boxShaderPhong;

  // Make sure z-buffering is enabled
  glEnable(GL_DEPTH_TEST);

  // Make sure cursor is hidden and stays in window
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

  // Set callback function for mouse movement
  glfwSetCursorPosCallback(window, mouse_callback);
  
  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Compute dt from last render
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();
    do_movement();

    // Render
    // Clear the colorbuffer and depthbuffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // View transformation moves the camera to its location in the world
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // Determine the current FOV
    if (warping) {
      fov += fov_inc_rate * (currentFrame - warp_start_time);
      fov = std::min(fov_warp, fov); 
    }
    else {
      fov -= 10.0f * fov_inc_rate * (currentFrame - warp_stop_time);
      fov = std::max(fov_normal, fov); 
    }

    // Projection transformation defines the clipping frustrum
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(fov), 
      (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    
    // Update the position of the light
    glm::vec3 lightPos(cameraPos + glm::vec3(2.0f) * cameraFront);
    
    // Get transformations uniform location and set matrices for drawing boxes
    GLint modelLoc_box = glGetUniformLocation(boxShader->GetProgram(), "model");
    GLint viewLoc_box = glGetUniformLocation(boxShader->GetProgram(), "view");
    GLint projLoc_box = glGetUniformLocation(boxShader->GetProgram(), "projection");
    glUniformMatrix4fv(viewLoc_box, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc_box, 1, GL_FALSE, glm::value_ptr(projection));
    
    // Activate shader for drawing boxes and set uniforms
    boxShader->Use();       
    GLint objectColorLoc = glGetUniformLocation(boxShader->GetProgram(), "objectColor");
    GLint lightColorLoc  = glGetUniformLocation(boxShader->GetProgram(), "lightColor");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f); // Also set light's color (white) 
    
		// Send the position of the light and camera to the box fragment shader
		GLint lightPosLoc = glGetUniformLocation(boxShader->GetProgram(), "lightPos");
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    GLint viewPosLoc = glGetUniformLocation(boxShader->GetProgram(), "viewPos");
    glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
    
    // Draw boxes
    glBindVertexArray(boxVAO);
    for(GLuint i = 0; i < cubePositions.size(); i++) {
      GLfloat angle = (1.0f + 0.2f * i) * (GLfloat)glfwGetTime();
      for (GLuint p = 0; p < periodic_displacements.size(); p++) {
        // Model transformation moves the object model to its location/orientation in the world
        glm::mat4 model;
        model = glm::translate(model, cubePositions[i] + periodic_displacements[p]);
        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(modelLoc_box, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
      }
    }
    glBindVertexArray(0);
    
    // Swap the screen buffers
    glfwSwapBuffers(window);
  }
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &boxVAO);
  glDeleteVertexArrays(1, &lightVAO);
  glDeleteBuffers(1, &VBO);
  // Terminate GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
bool isWireFrame = false;
bool isPhong = true;
float last_w_press_time = -100.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  // Close by pressing escape key
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  // Update the state machine of which keys are pressed
  if(action == GLFW_PRESS)
    keys[key] = true;
  else if(action == GLFW_RELEASE)
    keys[key] = false;
  // Check for double press on W
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    float w_press_time = glfwGetTime();
    if (w_press_time - last_w_press_time < 0.2f) {
      warping = true;
      warp_start_time = glfwGetTime(); 
    }
    last_w_press_time = w_press_time;
  }
  if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
    if (warping) {
      warp_stop_time = glfwGetTime();
    }
    warping = false;
  }
  // Pressing F1 toggles wireframe mode
  if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
    if (isWireFrame) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      isWireFrame = false;
    }
    else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      isWireFrame = true;
    }
  }
  // Pressing F2 toggles Phong/Gouraud
  if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
    if (isPhong) {
      boxShader = boxShaderGouraud;
      isPhong = false;
    }
    else {
      boxShader = boxShaderPhong;
      isPhong = true;
    }
  }
}

// Update the camera position based on key presses
void do_movement() {
  GLfloat cameraSpeed = 10.0f * deltaTime; // Ensure uniform movement speed
  if(keys[GLFW_KEY_W]) {
    if (warping) {
      cameraPos += 2.0f * cameraSpeed * cameraFront;
    }
    else {
      cameraPos += cameraSpeed * cameraFront;
    }
  }
  if(keys[GLFW_KEY_S])
    cameraPos -= cameraSpeed * cameraFront;
  if(keys[GLFW_KEY_A])
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if(keys[GLFW_KEY_D])
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

  // Make the movement periodic
  if (cameraPos.x > world_size / 2)
    cameraPos.x = -world_size / 2;
  if (cameraPos.x < -world_size / 2)
    cameraPos.x = world_size / 2;
  if (cameraPos.y > world_size / 2)
    cameraPos.y = -world_size / 2;
  if (cameraPos.y < -world_size / 2)
    cameraPos.y = world_size / 2;
  if (cameraPos.z > world_size / 2)
    cameraPos.z = -world_size / 2;
  if (cameraPos.z < -world_size / 2)
    cameraPos.z = world_size / 2;
}

// Update the camera target based on mouse input
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  // Check if this is the time the mouse enters the screen to prevent jumps
  if(firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = lastY - ypos; 
  lastX = xpos;
  lastY = ypos;

  GLfloat sensitivity = 0.2f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw = glm::mod(yaw + xoffset, 360.0f);
  
  pitch += yoffset;
  if(pitch > 89.0f)
      pitch = 89.0f;
  if(pitch < -89.0f)
      pitch = -89.0f;

  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(front);
}  
