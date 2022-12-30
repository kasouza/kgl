# kgl - Kasouza's OpengGL renderer

KGL is a simple 2d renderer written in c using OpenGL. For now, the idea for this project is just having a base for my other projects/games/things, making it easier to start something new without having to setup OpenGL from scratch.

# Build
```
mkdir build
cd build
cmake .. && cmake --build .
```
Then link to the generated static library
or dot the way I prefer and clone this repo and use CMake `àdd_subdirectory(path_to_kgl)`.
