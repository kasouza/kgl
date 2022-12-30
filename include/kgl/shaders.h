#ifndef KASOUZA_KGL_INCLUDE_KGL_SHADERS_H
#define KASOUZA_KGL_INCLUDE_KGL_SHADERS_H

#include "kgl/gl_includes.h"

extern const char *kgl_sprite_vertex_shader;
extern const char *kgl_sprite_fragment_shader;

GLuint load_shader_from_file(const char *path, GLenum shader_type);
GLuint load_shader(const char *shader_src, GLenum shader_type);
GLuint create_program_from_files(const char *vertex_shader_path,
                                 const char *fragment_shader_path);
GLuint create_program(GLuint vertex_shader, GLuint fragment_shader);

#endif
