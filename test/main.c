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

    struct KglSprite *mogus = kgl_load_sprite("assets/amogus.png");

    const struct KglKeyboard *kb = kgl_get_keyboard();
    const struct KglMouse *mouse = kgl_get_mouse();

    while (running)
    {
        if (kb->keys[KGL_KEY_Q] || kb->keys[KGL_KEY_ESCAPE])
            running = false;

        kgl_clear();

        kgl_draw_sprite(mogus, 100, 100, 64, 64, glfwGetTime(), 32, 32);
        kgl_present();
    }

    kgl_free_sprite(mogus);
    kgl_terminate();

    return 0;
}
