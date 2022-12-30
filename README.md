# kgl - Kasouza's OpengGL renderer

KGL is a simple 2d renderer written in c using OpenGL. For now, the idea for this project is just having a base for my other projects/games/things, making it easier to start something new without having to setup OpenGL from scratch.

# Build
```
mkdir build
cd build
cmake .. && cmake --build .
```
Then link the generated static library.
Note: You NEED to copy the `shaders` folder to where your executable is when using the library like this. (I'll fix this soon)

Or the way I personally prefer to use this library is by cloning this repo and using CMake `àdd_library(path_to_kgl)`.

