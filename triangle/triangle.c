// GLEW is an extension loading library
// OpenGL core functions are linked dynamically at runtime
// GLEW exposes them in a single header file
// Include GLEW before GLFW to use its OpenGL header
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "utils.h"

void initialize(GLFWwindow **window) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  *window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
  glViewport(0, 0, 800, 600);
  glfwMakeContextCurrent(*window);

  // An active OpenGL context is needed to retrieve function pointers
  glewInit();
}

int main() {
  // OpenGL objects are referenced by their GLuint names
  const GLfloat vertices[] = {-0.5, -0.5, 0.5, -0.5, 0.0, 0.5};
  GLFWwindow *window;
  GLuint vertexBuffer, vertexArray, shaderProgram;

  initialize(&window);

  // VBOs represent memory buffers in the GPU
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // VAOs store information for a complete rendered object
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  shaderProgram = create_program();

  while (glfwWindowShouldClose(window) == GL_FALSE) {
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return EXIT_SUCCESS;
}
