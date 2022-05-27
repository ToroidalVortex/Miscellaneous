#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        point3 origin;
        vec3 direction;
        
    public:
        Ray() {}
        Ray(const point3 _origin, const vec3 _direction) : origin(_origin), direction(_direction) {}

        point3 at(double t) const {
            return origin + t*direction;
        }
};

#endif