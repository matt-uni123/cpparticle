#include "Vector2.h"
#include <vector>

class Particle {
public:
  geometry::Vector2<float> coords;
  geometry::Vector2<float> velocity;
  float radius;
  friend class ParticleManager;

private:
  Particle(geometry::Vector2<float> coords, geometry::Vector2<float> velocity,
           float radius)
      : coords(coords), velocity(velocity), radius(radius) {}

  Particle &operator=(const Particle &) = delete;
};

class ParticleManager {
public:
  struct Area {
    float width;
    float height;
  };
  struct Config {
    Area container_area;
    int max_particles;
  };
  struct Collisions {
    bool left;
    bool right;
    bool top;
    bool bottom;

    bool any() { return left || right || top || bottom; }
    bool none() { return !any(); }
  };
  explicit ParticleManager(const Config &config) : config(config) {}
  void update();
  void create_particle(geometry::Vector2<float> coords,
                       geometry::Vector2<float> velocity, float radius) {
    particle_pool.emplace_back(Particle(coords, velocity, radius));
  }
  void spawn_particles_at_random_pos(float radius, float min_x_velocity,
                                     float min_y_velocity, float max_x_velocity,
                                     float max_y_velocity);
  std::vector<geometry::Vector2<float>> get_coords() const;

private:
  Config config;
  std::vector<Particle> particle_pool;
  geometry::Vector2<float> bounded_random_coords(float radius);
  void move_particle(Particle &p);

  // Collision systems:
  void detect_particle_collision(Particle &p1, Particle &p2);
  void collision_resolution(Particle &p1, Particle &p2,
                            const float &distance_sq);
  Collisions container_collisions(const Particle &p) const;
  void keep_inside_container(Particle &p);
  void collision_loop();
};
