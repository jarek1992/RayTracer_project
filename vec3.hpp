#pragma once

#include "rtweekend.hpp"

#include <cmath>
#include <cstdlib>
#include <ostream>


//class representing 3demensional vector
class vec3 {
public:
  //variable for x, y and z
  double e[3];

  //default constructor: initializes to (0, 0, 0)
  constexpr vec3() : e{0, 0, 0} {}

  //parameterized constructor: initializes to specific values (e0, e1, e2)
  constexpr vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  //getter methods for individual components (x, y, z))
  constexpr double x() const { return e[0]; }
  constexpr double y() const { return e[1]; }
  constexpr double z() const { return e[2]; }

  //Unary minus operator to negate the vector
  constexpr vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

  //array index operators
  constexpr double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  //addition assignment (v += u)
  vec3 &operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  //multiplication assignment (v *= scalar)
  vec3 &operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  //division assignment (v /= scalar)
  vec3 &operator/=(double t) { 
    return *this *= 1 / t; 
  }

  //length (magnitude) of the vector
  double length() const { 
    return std::sqrt(length_squared()); 
  }

  //length squared (no square root for efficiency)
  constexpr double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  bool near_zero() const {
    //return true if the vector is close to zero in all dimensions.
    auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
  }

  //static methods to generate random vectors
  static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }
  static vec3 random(double min, double max) {
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
  }
};

//point3 is allias for vec3, but useful for geometric clarity in the code
using point3 = vec3;

//vector utility functions

//allows to display vector as (x y z)
inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

//add or subtract components of 2 vectors
inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

//vector subtraction (u - v)
inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

//multiply components of 2 vectors
inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

//multiply by scalar
inline vec3 operator*(double t, const vec3 &v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

//scalar multiplication (v * t)
inline vec3 operator*(const vec3 &v, double t) { 
  return t * v; 
}

//scalar division (v / t)
inline vec3 operator/(const vec3 &v, double t) { 
  return (1 / t) * v; 
}

//dot product of two vectors (u . v)
inline double dot(const vec3 &u, const vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
// cross product
inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

//return unit vector with length = 1 with the same direction to v
inline vec3 unit_vector(const vec3 &v) { 
  return v / v.length(); 
}

//generate a random unit vecto
inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

//generate a random vector on the hemisphere defined by the normal
inline vec3 random_on_hemisphere(const vec3 &normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}

//vec3 reflection function
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}