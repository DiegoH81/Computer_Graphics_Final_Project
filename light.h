#ifndef LIGHT_H
#define  LIGHT_H

#include "shape.h"
#include "scene.h"
#include "vector.h"
#include "shader_list.h"
/*
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
*/

#define LIGHT_SHADER_NAME "LIGHT_SHADER"
#define SHADER_NAME "UNIQUE"

class Light
{
public:
    SceneNode* light_node;
    Vector3 ambient, diffuse, specular;

    Light():
        ambient(), diffuse(), specular()
    {
        Cube* light_cube = new Cube(0.1f);
        light_cube->add_faces();

        light_cube->set_shader_name(LIGHT_SHADER_NAME);

        light_node = new SceneNode(-1, light_cube);
    }
	
	virtual void apply(ShaderList& shaders, int index) = 0;
};

class DirectionalLight : public Light
{
public:
    Vector3 direction;

    DirectionalLight() : Light(), direction() {}

    void apply(ShaderList& shaders, int index) override
    {
        shaders.set_vec3(SHADER_NAME, "directional_light.ambient", ambient.x, ambient.y, ambient.z);
        shaders.set_vec3(SHADER_NAME, "directional_light.diffuse", diffuse.x, diffuse.y, diffuse.z);
        shaders.set_vec3(SHADER_NAME, "directional_light.specular", specular.x, specular.y, specular.z);
        shaders.set_vec3(SHADER_NAME, "directional_light.direction", direction.x, direction.y, direction.z);
    }
};

class PointLight : public Light
{
public:
    float constant, linear, quadratic;

    PointLight() : Light(), constant(1.0f), linear(0.09f), quadratic(0.032f) {}

    void apply(ShaderList& shaders, int index) override
    {
        std::string b = "point_lights[" + std::to_string(index) + "].";
		
		auto light_position = light_node->get_center();
		
        shaders.set_vec3(SHADER_NAME, b + "position", light_position.x, light_position.y, light_position.z);
        shaders.set_vec3(SHADER_NAME, b + "ambient", ambient.x, ambient.y, ambient.z);
        shaders.set_vec3(SHADER_NAME, b + "diffuse", diffuse.x, diffuse.y, diffuse.z);
        shaders.set_vec3(SHADER_NAME, b + "specular", specular.x, specular.y, specular.z);
        shaders.set_float(SHADER_NAME, b + "constant", constant);
        shaders.set_float(SHADER_NAME, b + "linear", linear);
        shaders.set_float(SHADER_NAME, b + "quadratic", quadratic);
    }
};

class SpotLight : public Light
{
public:
    Vector3 direction;
    float cut_off, outer_cut_off;

    SpotLight() : Light(), direction(), cut_off(0.0f), outer_cut_off(0.0f) {}

    void apply(ShaderList& shaders, int index) override
    {
        std::string b = "spot_lights[" + std::to_string(index) + "].";
		
		auto light_position = light_node->get_center();
        shaders.set_vec3(SHADER_NAME, b + "position", light_position.x, light_position.y, light_position.z);
        shaders.set_vec3(SHADER_NAME, b + "direction", direction.x, direction.y, direction.z);
        shaders.set_vec3(SHADER_NAME, b + "ambient", ambient.x, ambient.y, ambient.z);
        shaders.set_vec3(SHADER_NAME, b + "diffuse", diffuse.x, diffuse.y, diffuse.z);
        shaders.set_vec3(SHADER_NAME, b + "specular", specular.x, specular.y, specular.z);
        shaders.set_float(SHADER_NAME, b + "cut_off", cut_off);
        shaders.set_float(SHADER_NAME, b + "outer_cut_off", outer_cut_off);
    }
};


#endif