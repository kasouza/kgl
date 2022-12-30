#ifndef KASOUZA_KGL_INCLUDE_KGL_TEXTURE_H
#define KASOUZA_KGL_INCLUDE_KGL_TEXTURE_H

struct KglSprite
{
    unsigned int texture;
    double width;
    double height;
};

struct KglSprite* kgl_load_sprite(const char *path_to_image);
void kgl_free_sprite(struct KglSprite *texture);

#endif
