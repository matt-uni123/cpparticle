#include "particle_manager.h"
#include <iostream>
#include <raylib.h>

int main(int argc, char **argv) {
  constexpr float windowWidth = 800.0f;
  constexpr float windowHeight = 600.0f;
  constexpr float radius = 30.0f;

  InitWindow(windowWidth, windowHeight, "Window");
  SetTargetFPS(60);
  auto pm = particle_manager(radius, windowWidth - radius,
                             windowHeight - radius, radius);

  pm.spawn_particles_at_random_pos(5);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);
    auto coords = pm.get_coords();

    for (std::size_t i = 0; i < coords.size(); ++i) {
      DrawCircleV(coords[i], radius, BLUE);
    }

    pm.update();

    EndDrawing();
  }
  return 0;
}
