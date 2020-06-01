# ray-tracer-challenge
C++ implementation of the "Ray Tracing Challenge" book and extra things.

## Features

Lighting: Point, Area, Spot

![Spotlight on Chessboard](/images/chessboard.png)

Dear imgui based immediate mode GUI

![GUI](/images/elptracer.png)

Spherical and Plane UV mapped PNGs

![Texture Mapping](/images/texture_mapping.png)

OBJ file loading

![Underwater teapots](/images/chapter15_2.png)

Constructive Solid Geometry

![Texture Mapping](/images/chapter16_1.png)

Paterns including perlin noise deformation

![Patterned spheres](/images/chapter10_patterns.png)

Depth of Field

![Depth of field effect on spheres](/images/chapter11_5.png)

Supersampling camera

![Supersampled Tetronimoes](/images/chapter12_1.png)

Perlin Noise Normal Deformation

![Perturbed Normal Spheres](/images/perturbed_normals.png)

And... PNG and PPM output, Multithreaded rendering, googletest tests.

## Installation
### Install [Dear ImGui](https://github.com/ocornut/imgui)
```
git submodule update --init
```

### Run CMake
```
cd build
cmake ..
<use the build system of choice, e.g make that was generated>
```
