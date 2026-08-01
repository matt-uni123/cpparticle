#include "particle_manager.h"
#include <raylib.h>
int main(int argc, char **argv) {
  constexpr float windowWidth = 800.0f;
  constexpr float windowHeight = 600.0f;

  InitWindow(windowWidth, windowHeight, "Window");
  SetTargetFPS(60);

  ParticleManager::Config config{
      .container_area = {.width = windowWidth, .height = windowHeight},
      .max_particles = 20};

  auto manager = ParticleManager(config);

  // Customize particles
  constexpr float radius = 15.0f;
  constexpr float min_x_velocity = -10.0f;
  constexpr float min_y_velocity = -10.0f;
  constexpr float max_x_velocity = 10.0f;
  constexpr float max_y_velocity = 10.0f;

  // Change initial x,y velocity range, initial velocity will be random in range
  // of: min <= velocity <= max
  manager.spawn_particles_at_random_pos(radius, min_x_velocity, min_y_velocity,
                                        max_x_velocity, max_y_velocity);

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
