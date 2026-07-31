#include "Vector2.h"
#include <optional>
#include <vector>
enum class BoundSide { Left, Right, Top, Bottom };

class Particle {
public:
  geometry::Vector2<float> coords;
  geometry::Vector2<float> velocity;
  float radius;
  friend class particle_manager;

private:
  Particle(geometry::Vector2<float> coords, geometry::Vector2<float> velocity,
           float radius)
      : coords(coords), velocity(velocity), radius(radius) {}

  Particle &operator=(const Particle &) = delete;
};

class particle_manager {
public:
  struct Bounds {
    float left;
    float right;
    float top;
    float bottom;
  };
  struct Config {
    Bounds bounds;
    int max_particles;
  };
  explicit particle_manager(const Config &config) : config(config) {}

  void create_particle(geometry::Vector2<float> coords,
                       geometry::Vector2<float> velocity, float radius) {
    particle_pool.emplace_back(Particle(coords, velocity, radius));
  }

  void update();
  void spawn_particles_at_random_pos(float radius);

  std::vector<geometry::Vector2<float>> get_coords() const;
  const float get_bound(BoundSide side) const;

private:
  Config config;
  std::vector<Particle> particle_pool;

  geometry::Vector2<float> bounded_random_coords(float radius);

  void move_particle(Particle &p);
  void detect_particle_collision(Particle &p1, Particle &p2) const;
  std::optional<BoundSide> find_edge_collision(const Particle &p) const;
  void collision_loop();
};
