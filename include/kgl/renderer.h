#ifndef KASOUZA_KGL_INCLUDE_KGL_RENDERER_H
#define KASOUZA_KGL_INCLUDE_KGL_RENDERER_H

#include "kgl/gl_includes.h"

struct KglSprite;

enum KglInitFlags
{
    KGL_UNLOCK_FPS = 0x00000001,
};

int kgl_init(int canvas_width, int canvas_height, enum KglInitFlags flags);
void kgl_present();
void kgl_clear();
void kgl_clear_colored(float r, float g, float b, float a);
void kgl_terminate();

void kgl_draw_sprite(struct KglSprite *sprite, double x, double y, double width,
                     double height, double rotation, double pivot_x,
                     double pivot_y);

void kgl_draw_sub_sprite(struct KglSprite *sprite, double x, double y, double width,
                         double height, double rotation, double pivot_x,
                         double pivot_y, double sub_x1, double sub_y1,
                         double sub_x2, double sub_y2);

GLFWwindow *kgl_get_window();

#endif
