#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Mushroom
{
public:
    Mushroom(std::filesystem::path in_current_path, bool type):
        red(200, 20, 20, true), cream(210, 190, 140, true), white(255, 255, 255, true), material_hat(), material_body()
    {
	
		if(type){
            material_hat.ambient = Vector3(0.18f, 0.03f, 0.03f);
            material_hat.diffuse = Vector3(0.55f, 0.10f, 0.10f);
            material_hat.specular = Vector3(0.25f, 0.20f, 0.20f);
            material_hat.shininess = 20.0f;
            material_body.ambient = Vector3(0.18f, 0.16f, 0.12f);
            material_body.diffuse = Vector3(0.75f, 0.72f, 0.62f);
            material_body.specular = Vector3(0.08f, 0.08f, 0.08f);
            material_body.shininess = 10.0f;
        } 
		else{
            material_hat.ambient = Vector3(0.18f, 0.15f, 0.08f);
            material_hat.diffuse = Vector3(0.72f, 0.62f, 0.35f);
            material_hat.specular = Vector3(0.12f, 0.10f, 0.06f);
            material_hat.shininess = 20.0f;
            material_body.ambient = Vector3(0.18f, 0.16f, 0.12f);
            material_body.diffuse = Vector3(0.78f, 0.74f, 0.65f);
            material_body.specular = Vector3(0.08f, 0.08f, 0.06f);
            material_body.shininess = 10.0f;
        }
		

        in_current_path = in_current_path / "models" / "plants" / "fungi";
		
		
		Mesh3D* body_mesh;
        Mesh3D* hat_mesh;

        if(type) {
            body_mesh = new Mesh3D(in_current_path, "hongo1.obj");
            hat_mesh  = new Mesh3D(in_current_path, "hongo2.obj");
        } 
		else {
            body_mesh = new Mesh3D(in_current_path, "honguitos1.obj");
            hat_mesh  = new Mesh3D(in_current_path, "honguitos2.obj");
        }
		

   
        body_mesh->add_faces(&white);
        body_mesh->set_material(&material_body);


        if(type)
            hat_mesh->add_faces(&red);
        else
            hat_mesh->add_faces(&cream);

        hat_mesh->set_material(&material_hat);

    

        root = new SceneNode(0);
        body = new SceneNode(1, body_mesh);
        hat = new SceneNode(2, hat_mesh);
		
    
        
        root->add_children(body);
        body->add_children(hat);



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
    SceneNode *root, *body, *hat;

    Color red, cream, white;
    Material material_hat, material_body;
};


#endif