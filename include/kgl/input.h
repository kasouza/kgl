#ifndef KASOUZA_KGL_INCLUDE_KGL_INPUT_H
#define KASOUZA_KGL_INCLUDE_KGL_INPUT_H

#include <stdbool.h>

enum KglKey
{
    KGL_KEY_UNKNOWN = -1,
    KGL_KEY_SPACE,
    KGL_KEY_APOSTROPHE,
    KGL_KEY_COMMA,
    KGL_KEY_MINUS,
    KGL_KEY_PERIOD,
    KGL_KEY_SLASH,
    KGL_KEY_0,
    KGL_KEY_1,
    KGL_KEY_2,
    KGL_KEY_3,
    KGL_KEY_4,
    KGL_KEY_5,
    KGL_KEY_6,
    KGL_KEY_7,
    KGL_KEY_8,
    KGL_KEY_9,
    KGL_KEY_SEMICOLON,
    KGL_KEY_EQUAL,
    KGL_KEY_A,
    KGL_KEY_B,
    KGL_KEY_C,
    KGL_KEY_D,
    KGL_KEY_E,
    KGL_KEY_F,
    KGL_KEY_G,
    KGL_KEY_H,
    KGL_KEY_I,
    KGL_KEY_J,
    KGL_KEY_K,
    KGL_KEY_L,
    KGL_KEY_M,
    KGL_KEY_N,
    KGL_KEY_O,
    KGL_KEY_P,
    KGL_KEY_Q,
    KGL_KEY_R,
    KGL_KEY_S,
    KGL_KEY_T,
    KGL_KEY_U,
    KGL_KEY_V,
    KGL_KEY_W,
    KGL_KEY_X,
    KGL_KEY_Y,
    KGL_KEY_Z,
    KGL_KEY_LEFT_BRACKET,
    KGL_KEY_BACKSLASH,
    KGL_KEY_RIGHT_BRACKET,
    KGL_KEY_GRAVE_ACCENT,
    KGL_KEY_WORLD_1,
    KGL_KEY_WORLD_2,
    KGL_KEY_ESCAPE,
    KGL_KEY_ENTER,
    KGL_KEY_TAB,
    KGL_KEY_BACKSPACE,
    KGL_KEY_INSERT,
    KGL_KEY_DELETE,
    KGL_KEY_RIGHT,
    KGL_KEY_LEFT,
    KGL_KEY_DOWN,
    KGL_KEY_UP,
    KGL_KEY_PAGE_UP,
    KGL_KEY_PAGE_DOWN,
    KGL_KEY_HOME,
    KGL_KEY_END,
    KGL_KEY_CAPS_LOCK,
    KGL_KEY_SCROLL_LOCK,
    KGL_KEY_NUM_LOCK,
    KGL_KEY_PRINT_SCREEN,
    KGL_KEY_PAUSE,
    KGL_KEY_F1,
    KGL_KEY_F2,
    KGL_KEY_F3,
    KGL_KEY_F4,
    KGL_KEY_F5,
    KGL_KEY_F6,
    KGL_KEY_F7,
    KGL_KEY_F8,
    KGL_KEY_F9,
    KGL_KEY_F10,
    KGL_KEY_F11,
    KGL_KEY_F12,
    KGL_KEY_F13,
    KGL_KEY_F14,
    KGL_KEY_F15,
    KGL_KEY_F16,
    KGL_KEY_F17,
    KGL_KEY_F18,
    KGL_KEY_F19,
    KGL_KEY_F20,
    KGL_KEY_F21,
    KGL_KEY_F22,
    KGL_KEY_F23,
    KGL_KEY_F24,
    KGL_KEY_F25,
    KGL_KEY_KP_0,
    KGL_KEY_KP_1,
    KGL_KEY_KP_2,
    KGL_KEY_KP_3,
    KGL_KEY_KP_4,
    KGL_KEY_KP_5,
    KGL_KEY_KP_6,
    KGL_KEY_KP_7,
    KGL_KEY_KP_8,
    KGL_KEY_KP_9,
    KGL_KEY_KP_DECIMAL,
    KGL_KEY_KP_DIVIDE,
    KGL_KEY_KP_MULTIPLY,
    KGL_KEY_KP_SUBTRACT,
    KGL_KEY_KP_ADD,
    KGL_KEY_KP_ENTER,
    KGL_KEY_KP_EQUAL,
    KGL_KEY_LEFT_SHIFT,
    KGL_KEY_LEFT_CONTROL,
    KGL_KEY_LEFT_ALT,
    KGL_KEY_LEFT_SUPER,
    KGL_KEY_RIGHT_SHIFT,
    KGL_KEY_RIGHT_CONTROL,
    KGL_KEY_RIGHT_ALT,
    KGL_KEY_RIGHT_SUPER,
    KGL_KEY_MENU,
    KGL_KEY_LAST,
};

enum KglMouseButton
{
    KGL_MOUSE_BUTTON_NONE,
    KGL_MOUSE_BUTTON_1,
    KGL_MOUSE_BUTTON_2,
    KGL_MOUSE_BUTTON_3,
    KGL_MOUSE_BUTTON_4,
    KGL_MOUSE_BUTTON_5,
    KGL_MOUSE_BUTTON_6,
    KGL_MOUSE_BUTTON_7,
    KGL_MOUSE_BUTTON_8,
    KGL_MOUSE_BUTTON_LAST,
};

enum KglInputAction
{
    KGL_PRESS,
    KGL_RELEASE,
};

static struct KglMouse
{
    double x;
    double y;

    double scroll_offset_x;
    double scroll_offset_y;
    bool scrolling;

    bool buttons[KGL_MOUSE_BUTTON_LAST];
} s_mouse = {0};

static struct KglKeyboard
{
    bool keys[KGL_KEY_LAST];
} s_keyboard = {0};

const struct KglMouse *kgl_get_mouse();
const struct KglKeyboard *kgl_get_keyboard();

// Used internally, no need to call it yourself
void kgl_input_init();
void kgl_input_update();

#endif
