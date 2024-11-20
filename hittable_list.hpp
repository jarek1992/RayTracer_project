#pragma once

#include "hittable.hpp"

#include <vector>

class hittable_list : public hittable {
public:
  std::vector<std::shared_ptr<hittable>> objects;
  // default constructor
  hittable_list() {}
  // constructor with one argument added to the list
  hittable_list(shared_ptr<hittable> object) { add(object); }
  // remove objects from the list
  void clear() { objects.clear(); }
  // add new object to the list
  void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

  // Ensure the signature matches that of hittable's hit function
  bool hit(const ray &r, double t_min, double t_max,
           hit_record &rec) const override {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (const auto &object : objects) {
      if (object->hit(r, t_min, closest_so_far, temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }
    return hit_anything;
  }
};