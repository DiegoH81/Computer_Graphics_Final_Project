#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "color.h"

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

    Material(Color &in_color):
        ambient(Vector3(in_color.r * 0.2, in_color.g * 0.2, in_color.b * 0.2)),
        diffuse(Vector3(in_color.r, in_color.g, in_color.b)),
        specular(Vector3(1.0f, 1.0f, 1.0f)),
        shininess(16.0f),
        alpha_value(1.0f)
    { }
};

#endif