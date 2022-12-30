#include "kgl/error.h"
#include <assert.h>

const char *s_error_messages[KGL_ERROR_LAST] = {
    [KGL_SUCCESS] = "",
    [KGL_ERROR_GLFW_INIT] = "Could not initialize the GLFW library.",
    [KGL_ERROR_WINDOW_CREATION] = "Could not create a window.",
    [KGL_ERROR_GL_LOAD] = "Could not load OpenGL.",
    [KGL_ERROR_PROGRAM_CREATION] = "Could not create shader program.",
    [KGL_ERROR_FRAMEBUFFER_CREATION] = "Could not create framebuffer.",
};

const char *kgl_get_error_message(enum KglError error)
{
    assert(error >= 0 && error < KGL_ERROR_LAST && "Error out of bounds.");
    return s_error_messages[error];
}
