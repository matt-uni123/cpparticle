# cpparticle

`cpparticle` is a small particle simulation written in C++ using [raylib](https://www.raylib.com/) and built with [xmake](https://xmake.io/).

The project currently supports:

- Spawning particles at random positions
- Updating particle position and velocity
- Detecting collisions with container edges
- Rendering particles in a raylib window

## Requirements

- A C++ compiler
- xmake
- raylib

## Build and run

```sh
xmake
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
src/
├── main.cpp
├── particle_manager.cpp
└── particle_manager.h
xmake.lua
```

## Status

This is an early-stage learning project. Particle behaviour, collision handling, and rendering are still being developed.
