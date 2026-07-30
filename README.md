# cpparticle

`cpparticle` is a small particle simulation written in C++ using [raylib](https://www.raylib.com/) and built with [xmake](https://xmake.io/).

The project currently supports:

- Spawning particles at random positions
- Updating particle position and velocity
- Detecting collisions with container edges
- Rendering particles in a raylib window
- A custom `Vector2` type for simulation math
- Basic vector operations and near-zero checks
- Conversion between the custom vector type and raylib's `Vector2`

## Requirements

- A C++ compiler
- xmake
- raylib
- C++20

## Build and run

Debug build:

```sh
xmake
xmake run cpparticle
```

Release build:

```sh
xmake f -m release
xmake
xmake run cpparticle
```

## Project structure

```text
src/
├── main.cpp
├── particle_manager.cpp
├── particle_manager.h
└── vector2.h
xmake.lua
```

## Current development

The simulation now has its own `Vector2` implementation instead of relying on raylib's vector type for internal simulation logic.

This helps keep the simulation and math code separate from the rendering library. Values are converted to raylib types only when needed for rendering.

Collision handling currently includes container-edge collision detection, while particle movement is driven by position and velocity updates.

## Status

This is an early-stage learning project focused on building a particle simulation in C++ incorporating collision detection systems and vector math

Planned development includes improving particle behaviour, better collision handling, math utilities, and rendering.
