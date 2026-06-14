#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Mushroom
{
public:
    Mushroom(std::filesystem::path in_current_path, bool type, bool mode):
        red(200, 20, 20, true), cream(210, 190, 140, true), white(255, 255, 255, true), 
		orange(210, 100, 20, true), purple(120, 30, 160, true), material_hat(), material_body(), material_honguito()
    {
	
	
        material_hat.ambient = Vector3(0.18f, 0.03f, 0.03f);
        material_hat.diffuse = Vector3(0.55f, 0.10f, 0.10f);
        material_hat.specular = Vector3(0.25f, 0.20f, 0.20f);
        material_hat.shininess = 20.0f;
		
        material_body.ambient = Vector3(0.18f, 0.16f, 0.12f);
        material_body.diffuse = Vector3(0.9f, 0.82f, 0.79f);
        material_body.specular = Vector3(0.08f, 0.08f, 0.08f);
        material_body.shininess = 10.0f;
        
		
		material_honguito.ambient = Vector3(0.18f, 0.15f, 0.08f);
		material_honguito.diffuse = Vector3(0.72f, 0.62f, 0.35f);
		material_honguito.specular = Vector3(0.12f, 0.10f, 0.06f);
		material_honguito.shininess = 20.0f;
				

        std::filesystem::path base = in_current_path / "models" / "plants" / "fungi";
		
		Mesh3D* body_mesh;
        Mesh3D* hat_mesh;
		Mesh3D* hat2_mesh;
		Mesh3D* hat3_mesh;
		Mesh3D* honguito_body;
		Mesh3D* honguito_hat;
		
        root = new SceneNode(0);
		
		
        if (mode)
		{
			body_mesh = new Mesh3D(base / "UNIDO", "hongo_tronco.obj");
			hat_mesh = new Mesh3D(base / "UNIDO", "hongo_copa1.obj");
			hat2_mesh = new Mesh3D(base / "UNIDO", "hongo_copa2.obj");
			hat3_mesh = new Mesh3D(base / "UNIDO", "hongo_copa3.obj");
			honguito_body = new Mesh3D(base / "UNIDO", "honguito_tronco.obj");
			honguito_hat = new Mesh3D(base / "UNIDO", "honguito_copa.obj");

			body_mesh->add_faces(&white);
			hat_mesh->add_faces(&red);
			hat2_mesh->add_faces(&orange);
			hat3_mesh->add_faces(&purple);
			honguito_body->add_faces(&white);
			honguito_hat->add_faces(&cream);

			body_mesh->set_material(&material_body);
			hat_mesh->set_material(&material_hat);
			hat2_mesh->set_material(&material_hat);
			hat3_mesh->set_material(&material_hat);
			honguito_body->set_material(&material_body);
			honguito_hat->set_material(&material_honguito);
			
			body = new SceneNode(1, body_mesh);
			hat = new SceneNode(2, hat_mesh);
			hat2 = new SceneNode(3, hat2_mesh);
			hat3 = new SceneNode(4, hat3_mesh);
			hbody = new SceneNode(5, honguito_body);
			hhat = new SceneNode(6, honguito_hat);


			body->add_children(hat2);
			body->add_children(hat3);
			root->add_children(hbody);
			hbody->add_children(hhat);
		}
        else
        {
            if (type) {
                body_mesh = new Mesh3D(base / "SEPARADO", "hongo1.obj");
                hat_mesh = new Mesh3D(base / "SEPARADO", "hongo2.obj");
                hat_mesh->add_faces(&red);
				hat_mesh->set_material(&material_hat);
            } 
			
			else {
                body_mesh = new Mesh3D(base / "SEPARADO", "honguitos1.obj");
                hat_mesh = new Mesh3D(base / "SEPARADO", "honguitos2.obj");
                hat_mesh->add_faces(&cream);
				hat_mesh->set_material(&material_honguito);
            }

            body_mesh->add_faces(&white);
            body_mesh->set_material(&material_body);
			
           
			body = new SceneNode(1, body_mesh);
			hat = new SceneNode(2, hat_mesh);
        }
    

        
		
    
        
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
    SceneNode *root, *body, *hat, *hat2, *hat3, *hbody, *hhat;

    Color red, cream, white, orange, purple;
    Material material_hat, material_body, material_honguito;
};


#endif