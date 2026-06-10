# Voxel Engine

A real-time 3D renderer built from scratch in modern C++ with **SDL3**, **OpenGL
4.6**, **GLAD**, and **GLM**. It currently implements the core rendering foundation
— a textured, depth-tested 3D scene with a free-fly first-person camera — and is
intended as the base for a voxel engine (chunked terrain rendering). See the
[Roadmap](#roadmap--toward-voxels) for what "voxel" work is still ahead.

<!-- Add a screenshot once you have one: -->
<!-- ![Screenshot](docs/screenshot.png) -->
![Sample Image](/images/SampleImage.png)

## Overview

The renderer initializes an OpenGL 4.6 core context through SDL3, loads function
pointers with GLAD, and draws a depth-tested 3D scene of textured cubes. Camera
movement and view transforms are handled by a custom `Camera` class, and shader
loading/compilation by a custom `ShaderProgram` class. Matrix math is done with GLM.

This is honest about where it is: the current scene is the classic textured-cube
test scene used to validate the transform pipeline, lighting-free, with two bound
textures. The engineering value here is the from-scratch pipeline — context
creation, VAO/VBO setup, shader abstraction, and a working FPS camera — that a voxel
renderer would build directly on top of.

## Features

- OpenGL 4.6 core-profile context via SDL3
- GLAD function loading
- Custom `ShaderProgram` class (load, compile, link, uniform helpers)
- Custom `Camera` class: first-person fly camera with yaw/pitch, pitch clamping,
  and delta-time-based movement
- Perspective projection with depth testing
- Texture loading via STB (`stb_image`)
- CMake build with SDL pulled in as a submodule and resources copied next to the
  binary at build time

## Controls

| Input | Action |
|-------|--------|
| `W` / `A` / `S` / `D` | Move forward / left / back / right |
| Mouse | Look around (relative mouse mode) |
| `Esc` | Quit |

## Requirements

- A C++ compiler with C++17+ and **CMake** ≥ 3.28
- **OpenGL** 4.6-capable GPU/driver
- **GLM** and **GLEW** (via `find_package`)
- System OpenGL development packages
  - Arch / EndeavourOS: `sudo pacman -S glm glew mesa cmake`
  - Debian / Ubuntu: `sudo apt install libglm-dev libglew-dev mesa-common-dev cmake`

SDL3 is built from source as a submodule, so no separate SDL install is needed.

## Building

```bash
# Clone with submodules (SDL3 is a submodule)
git clone --recurse-submodules https://github.com/Morgenrot-dev/Voxel-Engine.git
cd Voxel-Engine
# If already cloned without submodules:
#   git submodule update --init --recursive

mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
cmake --build .

# Run (resources are copied next to the binary during the build)
./Debug/Voxel_Editor
```

## Project structure

```
src/
  editor.cxx              entry point: context, buffers, textures, render loop
  renderer/
    shaders.cxx           ShaderProgram implementation
    camera.cxx            Camera implementation
includes/
  renderer/shaders/shaders.hpp
  renderer/camera/camera.hpp
  Third-Party/            glad, stb, KHR headers
resources/
  shader.vs / shader.fs   GLSL shaders
  container.jpg / awesomeface.png  textures
lib/glad/src/glad.c
CMakeLists.txt
```

## Roadmap — toward voxels

To grow into the name, the work ahead:

- [ ] Voxel/chunk data structure (e.g. 16×16×16 chunks)
- [ ] Mesh generation from voxel data with face culling (skip hidden faces)
- [ ] Greedy meshing to reduce triangle count
- [ ] Instanced or batched chunk rendering
- [ ] Basic lighting / ambient occlusion
- [ ] Frustum culling for chunks

## Known issues / cleanup

- `using namespace glm;` appears in a header (`camera.hpp`); scoping it to `.cxx`
  files (or qualifying types) avoids leaking the namespace into every includer.
- One submodule URL in `.gitmodules` uses SSH (`git@github.com:`), which breaks
  clones for anyone without configured SSH keys — switch it to HTTPS.
- The face texture (PNG with alpha) is uploaded with `GL_RGB`; it should be
  `GL_RGBA` to carry the alpha channel.

## Credits

Built while working through [LearnOpenGL](https://learnopengl.com/) by Joey de
Vries; the transform/camera/coordinate-systems scene follows that material.
Textures are the LearnOpenGL sample assets.
