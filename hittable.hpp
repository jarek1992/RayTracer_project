#pragma once

#include "vec3.hpp"
#include "interval.hpp"
#include "ray.hpp"

//holds information about the intersection between a ray and an object
class hit_record {
public:
    point3 p;         //intersection point
    vec3 normal;      //normal vector at the intersection point
    double t;         //distance along the ray to the intersection point
    bool front_face;  //flag for front/back face hit;

    //sets the hit record normal vector, 'outward_normal' is assumed to have unit length
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};
//virtual abstract class for hittable objects
class hittable {
public:
    virtual ~hittable() = default;
    //pure virtual method that must be implemented by derived classes
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};