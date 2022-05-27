/*
    Name:   John Shafe-Purcell
    Date:   December 20, 2020
    Course: COIS 4480H - Computer Graphics
    
    Final Project: Ray Tracer

    This is a minimalistic ray tracing program. 

*/

// "stb_image_write.h" is a public domain image writing header 
// https://github.com/nothings/stb/blob/master/stb_image_write.h

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "primitives.h"
#include "materials.h"
#include "camera.h"
#include "scene.h"
#include "utils.h"

#include <iostream>

// Struct to store the colour data of each pixel
struct Colour {
    unsigned char R, G, B;
};

colour ray_colour(const Ray& r, const Scene &world, int depth) {
    hit_record rec;

    // If max depth reached just return a clear colour
    if(depth <= 0) {
        return colour(0,0,0);
    }

    if(world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        colour attentuation;
        if (rec.material->scatter(r,rec,attentuation,scattered)) {
            return attentuation * ray_colour(scattered, world, depth-1);
        }
        return colour(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction);
    double t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.25, 0.35, 1.0);
}

int main() {

    // Define image dimensions
    const int image_height = 225;
    const int image_width  = 400;
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Array to contain pixel data
    Colour data[image_height][image_width];
    
    // World
    Scene world;

    auto ground_material = make_shared<Lambertian>(colour(0.8,0.8,0.0));
    auto ground = make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, ground_material);
    world.add(ground);

    auto glass = make_shared<Glass>(1.5);

    auto outer = make_shared<Sphere>(point3(0.0, 0.0, -1.0),   0.5, glass);
    auto inner = make_shared<Sphere>(point3(0.0, 0.0, -1.0), -0.45, glass);
    
    world.add(outer); world.add(inner);

    // Create Camera
    double aspect_ratio = double(image_width) / double(image_height);
    //Camera camera(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 90, aspect_ratio); // Bird's eye
    Camera camera(point3(0,0,0), point3(0,0,-1), vec3(0,1,0), 90, aspect_ratio);    // Head on

    // Iterate through rows of pixels
    for(int j = 0; j < image_height; j++) {
        
        // Progress meter for large renders
        int progress = (j + 1)*100 / image_height;
        std::cerr << "\rProgress: " << progress << "%" << std::flush;

        // Iterate through each pixel in the row
        for (int i = 0; i < image_width; i++) {

            colour pixel_colour(0,0,0); // Clear colour
            
            // Random sampling for antialiasing
            for (int s=0; s < samples_per_pixel; s++) {
                double u = double(i + random_double()) / double(image_width-1);
                double v = double(j + random_double()) / double(image_height-1);
                Ray r = camera.get_ray(u, v);
                pixel_colour += ray_colour(r, world, max_depth);
            }

            // Divide by number of samples and gamma-correct for gamma=2.0
            double scale = 1.0 / double(samples_per_pixel);
            double r = sqrt(pixel_colour.r() * scale);
            double g = sqrt(pixel_colour.g() * scale);
            double b = sqrt(pixel_colour.b() * scale);

            data[image_height-1-j][i].R = static_cast<int>(255.999 * clamp(r, 0.0, 0.999));
            data[image_height-1-j][i].G = static_cast<int>(255.999 * clamp(g, 0.0, 0.999));
            data[image_height-1-j][i].B = static_cast<int>(255.999 * clamp(b, 0.0, 0.999));
        }
    }
    stbi_write_jpg("../renders/image.jpg", image_width, image_height, 3, data, 100);
    std::cerr << "\nFinished.\n";
}