#ifndef NENUFAR_H
#define NENUFAR_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Nenufar
{
public:
    Nenufar(std::filesystem::path in_current_path, bool type, bool mode):
        pink(260, 140, 190, true), purple(180, 80, 200, true), 
		green(40, 120, 50, true), material_leaf(), material_flower1(), material_flower2()
    {
	
		material_leaf.ambient = Vector3(0.05f, 0.12f, 0.05f);
        material_leaf.diffuse = Vector3(0.10f, 0.45f, 0.15f);
        material_leaf.specular = Vector3(0.10f, 0.20f, 0.10f);
        material_leaf.shininess = 30.0f;
      
        material_flower1.ambient = Vector3(0.40f, 0.35f, 0.40f);
        material_flower1.diffuse = Vector3(0.90f, 0.40f, 0.60f);
        material_flower1.specular = Vector3(0.30f, 0.10f, 0.20f);
        material_flower1.shininess = 45.0f;

        material_flower2.ambient = Vector3(0.30f, 0.20f, 0.40f);
        material_flower2.diffuse = Vector3(0.60f, 0.20f, 0.80f);
        material_flower2.specular = Vector3(0.20f, 0.10f, 0.30f);
        material_flower2.shininess = 45.0f;

		

        std::filesystem::path base = in_current_path / "models" / "in_water" / "nenufars";
		
		
		Mesh3D* nenufar_mesh;
		Mesh3D* flower1_mesh;
		Mesh3D* flower2_mesh = nullptr;

		if (mode)
		{
			nenufar_mesh = new Mesh3D(base / "UNIDO", "nenufares.obj");
			flower1_mesh = new Mesh3D(base / "UNIDO", "n_flor1.obj");
			flower2_mesh = new Mesh3D(base / "UNIDO", "n_flor2.obj");
		}
		else
		{
			if (type){
				nenufar_mesh = new Mesh3D(base / "SEPARADO", "nenufar_flor1.obj");
				flower1_mesh = new Mesh3D(base / "SEPARADO", "nenufar_flor2.obj");
			}
			else
				nenufar_mesh = new Mesh3D(base / "SEPARADO", "nenufar.obj");
		}
      
	   
        nenufar_mesh->add_faces(&material_leaf);
		
		root = new SceneNode(0);
        nenufar = new SceneNode(1, nenufar_mesh);
        root->add_children(nenufar);	
		
		
		if (flower1_mesh) 
		{
            flower1_mesh->add_faces(&material_flower1);
			flower = new SceneNode(2, flower1_mesh);
			nenufar->add_children(flower);

        }
        if (flower2_mesh) 
		{
            flower2_mesh->add_faces(&material_flower2);
			flower2 = new SceneNode(3, flower2_mesh);
			nenufar->add_children(flower2);
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
    SceneNode *root, *nenufar, *flower, *flower2;

    Color pink, purple, green;
    Material material_leaf, material_flower1, material_flower2;
};


#endif