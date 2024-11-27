#pragma once

#include "hittable.hpp"

//abstract class material
class material {
public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const {
        return false;
    }
};

//class for lambertian material
class lambertian : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        //catch degenerate scatter direction
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction);
        attentuation = albedo;
        return true;    
    }

private:
    color albedo;
};

//class for metal material with reflections
class metal : public material {
public:
    metal(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected);
        attentuation = albedo;
        return true;    
    }

private:
    color albedo;
};

