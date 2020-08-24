//light.h

#pragma once

#include "vector.h"

/*
 * Defines a Light object, consisting of the position of the light, and its
 * brightness.
 */
class Light {
    public:
        float brightness;
        Vector position;

        //Constructor
        Light(const Vector &pos, const float bright);
};

Light::Light(const Vector &pos, const float bright) {
    position = pos; brightness = bright;
}
