#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <iostream>

class Vector3d {
    public:
        float e[3];

        Vector3d() : e{0, 0, 0} {}
        Vector3d(float e0, float e1, float e2) : e{e0, e1, e2} {}

        float x() const { return e[0]; }
        float y() const { return e[1]; }
        float z() const { return e[2]; }

        // TODO: find out why addreses don't need to be declared as const
        float operator[](int i) const { return e[i]; }
        float& operator[](int i) { return e[i]; }

        Vector3d operator-() const { 
            return Vector3d{-e[0], -e[1], -e[2]};
        };

        // TODO: look up the `this` keyword
        Vector3d& operator+=(const Vector3d &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];

            return *this;
        }

        Vector3d& operator*=(float t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        Vector3d operator/=(float t) {
            return *this *= 1 / t;
        }

        float length_squared() const {
            return e[0] * e[0]
                    + e[1] * e[1]
                    + e[2] * e[2];
        }

        float length() const {
            return sqrt(length_squared());
        }
};

using Point3d = Vector3d;

// TODO: look up how I/O streams work in C++
inline std::ostream& operator<<(std::ostream &out, const Vector3d &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3d operator+(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3d operator-(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3d operator*(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3d operator*(float t, const Vector3d &v) {
    return Vector3d(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// TODO: figure out why we don't use a pointer here
inline Vector3d operator/(Vector3d v, float t) {
    return (1 / t) * v;
}

inline float dot(const Vector3d &u, const Vector3d &v) {
    return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
}

inline Vector3d cross(const Vector3d &u, const Vector3d &v) {
    return Vector3d(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

inline Vector3d unit_vector(Vector3d v) {
    return v / v.length();
}

#endif
