#include "particle_manager.h"
#include <raylib.h>
int main(int argc, char **argv) {
  constexpr float windowWidth = 800.0f;
  constexpr float windowHeight = 600.0f;
  constexpr float radius = 30.0f;

  InitWindow(windowWidth, windowHeight, "Window");
  SetTargetFPS(60);
  auto pm = particle_manager(radius, windowWidth - radius,
                             windowHeight - radius, radius);

  pm.spawn_particles_at_random_pos(5, radius);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);
    auto coords = pm.get_coords();
    Vector2 Vec2;

    for (std::size_t i = 0; i < coords.size(); ++i) {
      Vec2.x = coords[i].x;
      Vec2.y = coords[i].y;

      DrawCircleV(Vec2, radius, BLUE);
    }

    pm.update();

    EndDrawing();
  }
  return 0;
}
