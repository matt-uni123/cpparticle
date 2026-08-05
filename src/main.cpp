#include "cxxopts.hpp"
#include "particle_manager.h"
#include <iostream>
#include <raylib.h>
int main(int argc, char **argv) {
  int particle_amount{};
  int thread_amount{};
  bool benchmark_mode{};
  cxxopts::Options options("paraticle simulator",
                           "Parallel particle simulator made in c++");
  options.add_options()("p, particles", "Amount of particles",
                        cxxopts::value<int>()->default_value("100"))(
      "t, threads", "Amount of  worker threads to use",
      cxxopts::value<int>()->default_value("1"))(
      "s, seed", "Random seed", cxxopts::value<int>()->default_value("42"))(
      "b, benchmark", "Run program in benchmark mode",
      cxxopts::value<bool>()->default_value("0"))("h,help", "Show help");

  try {
    const auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help() << '\n';
      return 0;
    }
    particle_amount = result["particles"].as<int>();
    thread_amount = result["threads"].as<int>();
    benchmark_mode = result["benchmark"].as<bool>();

    if (benchmark_mode) {
      // Add benchmark mode code here.
      //
    }
  } catch (const cxxopts::exceptions::exception &err) {
    std::cerr << "Error: " << err.what() << '\n';
  }

  constexpr float windowWidth = 1600.0f;
  constexpr float windowHeight = 1000.0f;

  InitWindow(windowWidth, windowHeight, "Window");
  SetTargetFPS(60);

  ParticleManager::Config config{
      .container_area = {.width = windowWidth, .height = windowHeight},
      .max_particles = particle_amount};

  auto manager = ParticleManager(config);

  // Customize particles
  constexpr float radius = 6.0f;
  constexpr float maxX = 15.0f;
  constexpr float maxY = 15.0f;

  // Change initial x,y velocity range, initial velocity will be random in range
  // of: -max <= velocity <= max
  manager.spawn_particles_at_random_pos(radius, maxX, maxY);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    std::vector<geometry::Vector2<float>> coords = manager.get_coords();
    Vector2 Vec2;

    DrawFPS(0, 0);
    if (IsKeyPressed(KEY_SPACE)) {
      manager.paused = !manager.paused;
    }

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
