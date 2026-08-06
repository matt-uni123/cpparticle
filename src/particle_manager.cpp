#include "particle_manager.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <random>
#include <raylib.h>
#include <unistd.h>
#include <vector>

std::mt19937 rng{std::random_device{}()};
float random_float(float min, float max) {
  std::uniform_real_distribution<float> distrbution(min, max);
  return distrbution(rng);
}
void ParticleManager::update() {
  if (!paused && !particle_pool.empty()) {
    cell_list.rebuild(particle_pool);
    for (auto &p : particle_pool) {
      move_particle(p);
      collision_loop();
      keep_inside_container(p);
    }
  }
}

geometry::Vector2<float> ParticleManager::bounded_random_coords(float radius) {
  float x = random_float(radius, config.container_area.width - radius);
  float y = random_float(radius, config.container_area.height - radius);
  geometry::Vector2<float> rand_coords{x, y};
  return rand_coords;
}

void ParticleManager::spawn_particles_at_random_pos(float radius, float maxX,
                                                    float maxY) {
  for (int i = 0; i < config.max_particles; i++) {
    const float x = random_float(-maxX, maxX);
    const float y = random_float(-maxX, maxY);
    create_particle(bounded_random_coords(radius), {x, y}, radius);
  }
}

std::vector<geometry::Vector2<float>> ParticleManager::get_coords() const {
  std::vector<geometry::Vector2<float>> coords_vec;
  for (const auto &p : particle_pool) {
    coords_vec.emplace_back(geometry::Vector2<float>{p.coords.x, p.coords.y});
  }
  return coords_vec;
}

ParticleManager::Collisions
ParticleManager::container_collisions(const Particle &p) const {
  const auto &area = config.container_area;
  const auto minimumX = p.radius;
  const auto maximumX = area.width - p.radius;
  const auto minimumY = minimumX;
  const auto maximumY = area.height - p.radius;

  ParticleManager::Collisions collisions{};
  collisions.left = p.coords.x <= minimumX;
  collisions.right = p.coords.x >= maximumX;
  collisions.top = p.coords.y <= minimumY;
  collisions.bottom = p.coords.y >= maximumY;
  return collisions;
}

// TODO: Clean this up, put in seperate header.
void ParticleManager::collision_resolution(Particle &p1, Particle &p2,
                                           const float &distance_sq) {
  const auto displacement = p1.coords.vector_to(p2.coords);
  auto distance = std::sqrt(distance_sq);
  if (distance == 0) {
    const auto normal = {1, 0};
  }
  const auto normal = displacement / distance;
  const float overlap = (p1.radius + p2.radius) - distance;

  if (overlap > 0.0f) {
    // Correct position if circles overlap
    const auto half_correction = normal * (overlap * 0.5f);
    p1.coords = p1.coords - half_correction;
    p2.coords = p2.coords + half_correction;
  }

  // Clamp function ran each time particle coordinates are moved
  // Ensures particles are not moved outside of bounds.
  keep_inside_container(p1);
  keep_inside_container(p2);

  const auto relative_vel = p2.velocity - p1.velocity;
  const auto normal_speed = relative_vel.dot(normal);
  if (normal_speed < 0) {
    const float restitution = 0.7;
    const float mass = 1;
    const auto impulse = -1 * (((mass + restitution) * normal_speed) / 2);
    const geometry::Vector2<float> impulse_vec = normal * impulse;
    p1.velocity -= impulse_vec;
    p2.velocity += impulse_vec;

    keep_inside_container(p1);
    keep_inside_container(p2);
  }
}

void ParticleManager::keep_inside_container(Particle &p) {
  const auto &area = config.container_area;
  p.coords.x = std::clamp(p.coords.x, p.radius, area.width - p.radius);
  p.coords.y = std::clamp(p.coords.y, p.radius, area.width - p.radius);
}

void ParticleManager::detect_particle_collision(Particle &p1, Particle &p2) {
  auto distance_sq = p1.coords.distance_squared_to(p2.coords);
  if (distance_sq <= (p1.radius + p2.radius) * (p1.radius + p2.radius)) {
    collision_resolution(p1, p2, distance_sq);
  }
}

// TODO: FIX EVIL O(n)^2 loop >:(
void ParticleManager::collision_loop() {
  for (std::size_t i = 0; i < particle_pool.size(); ++i) {
    for (std::size_t j = i + 1; j < particle_pool.size(); ++j) {
      detect_particle_collision(particle_pool[i], particle_pool[j]);
    }
  }
}

void update_position(Particle &p) {
  p.coords.x += p.velocity.x;
  p.coords.y += p.velocity.y;
}

void ParticleManager::move_particle(Particle &p) {
  auto collisions = container_collisions(p);

  if (collisions.none()) {
    update_position(p);
    return;
  }
  bool corner_collision = ((collisions.top || collisions.bottom) &&
                           (collisions.left || collisions.right));

  if (corner_collision) {
    p.velocity.y *= -1;
    update_position(p);
    p.velocity.x *= -1;
    update_position(p);
  }
  if (collisions.top || collisions.bottom) {
    p.velocity.y *= -1;
    update_position(p);
  }
  if (collisions.left || collisions.right) {
    p.velocity.x *= -1;
    update_position(p);
  }
}
