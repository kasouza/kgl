#ifndef KASOUZA_KGL_INCLUDE_KGL_UTILS_H
#define KASOUZA_KGL_INCLUDE_KGL_UTILS_H

#define BOX_LOG(...) fprintf(stderr, __VA_ARGS__)

#define BOX_MIN(a, b) ((a) < (b) ? (a) : (b))
#define BOX_MAX(a, b) ((a) > (b) ? (a) : (b))
#define BOX_CLAMP(n, min, max) (BOX_MIN(BOX_MAX(n, min), max))

char *kgl_read_file(const char *path);
void *kgl_malloc(unsigned long bytes);
void *kgl_calloc(unsigned long n, unsigned long size);

#endif
