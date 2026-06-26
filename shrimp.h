#ifndef SHRIMP_H
#define SHRIMP_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Shrimp
{
public:
    Shrimp(std::filesystem::path in_current_path):
        black(0, 0, 0, false), orange(255, 140, 0, true), blue(30,  80, 200, true),
		gray(128, 128, 128, true), metal_material(), chair_material(), skin_material(), eye_material()
    {
		metal_material.ambient = Vector3(0.2f, 0.2f, 0.2f);
        metal_material.diffuse = Vector3(0.6f, 0.6f, 0.6f);
        metal_material.specular = Vector3(0.8f, 0.8f, 0.8f);
        metal_material.shininess = 200.0f;
		
        chair_material.ambient = Vector3(0.1f, 0.1f, 0.25f);
        chair_material.diffuse = Vector3(0.15f, 0.25f, 0.7f);
        chair_material.specular = Vector3(0.05f, 0.05f, 0.05f);
        chair_material.shininess = 5.0f;
        
		skin_material.ambient = Vector3(0.4f, 0.2f, 0.1f);
        skin_material.diffuse = Vector3(0.8f, 0.4f, 0.1f);
        skin_material.specular  = Vector3(0.9f, 0.7f, 0.5f);  
		skin_material.shininess = 150.0f;;

        eye_material.ambient = Vector3(0.05f, 0.05f, 0.05f);
        eye_material.diffuse = Vector3(0.1f, 0.1f, 0.1f);
        eye_material.specular = Vector3(0.9f, 0.9f, 0.9f);
        eye_material.shininess = 64.0f;
		
		

        in_current_path = in_current_path / "models" / "shrimp" ;

        Mesh3D* chair_bottom_top_mesh = new Mesh3D(in_current_path, "shrimp_chair1.obj");
        Mesh3D* chair_bottom_bottom_mesh = new Mesh3D(in_current_path, "shrimp_chair1_1.obj");
        Mesh3D* chair_top_mesh = new Mesh3D(in_current_path, "shrimp_chair2.obj");
		Mesh3D* eyes_mesh = new Mesh3D(in_current_path, "shrimp_chair3.obj");
		Mesh3D* body_mesh = new Mesh3D(in_current_path, "shrimp_chair4.obj");
		
		Mesh3D* lil_eyes_mesh = new Mesh3D(in_current_path, "lil_shrimp_eyes.obj");
		Mesh3D* lil_body_mesh = new Mesh3D(in_current_path, "lil_shrimp.obj");
		
		
        chair_top_mesh->add_faces(&chair_material);
        chair_bottom_top_mesh->add_faces(&metal_material);
        chair_bottom_bottom_mesh->add_faces(&metal_material);
		eyes_mesh->add_faces(&eye_material);
		body_mesh->add_faces(&skin_material);
		
		lil_eyes_mesh->add_faces(&eye_material);
		lil_body_mesh->add_faces(&skin_material);
		

        root = new SceneNode(0);
        upper_root = new SceneNode(1);
        chair_bottom_top = new SceneNode(2, chair_bottom_top_mesh);
        chair_bottom_bottom = new SceneNode(3, chair_bottom_bottom_mesh);
		//chair_bottom->scale(Vector3(0.1f,0.1f,0.1f),true);
		//chair_bottom->traslate(Vector3(-0.023f, 0.0f, 0.0f), true);
		
		
        chair_top = new SceneNode(4, chair_top_mesh);
		//chair_top->scale(Vector3(0.1f,0.1f,0.1f),true);

        eyes = new SceneNode(5, eyes_mesh);
        //eyes->traslate(Vector3(1.8f, 2.35f, -0.005f), true);


        body = new SceneNode(6, body_mesh);
		//body->scale(Vector3(0.1f,0.1f,0.1f),true);
        //body->traslate(Vector3(-0.06f, 0.12f, 0.0f), false);
		//body->traslate(Vector3(-0.026f, 0.0f, 0.0f), true);
		
		lil_eyes = new SceneNode(7, lil_eyes_mesh);
		lil_body = new SceneNode(8, lil_body_mesh);
    
    
		root->add_children(lil_body);
		lil_body->add_children(lil_eyes);
		
        
        root->add_children(chair_bottom_bottom);

        upper_root->add_children(chair_bottom_top);
        upper_root->add_children(chair_top);
        upper_root->add_children(body);
        upper_root->add_children(eyes);

        root->add_children(upper_root);

        root->traslate(Vector3(-15.5f, 0.0f, 0.0f), true);

    }

    void draw(ShaderList& in_shaders, TextureList& in_texturs, const Matrix_4& in_mat)
    {
        root->draw(in_shaders, in_texturs, in_mat);
    }

    SceneNode* get_root()
    {
        return root;
    }

     SceneNode* get_upper_root()
    {
        return upper_root;
    }


private:
    SceneNode *root, *upper_root,*chair_bottom_top, *chair_bottom_bottom, *chair_top, *eyes, *body, *lil_eyes, *lil_body;

    Color black, orange, blue, gray;
    Material metal_material, chair_material, skin_material, eye_material;
};


#endif