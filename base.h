#ifndef BASE_H
#define BASE_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Base
{
public:
    Base(std::filesystem::path in_current_path):
        floor_material(), floor_down_material()
    {
        floor_material.ambient = Vector3(0.35f, 0.22f, 0.14f);
        floor_material.diffuse = Vector3(0.55f, 0.38f, 0.22f);
        floor_material.specular = Vector3(0.01f, 0.01f, 0.01f);
        floor_material.shininess = 1.0f;
        

        floor_down_material.ambient = Vector3(0.18f, 0.12f, 0.08f);
        floor_down_material.diffuse = Vector3(0.32f, 0.20f, 0.12f);
        floor_down_material.specular = Vector3(0.10f, 0.08f, 0.08f);
        floor_down_material.shininess = 8.0f;


        in_current_path = in_current_path / "models";
		
		
		Mesh3D* base_mesh;
        Mesh3D* base_mesh_down;
		
 
        base_mesh = new Mesh3D(in_current_path, "cylinder_base.obj");
        base_mesh_down = new Mesh3D(in_current_path, "cylinder_base_1.obj");


        base_mesh->add_faces();
        base_mesh->set_material(&floor_material);

        base_mesh_down->add_faces();
        base_mesh_down->set_material(&floor_down_material);
		

        root = new SceneNode(0);
        base = new SceneNode(1, base_mesh);
        base_down = new SceneNode(1, base_mesh_down);

        root->add_children(base);
        root->add_children(base_down);
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

    SceneNode *root, *base, *base_down;

    Material floor_material, floor_down_material;
};


#endif