//ray.h

#pragma once

#include "vector.h"

/*
 * Defines a ray object, which are composed of two vectors.
 */
class Ray {
    private:
        Vector origin, direction;

    public:
        //Constructors
        Ray();
        Ray(Vector &orig, Vector &dir);
        //Accessors
        Vector getOrigin() const;
        Vector getDirection() const;
};

Ray::Ray() { origin = Vector(0,0,0); direction = Vector(1,1,1); }
Ray::Ray(Vector &orig, Vector &dir) { origin = orig; direction = dir; }

Vector Ray::getOrigin() const { Vector v = origin; return v; }
Vector Ray::getDirection() const { Vector v = direction; return v; };
