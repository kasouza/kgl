#ifndef KASOUZA_KGL_INCLUDE_KGL_RENDERER_H
#define KASOUZA_KGL_INCLUDE_KGL_RENDERER_H

#include "kgl/gl_includes.h"

enum KglInitFlags
{
    KGL_UNLOCK_FPS = 0x00000001,
};

int kgl_init(int canvas_width, int canvas_height, enum KglInitFlags flags);
void kgl_present();
void kgl_terminate();

GLFWwindow *kgl_get_window();

#endif
