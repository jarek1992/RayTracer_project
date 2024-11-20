#pragma once

#include "ray.hpp"
#include "vec3.hpp"

class hit_record {
public:
  point3 p;
  vec3 normal;
  double t;
  bool front_face;

  void set_face_normal(const ray &r, const vec3 &outward_normal) {
    // Sets the hit record normal vector.

    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

//virtual abstract class
class hittable {
public:
  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};
