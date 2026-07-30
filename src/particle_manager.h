#include "Vector2.h"
#include <array>
#include <execution>
#include <optional>
#include <raylib.h>
#include <utility>
enum class BoundSide { Left, Right, Top, Bottom };

struct Bounds {
  float left;
  float right;
  float top;
  float bottom;
};

class particle_container {
public:
  Bounds bounds;
  friend class particle_manager;

private:
  particle_container(Bounds bounds) : bounds(bounds) {}
};

class Particle {
public:
  physics::Vector2 coords;
  physics::Vector2 velocity;
  float radius;
  friend class particle_manager;

private:
  Particle(physics::Vector2 coords, physics::Vector2 velocity, float radius)
      : coords(coords), velocity(velocity), radius(radius) {}
  Particle operator=(const Particle &) = delete;
};

class particle_manager {
public:
  particle_manager(float left, float right, float top, float bottom)
      : container(Bounds{left, right, top, bottom}) {}

  void create_particle(physics::Vector2 coords, physics::Vector2 velocity,
                       float radius) {
    particle_pool.emplace_back(Particle(coords, velocity, radius));
  }

  void update();
  void spawn_particles_at_random_pos(int n, float radius);

  std::vector<physics::Vector2> get_coords() const;
  const float get_bound(BoundSide side) const;
  particle_container container;

private:
  std::vector<Particle> particle_pool;

  physics::Vector2 bounded_random_coords();
  void detect_particle_collision(Particle &p1, Particle &p2) const;
  void collision_loop();
  void move_particle(Particle &p);
  std::optional<BoundSide> find_edge_collision(const Particle &p) const;
};
