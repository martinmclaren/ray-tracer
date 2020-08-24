//material.h

#pragma once

#include "colour.h"

/*
 * Defines the surface material of an object. Consists of the colour of the
 * material, and its reflective and lighting properties.
 */
class Material {
    public:
        Colour colour;
        float saturation, shine, reflectivity, specularity;

        //Constructors
        Material();
        Material(const Colour &col, const float sat, const float shi,
                 const float ref, const float spe);
};

Material::Material() {
    saturation = 1;
    shine = 0;
    reflectivity = 0;
    colour = Colour();
    specularity = 0;
}

Material::Material(const Colour &col, const float sat, const float shi,
         const float ref, const float spe) {
    colour = col;
    saturation = sat;
    shine = shi;
    reflectivity = ref;
    specularity = spe;
}

