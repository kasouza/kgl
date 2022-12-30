#include "kgl/shaders.h"
#include "kgl/utils.h"

#include <stdlib.h>

GLuint load_shader(const char *path, GLenum shader_type)
{
    char *shader_src = box_read_file(path);

    GLuint shader = glCreateShader(shader_type);
    if (!shader)
        /* DEBUG_LOG("Could not load shader\"%s\"", path); */
        return 0;

    // This casting is just to make the warning go away
    glShaderSource(shader, 1, (const char *const *)&shader_src, NULL);
    free(shader_src);

    glCompileShader(shader);

    int res = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (!res)
    {
        const GLsizei INFO_LOG_MAX_LENGTH = 256;
        GLchar info_log[INFO_LOG_MAX_LENGTH];
        GLsizei info_log_length = 0;

        glGetShaderInfoLog(shader, INFO_LOG_MAX_LENGTH, &info_log_length,
                           info_log);

        /* DEBUG_LOG("Could not compile shader %s\n", info_log); */

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

GLuint create_program(const char *vertex_shader_path,
                      const char *fragment_shader_path)
{
    GLuint vertex_shader = load_shader(vertex_shader_path, GL_VERTEX_SHADER);
    GLuint fragment_shader =
        load_shader(fragment_shader_path, GL_FRAGMENT_SHADER);
    if (!vertex_shader || !fragment_shader)
    {
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    int res = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &res);
    if (!res)
    {
        const GLsizei INFO_LOG_MAX_LENGTH = 256;
        GLchar info_log[INFO_LOG_MAX_LENGTH];
        GLsizei info_log_length = 0;

        glGetProgramInfoLog(program, INFO_LOG_MAX_LENGTH, &info_log_length,
                            info_log);

        /* DEBUG_LOG(info_log); */

        glDeleteProgram(program);
        return 0;
    }

    return program;
}
