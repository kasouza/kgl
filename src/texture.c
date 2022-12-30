#include "kgl/gl_includes.h"

#include <stb_image.h>
#include <stdbool.h>

unsigned int kgl_load_texture(const char *path_to_image)
{
    stbi_set_flip_vertically_on_load(true);

    int width, height, nr_channels;
    unsigned char *data =
        stbi_load(path_to_image, &width, &height, &nr_channels, 0);

    if (!data)
        return 0;

    GLenum format;
    switch (nr_channels)
    {
    case 1:
        format = GL_RED;
        break;

    case 2:
        format = GL_RGB;
        break;

    case 3:
        format = GL_RGB;
        break;

    case 4:
        format = GL_RGBA;
        break;

    default:
        return 0;
    }

    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    return texture;
}
