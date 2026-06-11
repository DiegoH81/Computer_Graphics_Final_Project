#ifndef NENUFAR_H
#define NENUFAR_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Nenufar
{
public:
    Nenufar(std::filesystem::path in_current_path, bool type):
        pink(260, 140, 190, true), green(40, 120, 50, true), material_leaf(), material_flower()
    {
	
		material_leaf.ambient = Vector3(0.05f, 0.12f, 0.05f);
        material_leaf.diffuse = Vector3(0.10f, 0.45f, 0.15f);
        material_leaf.specular = Vector3(0.10f, 0.20f, 0.10f);
        material_leaf.shininess = 30.0f;

        material_flower.ambient = Vector3(0.40f, 0.35f, 0.40f);
        material_flower.diffuse = Vector3(0.90f, 0.40f, 0.60f);
        material_flower.specular = Vector3(0.30f, 0.10f, 0.20f);
        material_flower.shininess = 45.0f;
		

        in_current_path = in_current_path / "models" / "in_water" / "nenufars";
		
		
		Mesh3D* nenufar_mesh;
        Mesh3D* flower_mesh = nullptr;

        if(type) {
            nenufar_mesh = new Mesh3D(in_current_path, "nenufar_flor1.obj");
            flower_mesh  = new Mesh3D(in_current_path, "nenufar_flor2.obj");
        } 
		else {
			 nenufar_mesh = new Mesh3D(in_current_path, "nenufar.obj");
        }
		

   
        nenufar_mesh->add_faces(&green);
        nenufar_mesh->set_material(&material_leaf);

		root = new SceneNode(0);
        nenufar = new SceneNode(1, nenufar_mesh);
        root->add_children(nenufar);	
		
		
        if(type){
            flower_mesh->add_faces(&pink);
			flower_mesh->set_material(&material_flower);
			flower = new SceneNode(2, flower_mesh);
            nenufar->add_children(flower);
		}
    


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
    SceneNode *root, *nenufar, *flower;

    Color pink, green;
    Material material_leaf, material_flower;
};


#endif