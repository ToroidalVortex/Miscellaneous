#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
    public:
        vec3() : x(0.0), y(0.0), z(0.0) {}
        vec3(double _xyz) : x(_xyz), y(_xyz), z(_xyz) {}
        vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

        double x, y, z;

        double r() { return x; }
        double g() { return y; }
        double b() { return z; }

        vec3 operator - () const { return vec3(-x, -y, -z); }

        vec3& operator += (const vec3 &v) { x += v.x, y += v.y, z += v.z; return *this; }
        vec3& operator *= (const vec3 &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
        vec3& operator /= (const vec3 &v) { x /= v.x, y /= v.y, z /= v.z; return *this; }

        double length2() const { return x * x + y * y + z * z; }
        double length() const { return sqrt(length2()); }

        bool near_zero() const {
            const double s = 1e-8;
            return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
        }
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using colour = vec3; // RGB colour

// Utility functions

inline std::ostream& operator << (std::ostream &out, const vec3 &v) {
    return out << "[" << v.x << " " << v.y << " " << v.z << "]";
}

vec3 operator + (const vec3 &u, const vec3 &v) { return vec3(u.x + v.x, u.y + v.y, u.z + v.z); }
vec3 operator - (const vec3 &u, const vec3 &v) { return vec3(u.x - v.x, u.y - v.y, u.z - v.z); }
vec3 operator * (const vec3 &u, const vec3 &v) { return vec3(u.x * v.x, u.y * v.y, u.z * v.z); }
vec3 operator / (const vec3 &u, const vec3 &v) { return vec3(u.x/v.x, u.y/v.y, u.z/v.z); }

vec3 operator + (const vec3 &v, const double &f) { return vec3(v.x + f, v.y + f, v.z + f); }
vec3 operator - (const vec3 &v, const double &f) { return vec3(v.x - f, v.y - f, v.z - f); }
vec3 operator * (const vec3 &v, const double &f) { return vec3(v.x * f, v.y * f, v.z * f); }
vec3 operator / (const vec3 &v, const double &f) { return vec3(v.x / f, v.y / f, v.z / f); }

vec3 operator + (const double &f, const vec3 &v) { return v + f; }
vec3 operator - (const double &f, const vec3 &v) { return v - f; }
vec3 operator * (const double &f, const vec3 &v) { return v * f; }

inline vec3 unit_vector(const vec3 &v) {
    return v / v.length();
}

inline double dot(const vec3 &u, const vec3 &v) { 
    return u.x * v.x + u.y * v.y + u.z * v.z; 
}

inline vec3 cross(const vec3 &u, const vec3 &v) { 
    return vec3(u.y * v.z - u.z * v.y, 
                u.z * v.x - u.x * v.z, 
                u.x * v.y - u.y * v.x); 
}

#endif