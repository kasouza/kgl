#include <assert.h>
#include <err.h>

#include <kgl/error.h>
#include <kgl/input.h>
#include <kgl/renderer.h>
#include <kgl/texture.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool running = true;

int main()
{
    int result = kgl_init(256, 256, 0);
    if (result != KGL_SUCCESS)
        err(1, "%s", kgl_get_error_message(result));

    unsigned int tex = kgl_load_texture("assets/amogus.png");
    if (tex == 0)
        printf("WTF\n");

    const struct KglKeyboard *kb = kgl_get_keyboard();
    const struct KglMouse *mouse = kgl_get_mouse();
    while (running)
    {
        if (kb->keys[KGL_KEY_Q] || kb->keys[KGL_KEY_ESCAPE])
            running = false;

        if (mouse->buttons[KGL_MOUSE_BUTTON_2])
            printf("saske %f %f\n", mouse->x, mouse->y);

        if (mouse->scrolling)
            printf("scrolling\n");


		kgl_clear();

        kgl_draw_sprite(tex, 100, 100, 64, 64, glfwGetTime(), 32, 32);
        kgl_present();
    }

    kgl_terminate();

    return 0;
}
