#include "kgl/input.h"
#include "kgl/gl_includes.h"
#include "kgl/renderer.h"
#include <assert.h>
#include <stdbool.h>

// These arrays here map the keys/button/actions this library API provides to
// the keys/butotn/actions used internally (in this case, provided by GLFW)
static int box_keys_to_glfw_keys[] = {
    [KGL_KEY_SPACE] = GLFW_KEY_SPACE,
    [KGL_KEY_APOSTROPHE] = GLFW_KEY_APOSTROPHE,
    [KGL_KEY_COMMA] = GLFW_KEY_COMMA,
    [KGL_KEY_MINUS] = GLFW_KEY_MINUS,
    [KGL_KEY_PERIOD] = GLFW_KEY_PERIOD,
    [KGL_KEY_SLASH] = GLFW_KEY_SLASH,
    [KGL_KEY_0] = GLFW_KEY_0,
    [KGL_KEY_1] = GLFW_KEY_1,
    [KGL_KEY_2] = GLFW_KEY_2,
    [KGL_KEY_3] = GLFW_KEY_3,
    [KGL_KEY_4] = GLFW_KEY_4,
    [KGL_KEY_5] = GLFW_KEY_5,
    [KGL_KEY_6] = GLFW_KEY_6,
    [KGL_KEY_7] = GLFW_KEY_7,
    [KGL_KEY_8] = GLFW_KEY_8,
    [KGL_KEY_9] = GLFW_KEY_9,
    [KGL_KEY_SEMICOLON] = GLFW_KEY_SEMICOLON,
    [KGL_KEY_EQUAL] = GLFW_KEY_EQUAL,
    [KGL_KEY_A] = GLFW_KEY_A,
    [KGL_KEY_B] = GLFW_KEY_B,
    [KGL_KEY_C] = GLFW_KEY_C,
    [KGL_KEY_D] = GLFW_KEY_D,
    [KGL_KEY_E] = GLFW_KEY_E,
    [KGL_KEY_F] = GLFW_KEY_F,
    [KGL_KEY_G] = GLFW_KEY_G,
    [KGL_KEY_H] = GLFW_KEY_H,
    [KGL_KEY_I] = GLFW_KEY_I,
    [KGL_KEY_J] = GLFW_KEY_J,
    [KGL_KEY_K] = GLFW_KEY_K,
    [KGL_KEY_L] = GLFW_KEY_L,
    [KGL_KEY_M] = GLFW_KEY_M,
    [KGL_KEY_N] = GLFW_KEY_N,
    [KGL_KEY_O] = GLFW_KEY_O,
    [KGL_KEY_P] = GLFW_KEY_P,
    [KGL_KEY_Q] = GLFW_KEY_Q,
    [KGL_KEY_R] = GLFW_KEY_R,
    [KGL_KEY_S] = GLFW_KEY_S,
    [KGL_KEY_T] = GLFW_KEY_T,
    [KGL_KEY_U] = GLFW_KEY_U,
    [KGL_KEY_V] = GLFW_KEY_V,
    [KGL_KEY_W] = GLFW_KEY_W,
    [KGL_KEY_X] = GLFW_KEY_X,
    [KGL_KEY_Y] = GLFW_KEY_Y,
    [KGL_KEY_Z] = GLFW_KEY_Z,
    [KGL_KEY_LEFT_BRACKET] = GLFW_KEY_LEFT_BRACKET,
    [KGL_KEY_BACKSLASH] = GLFW_KEY_BACKSLASH,
    [KGL_KEY_RIGHT_BRACKET] = GLFW_KEY_RIGHT_BRACKET,
    [KGL_KEY_GRAVE_ACCENT] = GLFW_KEY_GRAVE_ACCENT,
    [KGL_KEY_WORLD_1] = GLFW_KEY_WORLD_1,
    [KGL_KEY_WORLD_2] = GLFW_KEY_WORLD_2,
    [KGL_KEY_ESCAPE] = GLFW_KEY_ESCAPE,
    [KGL_KEY_ENTER] = GLFW_KEY_ENTER,
    [KGL_KEY_TAB] = GLFW_KEY_TAB,
    [KGL_KEY_BACKSPACE] = GLFW_KEY_BACKSPACE,
    [KGL_KEY_INSERT] = GLFW_KEY_INSERT,
    [KGL_KEY_DELETE] = GLFW_KEY_DELETE,
    [KGL_KEY_RIGHT] = GLFW_KEY_RIGHT,
    [KGL_KEY_LEFT] = GLFW_KEY_LEFT,
    [KGL_KEY_DOWN] = GLFW_KEY_DOWN,
    [KGL_KEY_UP] = GLFW_KEY_UP,
    [KGL_KEY_PAGE_UP] = GLFW_KEY_PAGE_UP,
    [KGL_KEY_PAGE_DOWN] = GLFW_KEY_PAGE_DOWN,
    [KGL_KEY_HOME] = GLFW_KEY_HOME,
    [KGL_KEY_END] = GLFW_KEY_END,
    [KGL_KEY_CAPS_LOCK] = GLFW_KEY_CAPS_LOCK,
    [KGL_KEY_SCROLL_LOCK] = GLFW_KEY_SCROLL_LOCK,
    [KGL_KEY_NUM_LOCK] = GLFW_KEY_NUM_LOCK,
    [KGL_KEY_PRINT_SCREEN] = GLFW_KEY_PRINT_SCREEN,
    [KGL_KEY_PAUSE] = GLFW_KEY_PAUSE,
    [KGL_KEY_F1] = GLFW_KEY_F1,
    [KGL_KEY_F2] = GLFW_KEY_F2,
    [KGL_KEY_F3] = GLFW_KEY_F3,
    [KGL_KEY_F4] = GLFW_KEY_F4,
    [KGL_KEY_F5] = GLFW_KEY_F5,
    [KGL_KEY_F6] = GLFW_KEY_F6,
    [KGL_KEY_F7] = GLFW_KEY_F7,
    [KGL_KEY_F8] = GLFW_KEY_F8,
    [KGL_KEY_F9] = GLFW_KEY_F9,
    [KGL_KEY_F10] = GLFW_KEY_F10,
    [KGL_KEY_F11] = GLFW_KEY_F11,
    [KGL_KEY_F12] = GLFW_KEY_F12,
    [KGL_KEY_F13] = GLFW_KEY_F13,
    [KGL_KEY_F14] = GLFW_KEY_F14,
    [KGL_KEY_F15] = GLFW_KEY_F15,
    [KGL_KEY_F16] = GLFW_KEY_F16,
    [KGL_KEY_F17] = GLFW_KEY_F17,
    [KGL_KEY_F18] = GLFW_KEY_F18,
    [KGL_KEY_F19] = GLFW_KEY_F19,
    [KGL_KEY_F20] = GLFW_KEY_F20,
    [KGL_KEY_F21] = GLFW_KEY_F21,
    [KGL_KEY_F22] = GLFW_KEY_F22,
    [KGL_KEY_F23] = GLFW_KEY_F23,
    [KGL_KEY_F24] = GLFW_KEY_F24,
    [KGL_KEY_F25] = GLFW_KEY_F25,
    [KGL_KEY_KP_0] = GLFW_KEY_KP_0,
    [KGL_KEY_KP_1] = GLFW_KEY_KP_1,
    [KGL_KEY_KP_2] = GLFW_KEY_KP_2,
    [KGL_KEY_KP_3] = GLFW_KEY_KP_3,
    [KGL_KEY_KP_4] = GLFW_KEY_KP_4,
    [KGL_KEY_KP_5] = GLFW_KEY_KP_5,
    [KGL_KEY_KP_6] = GLFW_KEY_KP_6,
    [KGL_KEY_KP_7] = GLFW_KEY_KP_7,
    [KGL_KEY_KP_8] = GLFW_KEY_KP_8,
    [KGL_KEY_KP_9] = GLFW_KEY_KP_9,
    [KGL_KEY_KP_DECIMAL] = GLFW_KEY_KP_DECIMAL,
    [KGL_KEY_KP_DIVIDE] = GLFW_KEY_KP_DIVIDE,
    [KGL_KEY_KP_MULTIPLY] = GLFW_KEY_KP_MULTIPLY,
    [KGL_KEY_KP_SUBTRACT] = GLFW_KEY_KP_SUBTRACT,
    [KGL_KEY_KP_ADD] = GLFW_KEY_KP_ADD,
    [KGL_KEY_KP_ENTER] = GLFW_KEY_KP_ENTER,
    [KGL_KEY_KP_EQUAL] = GLFW_KEY_KP_EQUAL,
    [KGL_KEY_LEFT_SHIFT] = GLFW_KEY_LEFT_SHIFT,
    [KGL_KEY_LEFT_CONTROL] = GLFW_KEY_LEFT_CONTROL,
    [KGL_KEY_LEFT_ALT] = GLFW_KEY_LEFT_ALT,
    [KGL_KEY_LEFT_SUPER] = GLFW_KEY_LEFT_SUPER,
    [KGL_KEY_RIGHT_SHIFT] = GLFW_KEY_RIGHT_SHIFT,
    [KGL_KEY_RIGHT_CONTROL] = GLFW_KEY_RIGHT_CONTROL,
    [KGL_KEY_RIGHT_ALT] = GLFW_KEY_RIGHT_ALT,
    [KGL_KEY_RIGHT_SUPER] = GLFW_KEY_RIGHT_SUPER,
    [KGL_KEY_MENU] = GLFW_KEY_MENU,
};

static int glfw_keys_to_kgl_keys[] = {
    [GLFW_KEY_SPACE] = KGL_KEY_SPACE,
    [GLFW_KEY_APOSTROPHE] = KGL_KEY_APOSTROPHE,
    [GLFW_KEY_COMMA] = KGL_KEY_COMMA,
    [GLFW_KEY_MINUS] = KGL_KEY_MINUS,
    [GLFW_KEY_PERIOD] = KGL_KEY_PERIOD,
    [GLFW_KEY_SLASH] = KGL_KEY_SLASH,
    [GLFW_KEY_0] = KGL_KEY_0,
    [GLFW_KEY_1] = KGL_KEY_1,
    [GLFW_KEY_2] = KGL_KEY_2,
    [GLFW_KEY_3] = KGL_KEY_3,
    [GLFW_KEY_4] = KGL_KEY_4,
    [GLFW_KEY_5] = KGL_KEY_5,
    [GLFW_KEY_6] = KGL_KEY_6,
    [GLFW_KEY_7] = KGL_KEY_7,
    [GLFW_KEY_8] = KGL_KEY_8,
    [GLFW_KEY_9] = KGL_KEY_9,
    [GLFW_KEY_SEMICOLON] = KGL_KEY_SEMICOLON,
    [GLFW_KEY_EQUAL] = KGL_KEY_EQUAL,
    [GLFW_KEY_A] = KGL_KEY_A,
    [GLFW_KEY_B] = KGL_KEY_B,
    [GLFW_KEY_C] = KGL_KEY_C,
    [GLFW_KEY_D] = KGL_KEY_D,
    [GLFW_KEY_E] = KGL_KEY_E,
    [GLFW_KEY_F] = KGL_KEY_F,
    [GLFW_KEY_G] = KGL_KEY_G,
    [GLFW_KEY_H] = KGL_KEY_H,
    [GLFW_KEY_I] = KGL_KEY_I,
    [GLFW_KEY_J] = KGL_KEY_J,
    [GLFW_KEY_K] = KGL_KEY_K,
    [GLFW_KEY_L] = KGL_KEY_L,
    [GLFW_KEY_M] = KGL_KEY_M,
    [GLFW_KEY_N] = KGL_KEY_N,
    [GLFW_KEY_O] = KGL_KEY_O,
    [GLFW_KEY_P] = KGL_KEY_P,
    [GLFW_KEY_Q] = KGL_KEY_Q,
    [GLFW_KEY_R] = KGL_KEY_R,
    [GLFW_KEY_S] = KGL_KEY_S,
    [GLFW_KEY_T] = KGL_KEY_T,
    [GLFW_KEY_U] = KGL_KEY_U,
    [GLFW_KEY_V] = KGL_KEY_V,
    [GLFW_KEY_W] = KGL_KEY_W,
    [GLFW_KEY_X] = KGL_KEY_X,
    [GLFW_KEY_Y] = KGL_KEY_Y,
    [GLFW_KEY_Z] = KGL_KEY_Z,
    [GLFW_KEY_LEFT_BRACKET] = KGL_KEY_LEFT_BRACKET,
    [GLFW_KEY_BACKSLASH] = KGL_KEY_BACKSLASH,
    [GLFW_KEY_RIGHT_BRACKET] = KGL_KEY_RIGHT_BRACKET,
    [GLFW_KEY_GRAVE_ACCENT] = KGL_KEY_GRAVE_ACCENT,
    [GLFW_KEY_WORLD_1] = KGL_KEY_WORLD_1,
    [GLFW_KEY_WORLD_2] = KGL_KEY_WORLD_2,
    [GLFW_KEY_ESCAPE] = KGL_KEY_ESCAPE,
    [GLFW_KEY_ENTER] = KGL_KEY_ENTER,
    [GLFW_KEY_TAB] = KGL_KEY_TAB,
    [GLFW_KEY_BACKSPACE] = KGL_KEY_BACKSPACE,
    [GLFW_KEY_INSERT] = KGL_KEY_INSERT,
    [GLFW_KEY_DELETE] = KGL_KEY_DELETE,
    [GLFW_KEY_RIGHT] = KGL_KEY_RIGHT,
    [GLFW_KEY_LEFT] = KGL_KEY_LEFT,
    [GLFW_KEY_DOWN] = KGL_KEY_DOWN,
    [GLFW_KEY_UP] = KGL_KEY_UP,
    [GLFW_KEY_PAGE_UP] = KGL_KEY_PAGE_UP,
    [GLFW_KEY_PAGE_DOWN] = KGL_KEY_PAGE_DOWN,
    [GLFW_KEY_HOME] = KGL_KEY_HOME,
    [GLFW_KEY_END] = KGL_KEY_END,
    [GLFW_KEY_CAPS_LOCK] = KGL_KEY_CAPS_LOCK,
    [GLFW_KEY_SCROLL_LOCK] = KGL_KEY_SCROLL_LOCK,
    [GLFW_KEY_NUM_LOCK] = KGL_KEY_NUM_LOCK,
    [GLFW_KEY_PRINT_SCREEN] = KGL_KEY_PRINT_SCREEN,
    [GLFW_KEY_PAUSE] = KGL_KEY_PAUSE,
    [GLFW_KEY_F1] = KGL_KEY_F1,
    [GLFW_KEY_F2] = KGL_KEY_F2,
    [GLFW_KEY_F3] = KGL_KEY_F3,
    [GLFW_KEY_F4] = KGL_KEY_F4,
    [GLFW_KEY_F5] = KGL_KEY_F5,
    [GLFW_KEY_F6] = KGL_KEY_F6,
    [GLFW_KEY_F7] = KGL_KEY_F7,
    [GLFW_KEY_F8] = KGL_KEY_F8,
    [GLFW_KEY_F9] = KGL_KEY_F9,
    [GLFW_KEY_F10] = KGL_KEY_F10,
    [GLFW_KEY_F11] = KGL_KEY_F11,
    [GLFW_KEY_F12] = KGL_KEY_F12,
    [GLFW_KEY_F13] = KGL_KEY_F13,
    [GLFW_KEY_F14] = KGL_KEY_F14,
    [GLFW_KEY_F15] = KGL_KEY_F15,
    [GLFW_KEY_F16] = KGL_KEY_F16,
    [GLFW_KEY_F17] = KGL_KEY_F17,
    [GLFW_KEY_F18] = KGL_KEY_F18,
    [GLFW_KEY_F19] = KGL_KEY_F19,
    [GLFW_KEY_F20] = KGL_KEY_F20,
    [GLFW_KEY_F21] = KGL_KEY_F21,
    [GLFW_KEY_F22] = KGL_KEY_F22,
    [GLFW_KEY_F23] = KGL_KEY_F23,
    [GLFW_KEY_F24] = KGL_KEY_F24,
    [GLFW_KEY_F25] = KGL_KEY_F25,
    [GLFW_KEY_KP_0] = KGL_KEY_KP_0,
    [GLFW_KEY_KP_1] = KGL_KEY_KP_1,
    [GLFW_KEY_KP_2] = KGL_KEY_KP_2,
    [GLFW_KEY_KP_3] = KGL_KEY_KP_3,
    [GLFW_KEY_KP_4] = KGL_KEY_KP_4,
    [GLFW_KEY_KP_5] = KGL_KEY_KP_5,
    [GLFW_KEY_KP_6] = KGL_KEY_KP_6,
    [GLFW_KEY_KP_7] = KGL_KEY_KP_7,
    [GLFW_KEY_KP_8] = KGL_KEY_KP_8,
    [GLFW_KEY_KP_9] = KGL_KEY_KP_9,
    [GLFW_KEY_KP_DECIMAL] = KGL_KEY_KP_DECIMAL,
    [GLFW_KEY_KP_DIVIDE] = KGL_KEY_KP_DIVIDE,
    [GLFW_KEY_KP_MULTIPLY] = KGL_KEY_KP_MULTIPLY,
    [GLFW_KEY_KP_SUBTRACT] = KGL_KEY_KP_SUBTRACT,
    [GLFW_KEY_KP_ADD] = KGL_KEY_KP_ADD,
    [GLFW_KEY_KP_ENTER] = KGL_KEY_KP_ENTER,
    [GLFW_KEY_KP_EQUAL] = KGL_KEY_KP_EQUAL,
    [GLFW_KEY_LEFT_SHIFT] = KGL_KEY_LEFT_SHIFT,
    [GLFW_KEY_LEFT_CONTROL] = KGL_KEY_LEFT_CONTROL,
    [GLFW_KEY_LEFT_ALT] = KGL_KEY_LEFT_ALT,
    [GLFW_KEY_LEFT_SUPER] = KGL_KEY_LEFT_SUPER,
    [GLFW_KEY_RIGHT_SHIFT] = KGL_KEY_RIGHT_SHIFT,
    [GLFW_KEY_RIGHT_CONTROL] = KGL_KEY_RIGHT_CONTROL,
    [GLFW_KEY_RIGHT_ALT] = KGL_KEY_RIGHT_ALT,
    [GLFW_KEY_RIGHT_SUPER] = KGL_KEY_RIGHT_SUPER,
    [GLFW_KEY_MENU] = KGL_KEY_MENU,
};

static int kgl_mouse_button_to_glfw_mouse_button[] = {
    [KGL_MOUSE_BUTTON_1] = GLFW_MOUSE_BUTTON_1,
    [KGL_MOUSE_BUTTON_2] = GLFW_MOUSE_BUTTON_2,
    [KGL_MOUSE_BUTTON_3] = GLFW_MOUSE_BUTTON_3,
    [KGL_MOUSE_BUTTON_4] = GLFW_MOUSE_BUTTON_4,
    [KGL_MOUSE_BUTTON_5] = GLFW_MOUSE_BUTTON_5,
    [KGL_MOUSE_BUTTON_6] = GLFW_MOUSE_BUTTON_6,
    [KGL_MOUSE_BUTTON_7] = GLFW_MOUSE_BUTTON_7,
    [KGL_MOUSE_BUTTON_8] = GLFW_MOUSE_BUTTON_8,
};

static int glfw_mouse_button_to_kgl_mouse_button[] = {
    [GLFW_MOUSE_BUTTON_1] = KGL_MOUSE_BUTTON_1,
    [GLFW_MOUSE_BUTTON_2] = KGL_MOUSE_BUTTON_2,
    [GLFW_MOUSE_BUTTON_3] = KGL_MOUSE_BUTTON_3,
    [GLFW_MOUSE_BUTTON_4] = KGL_MOUSE_BUTTON_4,
    [GLFW_MOUSE_BUTTON_5] = KGL_MOUSE_BUTTON_5,
    [GLFW_MOUSE_BUTTON_6] = KGL_MOUSE_BUTTON_6,
    [GLFW_MOUSE_BUTTON_7] = KGL_MOUSE_BUTTON_7,
    [GLFW_MOUSE_BUTTON_8] = KGL_MOUSE_BUTTON_8,
};

static int kgl_input_action_to_glfw_action[] = {
    [KGL_PRESS] = GLFW_PRESS,
    [KGL_RELEASE] = GLFW_RELEASE,
};

static int glfw_action_to_kgl_input_action[] = {
    [GLFW_PRESS] = KGL_PRESS,
    [GLFW_RELEASE] = KGL_RELEASE,
};

const struct KglMouse *kgl_get_mouse() { return &s_mouse; }
const struct KglKeyboard *kgl_get_keyboard() { return &s_keyboard; }

void input_cursor_pos_cb(GLFWwindow *window, double x_pos, double y_pos)
{
    s_mouse.x = x_pos;
    s_mouse.y = y_pos;
}

void input_key_cb(GLFWwindow *window, int key, int scancode, int action,
                  int mods)
{
    if (action == GLFW_PRESS)
        s_keyboard.keys[glfw_keys_to_kgl_keys[key]] = true;

    if (action == GLFW_RELEASE)
        s_keyboard.keys[glfw_keys_to_kgl_keys[key]] = false;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
        s_mouse.buttons[glfw_mouse_button_to_kgl_mouse_button[button]] = true;

    if (action == GLFW_RELEASE)
        s_mouse.buttons[glfw_mouse_button_to_kgl_mouse_button[button]] = false;
}

void scroll_callback(GLFWwindow *window, double x_offset, double y_offset)
{
    s_mouse.scroll_offset_x += x_offset;
    s_mouse.scroll_offset_y += y_offset;
    s_mouse.scrolling = true;
}

void kgl_input_init()
{
    GLFWwindow *window = kgl_get_window();
    assert(window != NULL && "No window available for input handling.");

    glfwSetCursorPosCallback(window, input_cursor_pos_cb);
    glfwSetKeyCallback(window, input_key_cb);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void kgl_input_update()
{
    s_mouse.scroll_offset_x = 0;
    s_mouse.scroll_offset_y = 0;
	s_mouse.scrolling = false;
}
