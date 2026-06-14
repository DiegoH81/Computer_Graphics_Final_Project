#ifndef TABLE_H
#define TABLE_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Table
{
public:
    Table(std::filesystem::path in_current_path):
        marble(220, 215, 210, true), metal(160, 165, 170, true), material_marble(), material_metal()
    {
		material_marble.ambient = Vector3(0.18f, 0.17f, 0.16f);
        material_marble.diffuse = Vector3(0.80f, 0.78f, 0.75f);
        material_marble.specular = Vector3(0.60f, 0.60f, 0.58f);
        material_marble.shininess = 90.0f;

        material_metal.ambient = Vector3(0.12f, 0.12f, 0.13f);
        material_metal.diffuse = Vector3(0.50f, 0.52f, 0.55f);
        material_metal.specular = Vector3(0.80f, 0.80f, 0.82f);
        material_metal.shininess = 120.0f;


        in_current_path = in_current_path / "models";
		
		
		Mesh3D* top_mesh;
		Mesh3D* bottom_mesh;
		
 
        top_mesh = new Mesh3D(in_current_path, "table_top.obj");
        bottom_mesh = new Mesh3D(in_current_path, "table_bottom.obj");


        top_mesh->add_faces(&marble);
        top_mesh->set_material(&material_marble);

        bottom_mesh->add_faces(&metal);
        bottom_mesh->set_material(&material_metal);
		

        root = new SceneNode(0);
        top = new SceneNode(1, top_mesh);
		top->traslate(Vector3(0.0f, 0.1f, 0.0f), true);  

        bottom = new SceneNode(2, bottom_mesh);

        root->add_children(top);
        top->add_children(bottom);
    

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

    SceneNode *root, *top, *bottom;
	
    Color marble, metal;
    Material material_marble, material_metal;
};


#endif