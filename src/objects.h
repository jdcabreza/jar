#ifndef OBJECTS_H
#define OBJECTS_H

#include "hittable.h"
#include "vector3d.h"

class Sphere : public HittableObject {
    public:
        Sphere(Point3d _center, float _radius) 
            : center(_center), radius(_radius)
        
        bool is_hit(
            const Ray& r,
            float t_min,
            float t_max,
            HitRecord& hit_record
        ) const override {
            Vector3d OC = r.origin() - center;
            
            // Solve for roots to indicate a hit
            auto a = r.direction().length_squared();
            auto half_b = dot(OC, r.direction());
            auto c = OC.length_squared() - (radius * radius);
            auto discriminant = (half_b * half_b) - (a * c);

            if (discriminant < 0) {
                return false;
            }
            
            auto discriminant_sqrt = sqrt(discriminant);
            auto root = (-half_b - discriminant_sqrt) / a;

            // Check if the first root is a valid intersection
            if (root <= t_min || root >= t_max) {
                // Check if the second root is valid
                root = (-half_b + discriminant_sqrt) / a;

                if (root <= t_min || root >= t_max) {
                    return false;
                }
            }

            hit_record.t = root;
            hit_record.p = r.at(hit_record.t);

            // Surface normals are unit length by default
            hit_record.normal = (hit_record.p - center) / radius;

            return true;
        }
    
    private:
        Point3d center;
        float radius;
};

#endif
