#pragma once

#include "hittable.hpp"

//abstract class material
class material {
public:
    virtual ~material() = default;

    // /**
    //  * @brief Scatter the incoming ray according to the material's properties.
    //  * 
    //  * @param r_in The incoming ray.
    //  * @param rec The hit record containing information about the hit point.
    //  * @param attenuation The color attenuation of the material.
    //  * @param scattered The scattered ray.
    //  * @return true if the ray is scattered, false otherwise.
    //  */

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
};

//class for lambertian material
class lambertian : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        //catch degenerate scatter direction
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;    
    }

private:
    color albedo;
};

//class for metal material with reflections
class metal : public material {
public:
    metal(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;    
    }

private:
    color albedo;
};

