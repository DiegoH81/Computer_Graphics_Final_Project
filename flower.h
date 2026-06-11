#ifndef FLOWER_H
#define FLOWER_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Flower
{
public:
    Flower(std::filesystem::path in_current_path, int color):
        green(85, 130, 50, true), white(255,255,255,true), material_leaf(), material_flower()
    {
		
		material_leaf.ambient = Vector3(0.05f, 0.10f, 0.03f);
        material_leaf.diffuse = Vector3(0.20f, 0.45f, 0.10f);
        material_leaf.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_leaf.shininess = 10.0f;
		
		material_flower.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_flower.shininess = 10.0f;

        in_current_path = in_current_path / "models" / "plants" / "bushes";
		
	
		Mesh3D* head_mesh;
		Mesh3D* body_mesh;

        switch(color)
        { 
			case 0: 
				material_flower.ambient = Vector3(0.20f, 0.20f, 0.20f);
                material_flower.diffuse = Vector3(0.90f, 0.90f, 0.90f);
				break;
			case 1: 
				material_flower.ambient = Vector3(0.20f, 0.02f, 0.02f);
                material_flower.diffuse = Vector3(0.85f, 0.10f, 0.10f);
				break;
            case 2: 
				material_flower.ambient = Vector3(0.20f, 0.18f, 0.02f);
                material_flower.diffuse = Vector3(0.90f, 0.80f, 0.10f);
				break;
            case 3: 
				material_flower.ambient = Vector3(0.02f, 0.05f, 0.20f);
				material_flower.diffuse = Vector3(0.10f, 0.30f, 0.85f);
				break;
     
      
        }
        
		body_mesh = new Mesh3D(in_current_path,  "hierva_flores1.obj"); 
		head_mesh = new Mesh3D(in_current_path,  "hierva_flores2.obj"); 
		

        body_mesh->add_faces(&green);
        body_mesh->set_material(&material_leaf);
		
		head_mesh->add_faces(&white);
        head_mesh->set_material(&material_flower);

        root = new SceneNode(0);
        body = new SceneNode(1, body_mesh);
        head = new SceneNode(2, head_mesh);
		
       

        root->add_children(body);
        body->add_children(head);




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
    SceneNode *root, *head, *body;

    Color green, white;
    Material material_leaf, material_flower;
};


#endif