#ifndef ALGAE_H
#define ALGAE_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Algae
{
public:
    Algae(std::filesystem::path in_current_path):
        green(105, 150, 80, true), material_algae()
    {
		material_algae.ambient = Vector3(0.02f, 0.08f, 0.06f);
		material_algae.diffuse = Vector3(0.10f, 0.40f, 0.25f);
		material_algae.specular = Vector3(0.30f, 0.50f, 0.40f);
		material_algae.shininess = 80.0f;


        in_current_path = in_current_path / "models" / "in_water" / "algae";

        Mesh3D* body_mesh1 = new Mesh3D(in_current_path, "alga1.obj");
        Mesh3D* body_mesh2 = new Mesh3D(in_current_path, "alga2.obj");
        Mesh3D* body_mesh3 = new Mesh3D(in_current_path, "alga3.obj");
        Mesh3D* body_mesh4 = new Mesh3D(in_current_path, "alga4.obj");
        Mesh3D* body_mesh5 = new Mesh3D(in_current_path, "alga5.obj");
        Mesh3D* body_mesh6 = new Mesh3D(in_current_path, "alga6.obj");
        Mesh3D* body_mesh7 = new Mesh3D(in_current_path, "alga7.obj");
        Mesh3D* body_mesh8 = new Mesh3D(in_current_path, "alga8.obj");
		
		
        body_mesh1->add_faces(&green);
        body_mesh1->set_material(&material_algae);

		body_mesh2->add_faces(&green);
        body_mesh2->set_material(&material_algae);
		
		body_mesh3->add_faces(&green);
        body_mesh3->set_material(&material_algae);
		
		body_mesh4->add_faces(&green);
        body_mesh4->set_material(&material_algae);
		
		body_mesh5->add_faces(&green);
        body_mesh5->set_material(&material_algae);
		
		body_mesh6->add_faces(&green);
        body_mesh6->set_material(&material_algae);
		
		body_mesh7->add_faces(&green);
        body_mesh7->set_material(&material_algae);
		
		body_mesh8->add_faces(&green);
        body_mesh8->set_material(&material_algae);

  

    

        root = new SceneNode(0);
        alga1 = new SceneNode(1, body_mesh1);
        alga2 = new SceneNode(2, body_mesh2);
        alga3 = new SceneNode(3, body_mesh3);
        alga4 = new SceneNode(4, body_mesh4);
        alga5 = new SceneNode(5, body_mesh5);
        alga6 = new SceneNode(6, body_mesh6);
        alga7 = new SceneNode(7, body_mesh7);
        alga8 = new SceneNode(8, body_mesh8);
		
		

		
    
        
        root->add_children(alga1);
        root->add_children(alga2);
        root->add_children(alga3);
        root->add_children(alga4);
        root->add_children(alga5);
        root->add_children(alga6);
        root->add_children(alga7);
        root->add_children(alga8);
		
    



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
    SceneNode *root, *alga1, *alga2, *alga3, *alga4, *alga5, *alga6, *alga7, *alga8;

    Color green;
    Material material_algae;
};


#endif