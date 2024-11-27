#pragma once

#include "hittable.hpp"

class sphere : public hittable {
public:
    sphere(const point3& center, double radius, shared_ptr<material> mat) 
        : center(center)
        , radius(std::fmax(0, radius))
        , mat(mat)
    {}

    //sphere
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = h * h - a * c;

        //check if radius hits the sphere
        if (discriminant < 0) {
            return false;
        }
        auto sqrtd = std::sqrt(discriminant);

        //find the nearest root that lies in the acceptable range
        auto root = (h -sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }
        //save the record
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal); 
        rec.mat = mat;

        return true;
    }
private:
    point3 center;
    double radius; 
    shared_ptr<material> mat;
};