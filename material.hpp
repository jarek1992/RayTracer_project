#pragma once

#include "hittable.hpp"

//abstract class material
class material {
public:
    virtual ~material() = default;

    //   @brief Scatter the incoming ray according to the material's properties.
    //   
    //   @param r_in The incoming ray.
    //   @param rec The hit record containing information about the hit point.
    //   @param attenuation The color attenuation of the material.
    //   @param scattered The scattered ray.
    //   @return true if the ray is scattered, false otherwise.

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
    metal(const color& albedo, double fuzz) 
        : albedo(albedo)
        , fuzz(fuzz < 1 ? fuzz : 1) //condition for fuzziness 
        {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);    
    }

private:
    color albedo;
    double fuzz;
};

//class for dielectric material always refracts
class dielectric : public material {
public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0); //always white, because translucent doesnt change color
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index; //calculation of the refractive index

        vec3 unit_direction = unit_vector(r_in.direction()); //the unit direction vector of the incoming ray.
        vec3 refracted = refract(unit_direction,rec.normal, ri); //calculate refracted ray

        scattered = ray(rec.p, refracted); //creates new scattered ray with beginning = rec.p and refract direction = refracted 
        return true;
    }
private:
    //refractive index - n
    double refraction_index;
};