//colour.h

#pragma once

#include "vector.h"

/*
 * Defines a Colour object, consisting of three floats representing the red,
 * green, blue components of the colour. Includes functions for adding and
 * scaling colours, and clamping component values to [0,255].
 */
class Colour {
    private:
        float r, g, b;

    public:
        //Constructors
        Colour();
        Colour (float red, float green, float blue);

        //Accessors
        float getR() const;
        float getG() const;
        float getB() const;

        //Mutators
        void setR(float red);
        void setG(float green);
        void setB(float blue);
        void set(float red, float green, float blue);

        //Assignment
        void operator =(const Colour &col);

        //Addition
        Colour operator +(const Colour &col);

        //Scale
        Colour operator *(float scalar);

        //Add with vector
        Colour operator +(const Vector &v);

        //Addition-assignment
        Colour& operator +=(const Colour& col);

        //Normalises the colour to ensure its components are in [0,255]
        void bound();
};

Colour::Colour() { r= 0.5;  g = 0.5; b = 0.5; }
Colour::Colour (float red, float green, float blue) {
    r = red; g = green; b = blue;
}

float Colour::getR() const { return r; }
float Colour::getG() const { return g; }
float Colour::getB() const { return b; }

void Colour::setR(float red) { r = red; }
void Colour::setG(float green) { g = green; }
void Colour::setB(float blue) { b = blue; }
void Colour::set(float red, float green, float blue) {
    r = red; g = green; b = blue;
}

void Colour::operator =(const Colour &col) {
    r=col.r; g=col.g; b=col.b;
}

Colour Colour::operator +(const Colour &col) {
    return Colour(r+col.getR(), g+col.getG(), b+col.getB());
}

Colour Colour::operator *(float scalar) {
    return Colour(r*scalar, g*scalar, b*scalar);
}

Colour Colour::operator +(const Vector &v) {
    return Colour(r+v.getX(), g+v.getY(), b+v.getZ());
}

Colour& Colour::operator +=(const Colour& col) {
    r += col.r;
    g += col.g;
    b += col.b;
    return *this;
}

void Colour::bound() {
    r = r*255; g = g*255; b=b*255;
    r = (r > 255) ? 255 : (r < 0) ? 0 : r;
    g = (g > 255) ? 255 : (g < 0) ? 0 : g;
    b = (b > 255) ? 255 : (b < 0) ? 0 : b;
}
