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
    Color background_color, color_A, color_B;

    float max_height_preset;
    bool has_animation;
    
    Vector3 dir_ambient_A, dir_diffuse_A;
    Vector3 dir_ambient_B, dir_diffuse_B;

    LightPreset():
        directional(), point_lights(), spot_lights(), background_color(0.0f, 0.0f, 0.0f, false),
        color_A(0.0f, 0.0f, 0.0f, false),
        color_B(0.0f, 0.0f, 0.0f, false),
        max_height_preset(0.0f),
        dir_ambient_A(), dir_ambient_B(), dir_diffuse_A(), dir_diffuse_B(),
        has_animation(false)
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

        shaders.set_int("GLASS_SHADER", "num_point_lights", point_lights.size());
        shaders.set_int("GLASS_SHADER", "num_spot_lights", spot_lights.size());

        directional.apply(shaders, 0);

        for (int i = 0; i < point_lights.size(); i++)
            point_lights[i].apply(shaders, i);

        for (int i = 0; i < spot_lights.size(); i++)
            spot_lights[i].apply(shaders, i);
    }

    void update_cycle()
    {
        if (point_lights.empty() || point_lights[0].light_node == nullptr) 
            return;

        Vector3 sun_pos = point_lights[0].light_node->get_center();

        float normalized_height = sun_pos.y / max_height_preset; // [-1, 1]

        float t = (1.0f - normalized_height) / 2.0f; // [0, 1]

        t = std::max(0.0f, std::min(1.0f, t)); 


        this->background_color = Color( color_A.r + t * (color_B.r - color_A.r),
                                        color_A.g + t * (color_B.g - color_A.g),
                                        color_A.b + t * (color_B.b - color_A.b),
                                        false );

        this->directional.ambient = Vector3( dir_ambient_A.x + t * (dir_ambient_B.x - dir_ambient_A.x),
                                             dir_ambient_A.y + t * (dir_ambient_B.y - dir_ambient_A.y),
                                             dir_ambient_A.z + t * (dir_ambient_B.z - dir_ambient_A.z) );

        
        this->directional.diffuse = Vector3( dir_diffuse_A.x + t * (dir_diffuse_B.x - dir_diffuse_A.x),
                                             dir_diffuse_A.y + t * (dir_diffuse_B.y - dir_diffuse_A.y),
                                             dir_diffuse_A.z + t * (dir_diffuse_B.z - dir_diffuse_A.z) );

    }
};

LightPreset get_day()
{
    LightPreset to_return;

    
    to_return.background_color = Color(0.45f, 0.72f, 0.90f, false);
    to_return.directional.direction = Vector3(-1.2f, -0.8f, -0.6f);
    to_return.directional.ambient = Vector3(0.25f, 0.28f, 0.32f);
    to_return.directional.diffuse = Vector3(1.8f, 1.75f, 1.55f);
    to_return.directional.specular = Vector3(2.0f, 2.0f, 2.0f);

    PointLight floor_bounce;
    //floor_bounce.draw_sphere();
    floor_bounce.ambient = Vector3(0.15f, 0.1f, 0.05f);
    floor_bounce.diffuse = Vector3(0.6f, 0.45f, 0.3f);
    floor_bounce.specular = Vector3(0.1f, 0.1f, 0.1f);
    floor_bounce.constant = 1.0f;
    floor_bounce.linear = 0.01f;
    floor_bounce.quadratic = 0.001f;
    
    floor_bounce.light_node->traslate(Vector3(-10.0f, -5.0f, 15.0f), true);
    
    to_return.point_lights.push_back(floor_bounce);

    return to_return;
}

LightPreset get_night()
{
    LightPreset to_return;

    to_return.background_color = Color(0.01f, 0.01f, 0.04f, false);
    to_return.directional.ambient = Vector3(0.02f, 0.02f, 0.06f); 
    to_return.directional.diffuse = Vector3(0.05f, 0.05f, 0.15f);
    to_return.directional.specular = Vector3(0.1f, 0.1f, 0.3f);
    to_return.directional.direction = Vector3(-0.3f, -1.0f, -0.3f);

    PointLight lantern;
    lantern.ambient = Vector3(0.1f, 0.05f, 0.0f);
    lantern.diffuse = Vector3(2.8f, 1.4f, 0.3f);
    lantern.specular = Vector3(1.8f, 1.0f, 0.2f);
    
    lantern.constant = 1.0f;
    lantern.linear = 0.022f;
    lantern.quadratic = 0.0015f;
    //lantern.draw_sphere();
    lantern.light_node->traslate(Vector3(0.0f, 12.0f, 0.0f), true);
    
    to_return.point_lights.push_back(lantern);

    return to_return;
}

LightPreset get_cyberpunk()
{
    LightPreset to_return;

    to_return.background_color = Color(0.02f, 0.0f, 0.05f, false);

    // Directional
    to_return.directional.ambient   = Vector3(0.08f, 0.0f, 0.12f);
    to_return.directional.diffuse   = Vector3(0.15f, 0.0f, 0.25f);
    to_return.directional.specular  = Vector3(0.1f, 0.0f, 0.2f);
    to_return.directional.direction = Vector3(0.0f, -1.0f, 0.0f);

    // Neon magenta
    PointLight neon_magenta;
    neon_magenta.ambient = Vector3(0.08f, 0.0f, 0.08f);
    neon_magenta.diffuse = Vector3(1.2f, 0.0f, 0.8f);
    neon_magenta.specular = Vector3(1.5f, 0.0f, 1.0f);
    neon_magenta.constant = 1.0f;
    neon_magenta.linear = 0.014f;
    neon_magenta.quadratic = 0.0007f;
    neon_magenta.light_node->traslate(Vector3(-8.0f, 19.0f, 0.0f), true);
    //neon_magenta.draw_sphere();

    // Neon cyan
    PointLight neon_cyan;
    neon_cyan.ambient = Vector3(0.0f, 0.05f, 0.08f);
    neon_cyan.diffuse = Vector3(0.0f, 0.9f, 1.2f);
    neon_cyan.specular = Vector3(0.0f, 1.0f, 1.5f);
    neon_cyan.constant = 1.0f;
    neon_cyan.linear = 0.014f;
    neon_cyan.quadratic = 0.0007f;
    neon_cyan.light_node->traslate(Vector3(8.0f, 19.0f, 13.0f), true);
    //neon_cyan.draw_sphere();

    // Neon violeta
    PointLight neon_purple;
    neon_purple.ambient = Vector3(0.05f, 0.0f, 0.1f);
    neon_purple.diffuse = Vector3(0.6f, 0.0f, 1.2f);
    neon_purple.specular = Vector3(0.8f, 0.0f, 1.5f);
    neon_purple.constant = 1.0f;
    neon_purple.linear = 0.009f;
    neon_purple.quadratic = 0.002f;
    neon_purple.light_node->traslate(Vector3(0.0f, 19.0f, 8.0f), true);
    //neon_purple.draw_sphere();

    // Naranja/ambar
    PointLight ground_orange;
    ground_orange.ambient = Vector3(0.05f, 0.02f, 0.0f);
    ground_orange.diffuse = Vector3(0.8f, 0.4f, 0.0f);
    ground_orange.specular = Vector3(1.0f, 0.6f, 0.0f);
    ground_orange.constant = 1.0f;
    ground_orange.linear = 0.009f;
    ground_orange.quadratic = 0.0032f;
    ground_orange.light_node->traslate(Vector3(5.0f, 19.0f, 0.0f), true);
    //ground_orange.draw_sphere();

    to_return.point_lights.push_back(neon_magenta);
    to_return.point_lights.push_back(neon_cyan);
    to_return.point_lights.push_back(neon_purple);
    to_return.point_lights.push_back(ground_orange);

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
    world_sun.draw_sphere();
    world_sun.ambient = Vector3(0.3f, 0.3f, 0.3f);
    world_sun.diffuse = Vector3(1.0f, 0.9f, 0.9f);
    world_sun.specular = Vector3(1.0f, 1.0f, 1.0f);
	world_sun.light_node->traslate(Vector3(0.0f, 35.0f, 35.0f), true);

    to_return.point_lights.push_back(world_sun);

    return to_return;
}

LightPreset get_day_cicle()
{
    float max_height = 22.0f;

    LightPreset to_return;
    
    to_return.max_height_preset = max_height;
    to_return.has_animation = true;

    
    to_return.background_color = Color(185, 125, 80, true); 
    to_return.color_A = Color(195, 130, 75, true);
    to_return.color_B = Color(0.005f, 0.008f, 0.02f, false);

    
    to_return.dir_ambient_A = Vector3(0.28f, 0.22f, 0.18f);
    to_return.dir_diffuse_A = Vector3(1.9f, 1.65f, 1.1f);

    to_return.dir_ambient_B = Vector3(0.01f, 0.01f, 0.03f);
    to_return.dir_diffuse_B = Vector3(0.1f, 0.15f, 0.35f);  

    to_return.directional.ambient = to_return.dir_ambient_A;
    to_return.directional.diffuse = to_return.dir_diffuse_A;
    
    to_return.directional.specular = Vector3(1.5f, 1.1f, 0.5f); 
    to_return.directional.direction = Vector3(1.0f, -0.6f, -0.8f);
    
    PointLight world_sun;
    world_sun.draw_sphere();
    world_sun.ambient  = Vector3(0.10f, 0.08f, 0.06f); 
    world_sun.diffuse  = Vector3(1.6f, 1.40f, 1.0f);
    world_sun.specular = Vector3(0.15f, 0.12f, 0.08f); 
    
    world_sun.constant = 1.0f;
    world_sun.linear = 0.005f;                       
    world_sun.quadratic = 0.0002f;                   
    world_sun.draw_sphere();
    world_sun.light_node->traslate(Vector3(max_height, max_height, 0.0f), true);

    to_return.point_lights.push_back(world_sun);

    return to_return;
}

LightPreset get_bioluminiscente()
{
    LightPreset to_return;

    to_return.background_color = Color(0.0f, 0.02f, 0.02f, false);

    to_return.directional.ambient = Vector3(0.0f, 0.05f, 0.04f);
    to_return.directional.diffuse = Vector3(0.0f, 0.08f, 0.06f);
    to_return.directional.specular = Vector3(0.0f, 0.1f, 0.08f);
    to_return.directional.direction = Vector3(0.0f, -1.0f, 0.0f);

    PointLight bio_main;
    bio_main.ambient = Vector3(0.0f, 0.08f, 0.06f);
    bio_main.diffuse = Vector3(0.0f, 1.5f, 1.0f);
    bio_main.specular = Vector3(0.0f, 1.8f, 1.2f);
    bio_main.constant = 1.0f;
    bio_main.linear = 0.014f;
    bio_main.quadratic = 0.0007f;
    //bio_main.draw_sphere();
    bio_main.light_node->traslate(Vector3(0.0f, 17.0f, 0.0f), true);

    PointLight bio_blue;
    bio_blue.ambient = Vector3(0.02f, 0.0f, 0.08f);
    bio_blue.diffuse = Vector3(0.5f, 0.0f, 1.8f);
    bio_blue.specular = Vector3(0.6f, 0.0f, 2.0f);
    bio_blue.constant = 1.0f;
    bio_blue.linear = 0.025f;
    bio_blue.quadratic = 0.001f;
    //bio_blue.draw_sphere();
    bio_blue.light_node->traslate(Vector3(-8.0f, 17.0f, 5.0f), true);

    PointLight bio_ground;
    bio_ground.ambient = Vector3(0.0f, 0.05f, 0.05f);
    bio_ground.diffuse = Vector3(0.0f, 1.2f, 1.3f);  // Más fuerza
    bio_ground.specular = Vector3(0.0f, 1.4f, 1.5f);
    bio_ground.constant = 1.0f;
    bio_ground.linear = 0.035f;
    bio_ground.quadratic = 0.002f;
    //bio_ground.draw_sphere();
    bio_ground.light_node->traslate(Vector3(7.0f, 15.0f, 3.0f), true);

    to_return.point_lights.push_back(bio_main);
    to_return.point_lights.push_back(bio_blue);
    to_return.point_lights.push_back(bio_ground);

    return to_return;
}

LightPreset get_deep_sea()
{
    LightPreset to_return;

    to_return.background_color = Color(0.0f, 0.005f, 0.015f, false);

    to_return.directional.ambient = Vector3(0.0f, 0.02f, 0.04f);
    to_return.directional.diffuse = Vector3(0.0f, 0.03f, 0.06f);
    to_return.directional.specular = Vector3(0.0f, 0.05f, 0.1f);
    to_return.directional.direction = Vector3(0.0f, -1.0f, 0.0f);

    PointLight surface_light;
    surface_light.ambient = Vector3(0.0f, 0.02f, 0.06f);
    surface_light.diffuse = Vector3(0.0f, 0.3f, 1.5f);
    surface_light.specular = Vector3(0.0f, 0.4f, 1.2f);
    surface_light.constant = 1.0f;
    surface_light.linear = 0.022f;
    surface_light.quadratic = 0.0015f;
    //surface_light.draw_sphere();
    surface_light.light_node->traslate(Vector3(0.0f, 18.0f, 0.0f), true);

    PointLight algae_glow;
    algae_glow.ambient = Vector3(0.0f, 0.03f, 0.01f);
    algae_glow.diffuse = Vector3(0.0f, 0.8f, 0.3f);
    algae_glow.specular = Vector3(0.0f, 0.6f, 0.2f);
    algae_glow.constant = 1.0f;
    algae_glow.linear = 0.045f;
    algae_glow.quadratic = 0.005f;
    //algae_glow.draw_sphere();
    algae_glow.light_node->traslate(Vector3(-4.0f, 14.0f, 3.0f), true);

    PointLight cold_fill;
    cold_fill.ambient = Vector3(0.01f, 0.01f, 0.03f);
    cold_fill.diffuse = Vector3(0.1f, 0.1f, 0.4f);
    cold_fill.specular = Vector3(0.1f, 0.1f, 0.5f);
    cold_fill.constant = 1.0f;
    cold_fill.linear = 0.014f;
    cold_fill.quadratic = 0.0007f;
    //cold_fill.draw_sphere();
    cold_fill.light_node->traslate(Vector3(10.0f, 13.0f, -6.0f), true);

    to_return.point_lights.push_back(surface_light);
    to_return.point_lights.push_back(algae_glow);
    to_return.point_lights.push_back(cold_fill);

    return to_return;
}

LightPreset get_candlelight()
{
    LightPreset to_return;

    to_return.background_color = Color(0.005f, 0.002f, 0.0f, false);
    to_return.directional.ambient = Vector3(0.03f, 0.015f, 0.0f);
    to_return.directional.diffuse = Vector3(0.05f, 0.025f, 0.0f);
    to_return.directional.specular = Vector3(0.0f, 0.0f, 0.0f);
    to_return.directional.direction = Vector3(0.0f, -1.0f, 0.0f);

    PointLight candle_main;
    candle_main.ambient = Vector3(0.08f, 0.03f, 0.0f);
    candle_main.diffuse = Vector3(2.5f, 1.0f, 0.1f);
    candle_main.specular = Vector3(1.8f, 0.8f, 0.1f);
    candle_main.constant = 1.0f;
    candle_main.linear = 0.022f;
    candle_main.quadratic = 0.0015f;
    //candle_main.draw_sphere();
    candle_main.light_node->traslate(Vector3(2.0f, 14.5f, 1.0f), true);

    PointLight warm_bounce;
    warm_bounce.ambient = Vector3(0.04f, 0.01f, 0.0f);
    warm_bounce.diffuse = Vector3(1.2f, 0.4f, 0.05f);
    warm_bounce.specular = Vector3(0.5f, 0.2f, 0.0f);
    warm_bounce.constant = 1.0f;
    warm_bounce.linear = 0.035f;
    warm_bounce.quadratic = 0.002f;
    //warm_bounce.draw_sphere();
    warm_bounce.light_node->traslate(Vector3(-4.0f, 11.0f, 3.0f), true);

    to_return.point_lights.push_back(candle_main);
    to_return.point_lights.push_back(warm_bounce);

    return to_return;
}

#endif