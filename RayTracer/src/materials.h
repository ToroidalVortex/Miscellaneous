#ifndef MATERIALS_H
#define MATERIALS_H

#include "utils.h"

struct hit_record;

class Material {
    public:
        Material() {}

        virtual bool scatter(const Ray &r_in, const hit_record &rec, colour &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material {
    public:
        colour albedo;
    public:
        Lambertian(const colour &_albedo) : albedo(_albedo) {}

        bool scatter(const Ray &r_in, const hit_record &rec, colour &attenuation, Ray &scattered) const override {
            vec3 scatter_direction = rec.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if (scatter_direction.near_zero()) {
                scatter_direction = rec.normal;
            }

            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
};

class Metal : public Material {
    public:
        colour albedo;
        double roughness;
    public:
        Metal(const colour &_albedo, double _roughness) : albedo(_albedo), roughness(clamp(_roughness,0.0,1.0)) {}

        bool scatter(const Ray &r_in, const hit_record &rec, colour &attenuation, Ray &scattered) const override {
            vec3 reflected = reflect(unit_vector(r_in.direction), rec.normal);
            scattered = Ray(rec.p, reflected + roughness*random_vector_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction, rec.normal) > 0.0);
        }
};

class Glass : public Material {
    public:
        double index; // refractive index

    public:
        Glass(double _index) : index(_index) {}

        bool scatter(const Ray &r_in, const hit_record &rec, colour &attenuation, Ray &scattered) const override {
            attenuation = colour(1.0, 1.0, 1.0);
            double ratio = rec.front_face ? (1.0/index) : index;

            vec3 unit_direction = unit_vector(r_in.direction);
            double cos_theta = dot(-unit_direction, rec.normal);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool total_internal_reflection = ratio * sin_theta > 1.0;
            vec3 direction;

            double ref = reflectance(cos_theta, ratio);
            if(total_internal_reflection || ref > random_double()) 
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, ratio);

            scattered = Ray(rec.p, direction);
            return true;
        }
    
    private:
        static double reflectance(double cos_theta, double ref_index) {
            // Schlick's approximation
            double r0 = (1-ref_index) / (1+ref_index);
            r0 = r0*0;
            return r0 + (1-r0)*pow((1-cos_theta),5);
        }
};

#endif