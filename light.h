#ifndef LIGHT_H
#define  LIGHT_H

#include "shape.h"
#include "scene.h"

/*
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
*/

class Light
{
public:
    SceneNode* light_node;

    Light()
    {
        Cube* light_cube = new Cube(0.1f);
        light_cube->add_faces();

        light_cube->set_shader_name("LIGHT_SHADER");

        light_node = new SceneNode(-1, light_cube);
    }

};

#endif