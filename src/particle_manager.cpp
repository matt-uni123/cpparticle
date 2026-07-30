#include "particle_manager.h"
#include <cmath>
#include <cstdlib>
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
  float x = random_float(30.f, get_bound(BoundSide::Right) - 30.0f);
  float y = random_float(30.f, get_bound(BoundSide::Top) - 30.f);
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
    create_particle(bounded_random_coords(), {5.0, 3.0}, radius);
  }
}

std::vector<physics::Vector2> particle_manager::get_coords() const {
  std::vector<physics::Vector2> coords_vec;
  for (const auto &p : particle_pool) {
    coords_vec.emplace_back(physics::Vector2{p.coords.x, p.coords.y});
  }
  return coords_vec;
}

// TODO: Clean this up, put in seperate header.
void collision_resolution(Particle &p1, Particle &p2,
                          const float &distance_sq) {
  const auto displacement = p1.coords.vector_to(p2.coords);

  auto distance = std::sqrt(distance_sq);
  if (distance == 0) {
    const auto normal = {1, 0};
  }
  const auto normal = displacement / distance;
  std::cout << "Normal magnitude: " << normal.magnitude() << '\n';
  const float overlap = (p1.radius + p2.radius) - distance;
  const auto is_overlap = overlap > 0;

  const auto p1_prime = p1.coords - normal * overlap / 2;
  const auto p2_prime = p2.coords - normal * overlap / 2;
  p1.coords = p1_prime;
  p2.coords = p2_prime;

  const auto relative_vel = p2.velocity - p1.velocity;
  const auto normal_speed = relative_vel.dot(normal);

  if (normal_speed < 0) {
    // Hardcoded restitution: 0.5
    // Hardcoded mass = 1.0
    const auto impulse = -1 * (((1 + 0.9) * normal_speed) / 2);
    const physics::Vector2 impulse_vec = normal * impulse;
    p1.velocity -= impulse_vec;
    p2.velocity += impulse_vec;
    const auto v_rel_after = p2.velocity - p1.velocity;
    const auto v_n_after = v_rel_after.dot(normal);
  }
}

void particle_manager::detect_particle_collision(Particle &p1,
                                                 Particle &p2) const {
  auto distance_sq = p1.coords.distance_squared_to(p2.coords);
  if (distance_sq <= (p1.radius + p2.radius) * (p1.radius + p2.radius)) {
    collision_resolution(p1, p2, distance_sq);
  }
}

// TODO: FIX EVIL O(n)^2 loop >:(
void particle_manager::collision_loop() {
  for (std::size_t i = 0; i < particle_pool.size(); ++i) {
    for (std::size_t j = i + 1; j < particle_pool.size(); ++j) {
      detect_particle_collision(particle_pool[i], particle_pool[j]);
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
