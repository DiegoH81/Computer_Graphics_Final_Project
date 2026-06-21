#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

class Material
{
public:
    Vector3 ambient, diffuse, specular;
    float shininess, alpha_value;

    Material() :
        ambient(Vector3(0.2f, 0.2f, 0.2f)),
        diffuse(Vector3(0.5f, 0.5f, 0.5f)),
        specular(Vector3(0.4f, 0.4f, 0.4f)),
        shininess(22.0f),
        alpha_value(1.0f)
    {}
};

#endif