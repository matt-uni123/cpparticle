#include <cmath>
namespace physics {
struct Vector2 {
  float x;
  float y;

  constexpr Vector2(float x, float y) : x(x), y(y) {}
  constexpr float length() const { return std::sqrt((x * x + y * y)); }
  constexpr float length_squared() const { return x * x + y * y; }

  constexpr float dot(const Vector2 &vec) const {
    return x * vec.x + y * vec.y;
  }
  constexpr Vector2 normalise() const {
    if (is_close_to_zero()) {
      return {0.0, 0.0};
    }
    const auto len = length();
    return {x / len, y / len};
  }
  constexpr Vector2 direction(const Vector2 &vec) const {
    return Vector2{vec.x - x, vec.y - y};
  };
  constexpr float direction_sqaured(const Vector2 &vec) const {
    const auto dx = vec.x - x;
    const auto dy = vec.y - y;
    return dx * dx + dy * dy;
  };
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
    return {scalar / x, scalar / y};
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
    float lengthSq = length_squared();
    return lengthSq < 1.0e-30;
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
