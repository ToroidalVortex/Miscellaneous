#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "utils.h"

class Material;

struct hit_record {
    point3 p;
    double t;
    vec3 normal;
    bool front_face;
    shared_ptr<Material> material;

    void set_face_normal(const Ray &r, const vec3 &outward_normal) {
        front_face = dot(r.direction, outward_normal) < 0; 
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Primitive {
    public:
        virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

class Sphere : public Primitive {
    public:
        point3 position;
        double radius;
        shared_ptr<Material> material;
    public:
        Sphere() {}
        Sphere(point3 _position, double _radius, shared_ptr<Material> _material) 
            : position(_position), radius(_radius), material(_material) {}

        //virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
        bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {
            vec3 oc = r.origin - position;
            double a = r.direction.length2();
            double b = dot(oc, r.direction);
            double c = oc.length2() - radius*radius;            
            double d = b*b - a*c;

            if(d < 0) return false;

            double sqrtd = sqrt(d);
            double root = (-b - sqrtd) / a;

            if (root < t_min || t_max < root) {
                root = (-b + sqrtd) / a;
                if(root < t_min || t_max < root) return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - position) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.material = material;

            return true;
        }

};

class Triangle : public Primitive {

};

class Square : public Primitive {

};

#endif