#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

class Camera {
    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
    public:
        Camera(point3 position, point3 target, vec3 up, double vfov, double aspect_ratio) {
            double theta = deg_to_rad(vfov);
            double h = tan(theta/2);
            double viewport_height = 2.0 * h; 
            double viewport_width = aspect_ratio * viewport_height;

            vec3 w = unit_vector(position - target);
            vec3 u = unit_vector(cross(up,w));
            vec3 v = cross(w,u);

            origin = position;
            horizontal = viewport_width * u; 
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;

        }

        Ray get_ray(double u, double v) const {
            return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }
};

#endif