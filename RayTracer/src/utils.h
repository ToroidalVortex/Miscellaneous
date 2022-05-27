#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <vector>

// Ubiquitous Headers
#include "ray.h"
#include "vec3.h"

// Common Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants 
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
double deg_to_rad(double deg) {
    return deg * pi / 180.0;
}
double rad_to_deg(double rad) {
    return rad * 180.0 / pi;
}

double random_double() {
    // Returns random number between 0.0 and 0.9999... 
    return rand() / (RAND_MAX + 1.0);
}
double random_double(double min, double max) {
    // Returns random number between min and max*0.9999....
    return min + (max-min) * random_double();
}

vec3 random_vector() {
    return vec3(random_double(), random_double(), random_double());
}
vec3 random_vector(double min, double max) {
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

vec3 random_vector_in_unit_sphere() {
    // random_vector(-1,1) creates a random vector within a 2x2x2 cube centered on the origin
    // This biases the result giving diagonal vectors a higher probability, so we keep going
    // util a vector lands inside a unit sphere contained within the cube. Eliminates bias.
    while (true) {
        vec3 p = random_vector(-1,1);
        if(p.length() <= 1) return p;
    }
    
}
vec3 random_vector_in_unit_hemisphere(const vec3 &normal) {
    vec3 p = random_vector_in_unit_sphere();
    if (dot(p, normal) > 0.0) return p;
    else return -p;
}
vec3 random_unit_vector() {
    // use random vector in unit sphere to eliminate directional bias from rectangle corners.
    return unit_vector(random_vector_in_unit_sphere());
}

double clamp(double x, double min, double max) {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

vec3 reflect(const vec3 &v, const vec3 &n) {
    // v is the incident vector and n is the unit normal vector of the surface.
    return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3 &v, const vec3 &n, double ratio) {
    double cos_theta = dot(-v, n) / v.length();
    vec3 perp = ratio * (v + cos_theta * n);
    vec3 para = -sqrt(1.0 - perp.length2()) * n;
    return perp + para;
}


#endif