#include "kgl/renderer.h"
#include "kgl/error.h"
#include "kgl/input.h"
#include "kgl/shaders.h"
#include "kgl/utils.h"

#include <math.h>
#include <stb_image.h>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Call the setup function for `thing` and return a error if it ocurred.
#define SETUP(thing)                                                           \
    enum KglError thing##_error = setup_##thing();                             \
    if (thing##_error != KGL_SUCCESS)                                          \
        return thing##_error;

static bool init = false;
static enum KglInitFlags s_flags = 0;

static GLFWwindow *s_window = NULL;
static GLuint s_program = 0;

static GLuint s_rect_vao = 0;
static GLuint s_rect_vbo = 0;

static int s_window_width = 1024;
static int s_window_height = 600;

static void framebuffer_size_callback(GLFWwindow *_window, int width,
                                      int height)
{
    glViewport(0, 0, width, height);
    s_window_width = width;
    s_window_height = height;
}

static int setup_glfw()
{
    // GLFW Initialization
    if (!glfwInit())
        return KGL_ERROR_GLFW_INIT;

    // Window Creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    s_window =
        glfwCreateWindow(s_window_width, s_window_height, "KGL", NULL, NULL);

    if (!s_window)
        return KGL_ERROR_WINDOW_CREATION;

    glfwMakeContextCurrent(s_window);
    glfwSetFramebufferSizeCallback(s_window, framebuffer_size_callback);

    return KGL_SUCCESS;
}

static int setup_gl()
{
    // OpenGL setup
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return KGL_ERROR_GL_LOAD;

    glViewport(0, 0, s_window_width, s_window_height);

    return KGL_SUCCESS;
}

static enum KglError setup_buffers()
{
    // Rectangle
    float rect_vertices[] = {
        0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
        1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0,

        0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0,
        1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
    };

    glGenVertexArrays(1, &s_rect_vao);
    glGenBuffers(1, &s_rect_vbo);

    glBindVertexArray(s_rect_vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_rect_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                          (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                          (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glBindVertexArray(1);

    return KGL_SUCCESS;
}

static enum KglError setup_programs()
{
    s_program =
        create_program("shaders/passthrough.vert", "shaders/passthrough.frag");
    if (!s_program)
        return KGL_ERROR_PROGRAM_CREATION;

    return KGL_SUCCESS;
}

int kgl_init(int window_width, int window_height, enum KglInitFlags flags)
{
    s_window_width = window_width;
    s_window_height = window_height;

    SETUP(glfw);
    SETUP(gl);
    SETUP(programs);
    SETUP(buffers);

    init = true;
    s_flags = flags;

    kgl_input_init();

    return KGL_SUCCESS;
}

void kgl_present()
{
	// Update subsystems
    kgl_input_update();

	// Render
    static double start = -1;
    double dt = 1.0 / 60.0;
    if (start == -1)
    {
        start = glfwGetTime();
    }
    else
    {
        double now = glfwGetTime();
        dt = now - start;
        start = now;
    }

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(s_program);
    glBindVertexArray(s_rect_vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    if (s_flags & KGL_UNLOCK_FPS)
        glfwSwapInterval(0);

    glfwSwapBuffers(s_window);
    glfwPollEvents();
}

void kgl_terminate()
{
    if (!init)
        return;

    // Programs
    glDeleteProgram(s_program);
    s_program = 0;

    // VAOs and VBOs
    glDeleteVertexArrays(1, &s_rect_vao);
    glDeleteBuffers(1, &s_rect_vbo);

    glfwDestroyWindow(s_window);
    glfwTerminate();
}

GLFWwindow *kgl_get_window() { return s_window; }
