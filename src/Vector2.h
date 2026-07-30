#include <cmath>
constexpr float EPSILON = 1e-6f;
namespace physics {
struct Vector2 {
  float x;
  float y;

  constexpr Vector2(float x, float y) : x(x), y(y) {}
  constexpr float magnitude() const { return std::sqrt((x * x + y * y)); }
  constexpr float magnitude_squared() const { return x * x + y * y; }

  constexpr float dot(const Vector2 &vec) const {
    return x * vec.x + y * vec.y;
  }
  constexpr Vector2 vector_to(const Vector2 &vec) const {
    return Vector2{vec.x - x, vec.y - y};
  };
  constexpr float distance_to(const Vector2 &vec) const {
    return vector_to(vec).magnitude();
  };
  constexpr float distance_squared_to(const Vector2 &vec) const {
    return vector_to(vec).magnitude_squared();
  };
  constexpr Vector2 normalise() const {
    // Avoid division by zero
    if (is_close_to_zero()) {
      return {0.0, 0.0};
    }
    const auto mag = magnitude();
    return {x / mag, y / mag};
  }
  constexpr Vector2 operator+(const Vector2 &vec) const {
    return {x + vec.x, y + vec.y};
  }
  constexpr Vector2 operator-(const Vector2 &vec) const {
    return {x - vec.x, y - vec.y};
  };
  constexpr Vector2 operator*(const float scalar) const {
    return {scalar * x, scalar * y};
  }
  constexpr Vector2 operator/(const float scalar) const {
    return {x / scalar, y / scalar};
  }
  constexpr Vector2 operator+=(const Vector2 &vec) {
    x = x + vec.x;
    y = y + vec.y;
    return *this;
  }
  constexpr Vector2 operator-=(const Vector2 &vec) {
    x = x - vec.x;
    y = y - vec.y;
    return *this;
  }
  constexpr Vector2 operator*=(const float scalar) {
    x = x * scalar;
    y = y * scalar;
    return *this;
  }
  constexpr Vector2 operator/=(const float scalar) {
    x = x / scalar;
    y = y / scalar;
    return *this;
  }

  constexpr bool operator==(const Vector2 &vec) const {
    return x == vec.x && y == vec.y;
  };
  constexpr bool operator!=(const Vector2 &vec) const {
    return x != vec.x || y != vec.y;
  }

  constexpr bool is_close_to_zero() const {
    float magSq = magnitude_squared();
    return magSq < EPSILON * EPSILON;
  }

  constexpr float angle() const { return std::atan2(y, x); }
  constexpr Vector2 perpendicular() const { return {y * -1.0f, x}; };

  constexpr Vector2 reflect(const Vector2 &normal, const Vector2 &v) const {
    const float dot = normal.dot(v);
    const Vector2 reflection_offset = normal * (dot * 2.0f);
    return v - reflection_offset;
  }
};
} // namespace physics
