#ifndef KASOUZA_KGL_INCLUDE_KGL_ERROR_H
#define KASOUZA_KGL_INCLUDE_KGL_ERROR_H

enum KglError
{
    KGL_SUCCESS,	// Success == 0

    KGL_ERROR_GLFW_INIT,
    KGL_ERROR_WINDOW_CREATION,
    KGL_ERROR_GL_LOAD,
    KGL_ERROR_PROGRAM_CREATION,
    KGL_ERROR_FRAMEBUFFER_CREATION,

	KGL_ERROR_LAST,	// Used to create arrays
};

const char *kgl_get_error_message(enum KglError error);

#endif
