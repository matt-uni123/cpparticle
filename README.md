# cpparticle

A small particle simulation written in C++ with raylib.

This project is mainly a way for me to learn C++ game/physics programming, including vector math, particle movement, collision handling, and structuring a project.

## Current features

- Particle spawning at random coordinates
- Position and velocity updates
- Collision with the simulation bounds
- Collision with other particles
- Particle rendering with raylib

- Custom `physics::Vector2` implementation
- Vector magnitude and squared magnitude
- Dot products
- Vector normalization
- Arithmetic operators
- Angle and perpendicular-vector helpers
- Vector reflection
  
## Dependencies

- C++
- [raylib](https://www.raylib.com/)
- [xmake](https://xmake.io/)
- 
Dependencies are handled through xmake.

## Build

Clone the repository and run:

```sh
xmake
```

Then start the simulation with:

```sh
xmake run cpparticle
```

For a release build:

```sh
xmake f -m release
xmake
xmake run cpparticle
```

## Project structure

```text
cpparticle/
├── src/
│   ├── Vector2.h
│   ├── main.cpp
│   ├── particle_manager.cpp
│   └── particle_manager.h
├── xmake.lua
└── README.md
```

## About

This is an early-stage learning project, so the implementation and structure will change as I learn.

Current areas of focus include improving collision handling, particle behaviour, vector math, and separating simulation logic from rendering.
