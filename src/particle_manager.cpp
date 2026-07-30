#include "particle_manager.h"
#include <cmath>
#include <iostream>
#include <optional>
#include <ostream>
#include <random>
#include <raylib.h>
#include <stdexcept>
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
  throw std::invalid_argument("Invalid BoundSide");
}

physics::Vector2 particle_manager::bounded_random_coords() {
  float x = random_float(0, get_bound(BoundSide::Right));
  float y = random_float(0, get_bound(BoundSide::Top));
  physics::Vector2 rand_coords{x, y};
  std::cout << "Random coords are: " << rand_coords.x << ',' << rand_coords.y
            << '\n';
  return rand_coords;
}

void particle_manager::update() {
  if (!particle_pool.empty()) {
    collision_loop();
    for (auto &p : particle_pool) {
      move_particle(p);
    }
  }
}

void particle_manager::spawn_particles_at_random_pos(int n, float radius) {
  for (int i = 0; i < n; i++) {
    create_particle(bounded_random_coords(), {10.0, 9.0}, radius);
  }
}

std::vector<physics::Vector2> particle_manager::get_coords() const {
  std::vector<physics::Vector2> coords_vec;
  for (const auto &p : particle_pool) {
    coords_vec.emplace_back(physics::Vector2{p.coords.x, p.coords.y});
  }
  return coords_vec;
}

bool particle_manager::particle_collision(const Particle &p1,
                                          const Particle &p2) const {
  auto delta_x = p1.coords.x - p2.coords.x;
  auto delta_y = p1.coords.y - p2.coords.y;
  auto distance = std::sqrt(((delta_x * delta_x) + (delta_y * delta_y)));

  if (distance <= (p1.radius + p2.radius)) {
    const float magnitude = sqrt((delta_x * delta_x) + (delta_y + delta_y));
    const physics::Vector2 unit_normal_vector = {(delta_x / magnitude),
                                                 (delta_y / magnitude)};
  }
  return false;
}

void particle_manager::collision_loop() {
  for (std::size_t i = 0; i < particle_pool.size(); ++i) {
    for (std::size_t j = i + 1; j < particle_pool.size(); ++j) {
      if (particle_collision(particle_pool[i], particle_pool[j])) {
        std::cout << "COLLISION";
      }
    }
  }
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
