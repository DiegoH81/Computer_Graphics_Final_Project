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
        green_earth(85, 95, 60, true), brown_earth(120, 88, 52, true), blue_water(140, 185, 220, true), 
		material_terrain(), material_water()
    {
		material_terrain.ambient = Vector3(0.08f, 0.10f, 0.05f);
        material_terrain.diffuse = Vector3(0.30f, 0.38f, 0.18f);
        material_terrain.specular = Vector3(0.03f, 0.04f, 0.02f);
        material_terrain.shininess = 5.0f;
		
		material_dirt.ambient = Vector3(0.10f, 0.07f, 0.04f);
		material_dirt.diffuse = Vector3(0.42f, 0.28f, 0.15f);
		material_dirt.specular = Vector3(0.02f, 0.02f, 0.01f);
		material_dirt.shininess = 5.0f;

		material_water.ambient = Vector3(0.10f, 0.18f, 0.25f);
		material_water.diffuse = Vector3(0.35f, 0.58f, 0.75f);
		material_water.specular = Vector3(0.60f, 0.70f, 0.80f);
		material_water.shininess = 180.0f;
        material_water.alpha_value = 0.3f;


        in_current_path = in_current_path / "models";
		
		
		Mesh3D* terrain_mesh;
		Mesh3D* terrain_bottom_mesh;
		
		Mesh3D* water_mesh;
		
 
        terrain_mesh = new Mesh3D(in_current_path, "terreno.obj");
        terrain_bottom_mesh = new Mesh3D(in_current_path, "terreno_bottom.obj");
		
        water_mesh = new Mesh3D(in_current_path, "lago.obj");

			
    
        terrain_mesh->add_faces(&green_earth);
        terrain_mesh->set_material(&material_terrain);
		
		terrain_bottom_mesh->add_faces(&brown_earth);
        terrain_bottom_mesh->set_material(&material_dirt);

        water_mesh->add_faces(&blue_water);
        water_mesh->set_material(&material_water);

        root = new SceneNode(0);
        terrain = new SceneNode(1, terrain_mesh);
        dirt = new SceneNode(2, terrain_bottom_mesh);
		
        water = new SceneNode(3, water_mesh);

        root->add_children(terrain);
        terrain->add_children(dirt);
        //root->add_children(water);

    }

    void draw(ShaderList& in_shaders, TextureList& in_texturs, const Matrix_4& in_mat)
    {
        root->draw(in_shaders, in_texturs, in_mat);
    }

    SceneNode* get_root()
    {
        return root;
    }

    SceneNode* get_water()
    {
        return water;
    }

private:
    SceneNode *root, *terrain, *dirt, *water;

    Color green_earth, brown_earth, blue_water;
    Material material_terrain, material_dirt, material_water;
};


#endif