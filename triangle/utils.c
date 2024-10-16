#include "utils.h"

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GLuint compileShader(char *filename, GLuint type) {
  GLuint shader;
  FILE *file;
  char *buffer = NULL;
  size_t len = 0;
  ssize_t n;
  GLchar *source[100] = {NULL};
  int line = 0;
  int success;

  file = fopen(filename, "r");

  if (file == NULL) {
    printf("%s does not exist\n", filename);
    exit(EXIT_FAILURE);
  }

  while ((n = getline(&buffer, &len, file)) != -1) {
    source[line] = malloc(n * sizeof(char));
    memcpy(source[line], buffer, n);
    line++;
  }

  fclose(file);

  if (type == GL_VERTEX_SHADER) {
    shader = glCreateShader(GL_VERTEX_SHADER);
  } else {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  }

  glShaderSource(shader, line, (const GLchar **)source, NULL);
  glCompileShader(shader);

  for (int i = 0; i < line; i++) {
    free(source[i]);
  }

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    printf("%s failed to compile\n", filename);
    exit(EXIT_FAILURE);
  }

  printf("%s compiled successfully\n", filename);

  return shader;
}

GLuint createShaderProgram() {
  GLuint vertexShader, fragmentShader, shaderProgram;
  int success;
  shaderProgram = glCreateProgram();
  vertexShader = compileShader("vertex.shader", GL_VERTEX_SHADER);
  fragmentShader = compileShader("fragment.shader", GL_FRAGMENT_SHADER);

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (success == GL_FALSE) {
    printf("shader program failed to link\n");
    exit(EXIT_FAILURE);
  }

  printf("shader program linked successfully\n");

  return shaderProgram;
}
