#include <cmath>
#include <concepts>

constexpr float EPSILON = 1e-6f;
template <typename T>
concept Scalar = std::integral<T> || std::floating_point<T>;

namespace geometry {
template <Scalar T> struct Vector2 {
  T x;
  T y;

  constexpr Vector2(T x, T y) : x(x), y(y) {}
  constexpr T magnitude() const { return std::sqrt((x * x + y * y)); }
  constexpr T magnitude_squared() const { return x * x + y * y; }
  constexpr T dot(const Vector2<T> &vec) const { return x * vec.x + y * vec.y; }
  constexpr Vector2<T> vector_to(const Vector2<T> &vec) const {
    return Vector2<T>{vec.x - x, vec.y - y};
  };
  constexpr T distance_to(const Vector2<T> &vec) const {
    return vector_to(vec).magnitude();
  };
  constexpr T distance_squared_to(const Vector2<T> &vec) const {
    return vector_to(vec).magnitude_squared();
  };
  constexpr Vector2<T> normalise() const {
    // Avoid division by zero
    if (is_close_to_zero()) {
      return {0.0, 0.0};
    }
    const auto mag = magnitude();
    return {x / mag, y / mag};
  }
  constexpr Vector2<T> operator+(const Vector2<T> &vec) const {
    return {x + vec.x, y + vec.y};
  }
  constexpr Vector2<T> operator-(const Vector2<T> &vec) const {
    return {x - vec.x, y - vec.y};
  };
  constexpr Vector2<T> operator*(const T scalar) const {
    return {scalar * x, scalar * y};
  }
  constexpr Vector2<T> operator/(const T scalar) const {
    return {x / scalar, y / scalar};
  }
  constexpr Vector2<T> operator+=(const Vector2<T> &vec) {
    x = x + vec.x;
    y = y + vec.y;
    return *this;
  }
  constexpr Vector2<T> operator-=(const Vector2<T> &vec) {
    x = x - vec.x;
    y = y - vec.y;
    return *this;
  }
  constexpr Vector2<T> operator*=(const T scalar) {
    x = x * scalar;
    y = y * scalar;
    return *this;
  }
  constexpr Vector2<T> operator/=(const T scalar) {
    x = x / scalar;
    y = y / scalar;
    return *this;
  }
  constexpr bool operator==(const Vector2<T> &vec) const {
    return x == vec.x && y == vec.y;
  };
  constexpr bool operator!=(const Vector2<T> &vec) const {
    return x != vec.x || y != vec.y;
  }
  constexpr bool is_close_to_zero() const {
    T magSq = magnitude_squared();
    return magSq < EPSILON * EPSILON;
  }
  constexpr T angle() const { return std::atan2(y, x); }
  constexpr Vector2<T> perpendicular() const { return {y * -1.0f, x}; };
  constexpr Vector2<T> reflect(const Vector2<T> &normal,
                               const Vector2<T> &v) const {
    const T dot = normal.dot(v);
    const Vector2<T> reflection_offset = normal * (dot * 2.0f);
    return v - reflection_offset;
  }
};
} // namespace geometry
