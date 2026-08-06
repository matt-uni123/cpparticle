#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP
#include "Vector2.hpp"
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
#endif // !COMMON_TYPES_HPP
