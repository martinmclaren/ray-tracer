//vector.h

#pragma once

#include <cmath>
#include <iostream>

/*
 * Defines a 3D Vector object and its associated attributes and behaviours.
 * Includes functions for simple vector operations, including dot and
 * cross-products.
 */
class Vector {
    private:
        float x, y, z;

    public:
        //Constructors
        Vector(){}
        Vector(float vx, float vy, float vz) { x = vx; y = vy; z = vz; }
        Vector(const Vector &v) { x = v.x; y = v.y; z = v.z; }

        //Accessors
        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }

        //Mutators
        void setX(float nx) { x = nx; }
        void setY(float ny) { y = ny; }
        void setZ(float nz) { z = nz; }

        //Assignment
        void operator =(const Vector &v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }

        //Equality checking
        bool operator ==(const Vector &v) const {
            return (x==v.x && y==v.y && z==v.z);
        }

        //Set to zero vector
        void zero() {
            x = y = z = 0;
        }

        //Negation
        Vector operator -() const {
            return Vector(-x, -y, -z);
        }

        //Addition
        Vector operator +(const Vector &v) const {
            return Vector(x+v.x, y+v.y, z+v.z);
        }

        //Subtraction
        Vector operator -(const Vector &v) const {
            return Vector(x-v.x, y-v.y, z-v.z);
        }

        //Scalar multiplication
        Vector operator *(float scalar) const {
            return Vector(x*scalar, y*scalar, z*scalar);
        }

        //Scalar division
        Vector operator /(float scalar) const {
            return Vector(x/scalar, y/scalar, z/scalar);
        }

        //Magnitude
        float magnitude() {
            return sqrt(x*x + y*y + z*z);
        }

        //Normalise
        Vector normalize() {
            Vector v(x, y, z);
            float mag = v.magnitude();
            return v/mag;
        }

        //Dot product
        float dot(const Vector &v) const {
            return (x*v.x + y*v.y + z*v.z);
        }

        //Cross product
        Vector cross(const Vector &v) {
            return Vector(y*v.z - z*v.y,
                          z*v.x - x*v.z,
                          x*v.y - y*v.x);
        }

        //Reflection of two vectors
        static Vector reflect(const Vector &incidence, const Vector &normal) {
            return (incidence - normal*(2.0*(normal.dot(incidence)))).normalize();
        }

        //Output to screen
        friend std::ostream& operator<< (std::ostream &os, const Vector &v) {
            os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
            return os;
        }
};

