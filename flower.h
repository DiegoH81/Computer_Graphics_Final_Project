#ifndef FLOWER_H
#define FLOWER_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Flower
{
public:
    Flower(std::filesystem::path in_current_path, int color, bool mode):
        green(85, 130, 50, true), white(255, 255, 255, true), red(220, 30, 30, true), 
		yellow(230, 205, 25, true), blue(25, 75, 220, true), material_leaf(),
		material_flower(), material_flower2(), material_flower3(), material_flower4()
    {
		
		material_leaf.ambient = Vector3(0.05f, 0.10f, 0.03f);
        material_leaf.diffuse = Vector3(0.20f, 0.45f, 0.10f);
        material_leaf.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_leaf.shininess = 10.0f;
		
		
		
		material_flower.ambient = Vector3(0.20f, 0.20f, 0.20f); 
		material_flower.diffuse = Vector3(0.90f, 0.90f, 0.90f);
		material_flower.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_flower.shininess = 10.0f;

		material_flower2.ambient = Vector3(0.20f, 0.02f, 0.02f); 
		material_flower2.diffuse = Vector3(0.85f, 0.10f, 0.10f);
		material_flower2.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_flower2.shininess = 10.0f;

		material_flower3.ambient = Vector3(0.20f, 0.18f, 0.02f); 
		material_flower3.diffuse = Vector3(0.90f, 0.80f, 0.10f);
		material_flower3.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_flower3.shininess = 10.0f;

		material_flower4.ambient = Vector3(0.02f, 0.05f, 0.20f); 
		material_flower4.diffuse = Vector3(0.10f, 0.30f, 0.85f);
		material_flower4.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_flower4.shininess = 10.0f;


        std::filesystem::path base = in_current_path / "models" / "plants" / "bushes";
		
	
		Mesh3D* top1_mesh;
		Mesh3D* top2_mesh;
		Mesh3D* top3_mesh;
		Mesh3D* top4_mesh;
		
		Mesh3D* body_mesh;

		if (mode)
        {
            body_mesh = new Mesh3D(base / "UNIDO", "flower_body.obj");
            top1_mesh = new Mesh3D(base / "UNIDO", "flower_top1.obj");
            top2_mesh = new Mesh3D(base / "UNIDO", "flower_top2.obj");
            top3_mesh = new Mesh3D(base / "UNIDO", "flower_top3.obj");
            top4_mesh = new Mesh3D(base / "UNIDO", "flower_top4.obj");
			
			material_flower.ambient   = Vector3(0.20f, 0.15f, 0.15f);
			material_flower.diffuse   = Vector3(0.90f, 0.60f, 0.60f);
			
            body_mesh->add_faces(&green);
            top1_mesh->add_faces(&white);  
            top2_mesh->add_faces(&red);  
            top3_mesh->add_faces(&yellow);  
            top4_mesh->add_faces(&blue);  
			
			
            body_mesh->set_material(&material_leaf);
			top1_mesh->set_material(&material_flower);
			top2_mesh->set_material(&material_flower2);
			top3_mesh->set_material(&material_flower3);
			top4_mesh->set_material(&material_flower4);
			
            body = new SceneNode(1, body_mesh);
            head1 = new SceneNode(2, top1_mesh);
            head2 = new SceneNode(3, top2_mesh);
            head3 = new SceneNode(4, top3_mesh);
            head4 = new SceneNode(5, top4_mesh);
			
            body->add_children(head1);
            body->add_children(head2);
            body->add_children(head3);
            body->add_children(head4);
        }
        else
        {
            body_mesh = new Mesh3D(base / "SEPARADO", "hierva_flores1.obj");
            top1_mesh = new Mesh3D(base / "SEPARADO", "hierva_flores2.obj");

            body_mesh->add_faces(&green);
            body_mesh->set_material(&material_leaf);

            switch(color)
            { 
                case 0: 
                    material_flower.ambient = Vector3(0.20f, 0.20f, 0.20f);
                    material_flower.diffuse = Vector3(0.90f, 0.90f, 0.90f);
                    top1_mesh->add_faces(&white);
                    break;
                case 1: 
                    material_flower.ambient = Vector3(0.20f, 0.02f, 0.02f);
                    material_flower.diffuse = Vector3(0.85f, 0.10f, 0.10f);
                    top1_mesh->add_faces(&red);
                    break;
                case 2: 
                    material_flower.ambient = Vector3(0.20f, 0.18f, 0.02f);
                    material_flower.diffuse = Vector3(0.90f, 0.80f, 0.10f);
                    top1_mesh->add_faces(&yellow);
                    break;
                case 3: 
                    material_flower.ambient = Vector3(0.02f, 0.05f, 0.20f);
                    material_flower.diffuse = Vector3(0.10f, 0.30f, 0.85f);
                    top1_mesh->add_faces(&blue);
                    break;
            }
            top1_mesh->set_material(&material_flower);

            body  = new SceneNode(1, body_mesh);
            head1 = new SceneNode(2, top1_mesh);
			
            body->add_children(head1);
        }
	
		
		root = new SceneNode(0);		
        root->add_children(body);

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
    SceneNode *root, *body, *head1, *head2, *head3, *head4;

    Color green, white, red, yellow, blue;
    Material material_leaf, material_flower, material_flower2, material_flower3, material_flower4;;
};


#endif