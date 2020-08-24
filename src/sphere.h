//sphere.h

#pragma once

#include "ray.h"
#include "vector.h"
#include "material.h"

/*
 * Defines a Sphere object, consisting of a radius, a vector representing its
 * center, and the surface material. Includes function for calculating
 * ray-sphere intersection.
 */
class Sphere {
    private:
    float radius;
    Vector center;
    Material material;

    public:
    //Constructor
    Sphere(const float rad, const Vector &cent, const Material &mat);

    //Accessors
    float getRadius() const;
    Vector getCenter() const;
    Material getMaterial() const;

    //Calculate ray-sphere intersection
    bool sphereIntersection(const Ray &ray, float &t) const;
};

Sphere::Sphere(const float rad, const Vector &cent, const Material &mat) {
    center = cent; radius = rad; material = mat;
}

float Sphere::getRadius() const { return radius; }
Vector Sphere::getCenter() const { Vector v = center; return v; }
Material Sphere::getMaterial() const { return material; }

bool Sphere::sphereIntersection(const Ray &ray, float &t) const {
    Vector L = ray.getOrigin() - center;

    //Calculate components
    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2.0 * ray.getDirection().dot(L);
    float c = L.dot(L) - radius*radius;

    //Get value for discriminant
    float disc = b*b - 4*a*c;

    //Discriminant < 0, no roots and no intersection
    if (disc < 0.0) return false;

    //Discriminant = 0, one root (ray intersects at one point)
    if (disc == 0.0) {
        t = (-b/(2*a));
        return true;
    }

    //calculate both roots, return smaller value
    float t1 = (-b + std::sqrt(disc))/2*a;
    float t2 = (-b - std::sqrt(disc))/2*a;
    t = (t1 < t2) ? t1 : t2;

    if (t < 0.0) return false;

    return true;
}
