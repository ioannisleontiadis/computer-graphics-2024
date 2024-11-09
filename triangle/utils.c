#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

GLuint compile_shader(char *filename, GLenum type) {
  GLuint shader;
  GLint success;

  FILE *file;
  char *source;
  long int length;

  file = fopen(filename, "r");

  if (file == NULL) {
    printf("%s does not exist\n", filename);
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  source = malloc((length + 1) * sizeof(char));
  fread(source, sizeof(char), length, file);
  source[length] = '\0';
  fclose(file);

  if (type == GL_VERTEX_SHADER) {
    shader = glCreateShader(GL_VERTEX_SHADER);
  } else {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  }

  glShaderSource(shader, 1, (const GLchar **)&source, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    printf("%s failed to compile\n", filename);
    exit(EXIT_FAILURE);
  }

  printf("%s compiled successfully\n", filename);

  return shader;
}

GLuint create_program() {
  GLuint vertex_shader, fragment_shader, program;
  GLint success;

  program = glCreateProgram();
  vertex_shader = compile_shader("vertex.shader", GL_VERTEX_SHADER);
  fragment_shader = compile_shader("fragment.shader", GL_FRAGMENT_SHADER);

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (success == GL_FALSE) {
    printf("shader program failed to link\n");
    exit(EXIT_FAILURE);
  }

  printf("shader program linked successfully\n");

  return program;
}
