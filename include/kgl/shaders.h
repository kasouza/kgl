#ifndef KASOUZA_KGL_INCLUDE_KGL_SHADERS_H
#define KASOUZA_KGL_INCLUDE_KGL_SHADERS_H

#include "kgl/gl_includes.h"

GLuint load_shader(const char *path, GLenum shader_type);
GLuint create_program(const char *vertex_shader_path,
                      const char *fragment_shader_path);

#endif
