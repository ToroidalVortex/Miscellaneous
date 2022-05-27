#ifndef SCENE_H
#define SCENE_H

#include "primitives.h"
#include "utils.h"

class Scene {
    public:
        Scene() {}
        
        std::vector<shared_ptr<Primitive>> objects;

        void add(const shared_ptr<Primitive> object) { objects.push_back(object); }
        void clear() { objects.clear(); }

        bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {
            hit_record temp_rec;
            bool hit_anything = false;
            double current_closest = t_max;

            for(const shared_ptr<Primitive> object : objects) {
                if(object -> hit(r,t_min,current_closest,temp_rec)) {
                    hit_anything = true;
                    current_closest = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_anything;
        }
};

#endif