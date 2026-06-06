#ifndef LIGHT_PRESET_H
#define  LIGHT_PRESET_H

#include <vector>

#include "light.h"
#include "shader_list.h"
#include "color.h"

/*
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
*/

class LightPreset
{
public:
    DirectionalLight directional;
    std::vector<PointLight> point_lights;
    std::vector<SpotLight> spot_lights;
    Color background_color;

    LightPreset():
        directional(), point_lights(), spot_lights(), background_color(0.0f, 0.0f, 0.0f, false)
    {}

    std::vector<SceneNode*> get_point_lights_ptr()
    {
        std::vector<SceneNode*> to_return;
        for (auto &p: point_lights)
            to_return.push_back(p.light_node);

        return to_return;
    }

    void apply(ShaderList& shaders, Color& in_background_color)
    {
        in_background_color = background_color;

        shaders.set_int("UNIQUE", "num_point_lights", point_lights.size());
        shaders.set_int("UNIQUE", "num_spot_lights", spot_lights.size());

        directional.apply(shaders, 0);

        for (int i = 0; i < point_lights.size(); i++)
            point_lights[i].apply(shaders, i);

        for (int i = 0; i < spot_lights.size(); i++)
            spot_lights[i].apply(shaders, i);
    }
};

LightPreset get_day()
{
    LightPreset to_return;

    to_return.background_color = Color(0.53f, 0.81f, 0.92f, false);

    // Directional
    to_return.directional.ambient = Vector3(0.3f, 0.3f, 0.25f);
    to_return.directional.diffuse = Vector3(1.0f, 0.95f, 0.8f);
    to_return.directional.specular = Vector3(1.0f, 1.0f, 0.9f);
    to_return.directional.direction = Vector3(-0.5f, -1.0f, -0.5f);

    // Point
    PointLight fill;
    fill.ambient = Vector3(0.05f, 0.05f, 0.1f);
    fill.diffuse = Vector3(0.2f, 0.2f, 0.35f);
    fill.specular = Vector3(0.0f, 0.0f, 0.0f);
    fill.constant = 1.0f;
    fill.linear = 0.09f;
    fill.quadratic = 0.032f;
    to_return.point_lights.push_back(fill);

    return to_return;
}

LightPreset get_night()
{
    LightPreset to_return;

    to_return.background_color = Color(0.02f, 0.02f, 0.08f, false);

    // Directional
    to_return.directional.ambient = Vector3(0.05f, 0.05f, 0.1f);
    to_return.directional.diffuse = Vector3(0.1f, 0.1f, 0.2f);
    to_return.directional.specular = Vector3(0.2f, 0.2f, 0.3f);
    to_return.directional.direction = Vector3(-0.3f, -1.0f, -0.3f);

    // Point
    PointLight lantern;
    lantern.ambient = Vector3(0.1f, 0.05f, 0.0f);
    lantern.diffuse = Vector3(1.0f, 0.5f, 0.1f);
    lantern.specular = Vector3(0.8f, 0.4f, 0.1f);
    lantern.constant = 1.0f;
    lantern.linear = 0.22f;
    lantern.quadratic = 0.2f;
    to_return.point_lights.push_back(lantern);

    return to_return;
}

LightPreset get_cyberpunk()
{
    LightPreset to_return;

    to_return.background_color = Color(0.02f, 0.0f, 0.05f, false);

    // Directional
    to_return.directional.ambient   = Vector3(0.02f, 0.0f, 0.05f);
    to_return.directional.diffuse   = Vector3(0.05f, 0.0f, 0.08f);
    to_return.directional.specular  = Vector3(0.0f, 0.0f, 0.0f);
    to_return.directional.direction = Vector3(0.0f, -1.0f, 0.0f);

    // Neon magenta
    PointLight neon_magenta;
    neon_magenta.ambient   = Vector3(0.05f, 0.0f, 0.05f);
    neon_magenta.diffuse   = Vector3(0.9f, 0.0f, 0.6f);
    neon_magenta.specular  = Vector3(1.0f, 0.0f, 0.8f);
    neon_magenta.constant  = 1.0f;
    neon_magenta.linear = 0.22f;
    neon_magenta.quadratic = 0.2f;
    

    // Neón cyan — lado derecho
    PointLight neon_cyan;
    neon_cyan.ambient   = Vector3(0.0f, 0.05f, 0.05f);
    neon_cyan.diffuse   = Vector3(0.0f, 0.8f, 0.9f);
    neon_cyan.specular  = Vector3(0.0f, 1.0f, 1.0f);

    neon_cyan.constant  = 1.0f;
    neon_cyan.linear = 0.22f;
    neon_cyan.quadratic = 0.2f;

    // Luz de piso naranja/amarillo
    PointLight ground_reflect;
    ground_reflect.ambient   = Vector3(0.02f, 0.01f, 0.0f);
    ground_reflect.diffuse   = Vector3(0.4f, 0.25f, 0.0f);
    ground_reflect.specular  = Vector3(0.6f, 0.4f, 0.0f);

    ground_reflect.constant  = 1.0f;
    ground_reflect.linear = 0.35f;
    ground_reflect.quadratic = 0.44f;

    to_return.point_lights.push_back(neon_magenta);
    to_return.point_lights.push_back(neon_cyan);
    to_return.point_lights.push_back(ground_reflect);

    return to_return;
}

LightPreset get_desert()
{
    LightPreset to_return;
    to_return.background_color = Color(191, 133, 76, true);

    // Directional
	to_return.directional.ambient = Vector3(0.3f, 0.3f, 0.3f);
    to_return.directional.diffuse = Vector3(1.0f, 0.9f, 0.9f);
    to_return.directional.specular = Vector3(1.0f, 1.0f, 1.0f);
	to_return.directional.direction = Vector3(1.0f, -1.0f, -1.0f);
	
    // Sun
    PointLight world_sun;
    world_sun.ambient = Vector3(0.3f, 0.3f, 0.3f);
    world_sun.diffuse = Vector3(1.0f, 0.9f, 0.9f);
    world_sun.specular = Vector3(1.0f, 1.0f, 1.0f);
	world_sun.light_node->traslate(Vector3(0.0f, 0.0f, 2.0f), true);

    to_return.point_lights.push_back(world_sun);

    return to_return;
}

#endif