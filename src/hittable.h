#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct HitRecord {
    public:
        float t;
        Point3d p;
        Vector3d normal;
};

class HittableObject {
    public:
        // NOTE: Figure out what this syntax means
        virtual ~hittable() = default;

        virtual bool is_hit(
            const Ray& r,
            float t_min,
            float t_max,
            HitRecord& hit_record
        ) const = 0; // Also figure out why this is = 0
}

#endif
