#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point3d& origin, const Vector3d& direction)
            : orig(origin), dir(direction) {}
        
        Point3d origin() const { return orig; }
        Vector3d direction() const { return dir; }

        // Translate (?) the origin into some destination point
        Point3d at(float t) const {
            return orig + (t * dir);
        }

    private:
        Point3d orig;
        Vector3d dir;
};

#endif
