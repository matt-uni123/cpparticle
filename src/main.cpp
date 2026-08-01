#include "particle_manager.h"
#include <raylib.h>
int main(int argc, char **argv) {
  constexpr float windowWidth = 800.0f;
  constexpr float windowHeight = 600.0f;
  constexpr float radius = 15.0f;
  InitWindow(windowWidth, windowHeight, "Window");
  SetTargetFPS(60);

  ParticleManager::Config config{
      .container_area = {.width = windowWidth, .height = windowHeight},
      .max_particles = 20};

  auto manager = ParticleManager(config);

  manager.spawn_particles_at_random_pos(radius);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    std::vector<geometry::Vector2<float>> coords = manager.get_coords();
    Vector2 Vec2;

    for (std::size_t i = 0; i < coords.size(); ++i) {
      Vec2.x = coords[i].x;
      Vec2.y = coords[i].y;

      DrawCircleV(Vec2, radius, RED);
    }

    manager.update();

    EndDrawing();
  }
  return 0;
}
