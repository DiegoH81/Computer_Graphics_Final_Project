#ifndef TERRAIN_H
#define TERRAIN_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Terrain
{
public:
    Terrain(std::filesystem::path in_current_path):
        green_earth(85, 95, 60, true), blue_water(140, 185, 220, true), material_terrain(), material_water()
    {
		material_terrain.ambient = Vector3(0.08f, 0.10f, 0.05f);
        material_terrain.diffuse = Vector3(0.30f, 0.38f, 0.18f);
        material_terrain.specular = Vector3(0.03f, 0.04f, 0.02f);
        material_terrain.shininess = 5.0f;


		material_water.ambient = Vector3(0.10f, 0.18f, 0.25f);
		material_water.diffuse = Vector3(0.35f, 0.58f, 0.75f);
		material_water.specular = Vector3(0.60f, 0.70f, 0.80f);
		material_water.shininess = 180.0f;


        in_current_path = in_current_path / "models";
		
		
		Mesh3D* terrain_mesh;
		Mesh3D* water_mesh;
		
 
        terrain_mesh = new Mesh3D(in_current_path, "terreno.obj");
        water_mesh = new Mesh3D(in_current_path, "lago.obj");

			
    
        terrain_mesh->add_faces(&green_earth);
        terrain_mesh->set_material(&material_terrain);

        water_mesh->add_faces(&blue_water);
        water_mesh->set_material(&material_water);

        root = new SceneNode(0);
        terrain = new SceneNode(1, terrain_mesh);
        water = new SceneNode(2, water_mesh);

        root->add_children(terrain);
        root->add_children(water);

    }

    void draw(ShaderList& in_shaders, TextureList& in_texturs, const Matrix_4& in_mat)
    {
        root->draw(in_shaders, in_texturs, in_mat);
    }

    SceneNode* get_root()
    {
        return root;
    }

private:
    SceneNode *root, *terrain, *water;

    Color green_earth, blue_water;
    Material material_terrain, material_water;
};


#endif