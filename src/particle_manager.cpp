#include "particle_manager.h"
#include <iostream>
#include <optional>
#include <ostream>
#include <random>
#include <raylib.h>
#include <unistd.h>

std::mt19937 rng{std::random_device{}()};
float random_float(float min, float max) {
  std::uniform_real_distribution<float> distrbution(min, max);
  return distrbution(rng);
}

const float particle_manager::get_bound(BoundSide side) const {
  switch (side) {
  case BoundSide::Left:
    return container.bounds.left;
  case BoundSide::Right:
    return container.bounds.right;
  case BoundSide::Top:
    return container.bounds.top;
  case BoundSide::Bottom:
    return container.bounds.bottom;
  }
}

Vector2 particle_manager::bounded_random_coords() {
  float x = random_float(0, get_bound(BoundSide::Right));
  float y = random_float(0, get_bound(BoundSide::Top));
  Vector2 rand_coords{x, y};
  std::cout << "Random coords are: " << rand_coords.x << ',' << rand_coords.y
            << '\n';
  return rand_coords;
}

void particle_manager::update() {
  if (!particle_pool.empty()) {
    for (auto &p : particle_pool) {
      move_particle(p);
    }
  }
}

void particle_manager::spawn_particles_at_random_pos(int n) {
  for (int i = 0; i < n; i++) {
    create_particle(bounded_random_coords(), {10.0, 9.0});
  }
}

std::vector<Vector2> particle_manager::get_coords() const {
  std::vector<Vector2> coords_vec;
  for (const auto &p : particle_pool) {
    coords_vec.emplace_back(Vector2{p.coords.x, p.coords.y});
  }
  return coords_vec;
}

std::optional<BoundSide>
particle_manager::find_edge_collision(const Particle &p) const {
  if (p.coords.x + p.velocity.x >= container.bounds.right) {
    return BoundSide::Right;
  }
  if (p.coords.x + p.velocity.x <= container.bounds.left) {
    return BoundSide::Left;
  }
  if (p.coords.y + p.velocity.y >= container.bounds.top) {
    return BoundSide::Top;
  }
  if (p.coords.y + p.velocity.y <= container.bounds.bottom) {
    return BoundSide::Bottom;
  }

  return std::nullopt;
}

void update_position(Particle &p) {
  p.coords.x += p.velocity.x;
  p.coords.y += p.velocity.y;
}
void particle_manager::move_particle(Particle &p) {
  auto has_collided = find_edge_collision(p);

  if (!has_collided) {
    update_position(p);

  } else if (has_collided == BoundSide::Top ||
             has_collided == BoundSide::Bottom) {
    p.velocity.y *= -1;
    update_position(p);

  } else if (has_collided == BoundSide::Left ||
             has_collided == BoundSide::Right) {
    p.velocity.x *= -1;
    update_position(p);
  }
  {
  }
}
