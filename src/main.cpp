#include "particle_manager.h"
#include <raylib.h>
int main(int argc, char **argv) {
  constexpr float windowWidth = 800.0f;
  constexpr float windowHeight = 600.0f;
  constexpr float radius = 10.0f;
  InitWindow(windowWidth, windowHeight, "Window");
  SetTargetFPS(60);

  particle_manager manager(
      {.bounds = {.left = 0.0f, .right = 800.0f, .top = 600.0f, .bottom = 0.0f},
       .max_particles = 40});
  manager.spawn_particles_at_random_pos(radius);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);
    std::vector<geometry::Vector2<float>> coords = manager.get_coords();
    Vector2 Vec2;

    for (std::size_t i = 0; i < coords.size(); ++i) {
      Vec2.x = coords[i].x;
      Vec2.y = coords[i].y;

      DrawCircleV(Vec2, radius, BLUE);
    }

    manager.update();

    EndDrawing();
  }
  return 0;
}
