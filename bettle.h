#ifndef BETTLE_H
#define BETTLE_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Bettle
{
public:
    Bettle(std::filesystem::path in_current_path):
        gold(255, 200, 50, true), material_skin()
    {
        in_current_path = in_current_path / "models" / "bettle" ;

        
        material_skin.ambient = Vector3(0.15f, 0.10f, 0.00f);
        material_skin.diffuse = Vector3(0.60f, 0.50f, 0.10f);
        material_skin.specular = Vector3(0.90f, 0.80f, 0.40f);
        material_skin.shininess = 100.0f;
        

        Mesh3D* head_mesh = new Mesh3D(in_current_path, "bettle_head.obj");
        head_mesh->add_faces(&gold);
        head_mesh->set_material(&material_skin);
        
        Mesh3D* body_mesh = new Mesh3D(in_current_path, "bettle_body.obj");
        body_mesh->add_faces(&gold);
        body_mesh->set_material(&material_skin);
		
		

        // Pata IZQ 1 (original)
        Mesh3D* leg_1_mesh = new Mesh3D(in_current_path, "bettle_leg_front1.obj");
        leg_1_mesh->add_faces(&gold);
        leg_1_mesh->set_material(&material_skin);
		
        Mesh3D* leg_2_mesh = new Mesh3D(in_current_path, "bettle_leg_front2.obj");
        leg_2_mesh->add_faces(&gold);
        leg_2_mesh->set_material(&material_skin);
		
        Mesh3D* leg_3_mesh = new Mesh3D(in_current_path, "bettle_leg_front3.obj");
        leg_3_mesh->add_faces(&gold);
        leg_3_mesh->set_material(&material_skin);
		
		
        // Pata IZQ 2
        Mesh3D* leg_1_m_i2 = new Mesh3D(in_current_path, "bettle_leg_middle1.obj");
        leg_1_m_i2->add_faces(&gold);
        leg_1_m_i2->set_material(&material_skin);
        Mesh3D* leg_2_m_i2 = new Mesh3D(in_current_path, "bettle_leg_middle2.obj");
        leg_2_m_i2->add_faces(&gold);
        leg_2_m_i2->set_material(&material_skin);
        Mesh3D* leg_3_m_i2 = new Mesh3D(in_current_path, "bettle_leg_middle3.obj");
        leg_3_m_i2->add_faces(&gold);
        leg_3_m_i2->set_material(&material_skin);
		
        // Pata IZQ 3
        Mesh3D* leg_1_m_i3 = new Mesh3D(in_current_path, "bettle_leg_behind1.obj");
        leg_1_m_i3->add_faces(&gold);
        leg_1_m_i3->set_material(&material_skin);
        Mesh3D* leg_2_m_i3 = new Mesh3D(in_current_path, "bettle_leg_behind2.obj");
        leg_2_m_i3->add_faces(&gold);
        leg_2_m_i3->set_material(&material_skin);
        Mesh3D* leg_3_m_i3 = new Mesh3D(in_current_path, "bettle_leg_behind3.obj");
        leg_3_m_i3->add_faces(&gold);
        leg_3_m_i3->set_material(&material_skin);
		

			
			
			
			
        // Pata DER 1
        Mesh3D* leg_1_m_d1 = new Mesh3D(in_current_path, "bettle_leg_front1_L.obj");
        leg_1_m_d1->add_faces(&gold);
        leg_1_m_d1->set_material(&material_skin);
        Mesh3D* leg_2_m_d1 = new Mesh3D(in_current_path, "bettle_leg_front2_L.obj");
        leg_2_m_d1->add_faces(&gold);
        leg_2_m_d1->set_material(&material_skin);
        Mesh3D* leg_3_m_d1 = new Mesh3D(in_current_path, "bettle_leg_front3_L.obj");
        leg_3_m_d1->add_faces(&gold);
        leg_3_m_d1->set_material(&material_skin);
		
	
        // Pata DER 2
        Mesh3D* leg_1_m_d2 = new Mesh3D(in_current_path, "bettle_leg_middle1_L.obj");
        leg_1_m_d2->add_faces(&gold);
        leg_1_m_d2->set_material(&material_skin);
        Mesh3D* leg_2_m_d2 = new Mesh3D(in_current_path, "bettle_leg_middle2_L.obj");
        leg_2_m_d2->add_faces(&gold);
        leg_2_m_d2->set_material(&material_skin);
        Mesh3D* leg_3_m_d2 = new Mesh3D(in_current_path, "bettle_leg_middle3_L.obj");
        leg_3_m_d2->add_faces(&gold);
        leg_3_m_d2->set_material(&material_skin);
		
			
        // Pata DER 3
        Mesh3D* leg_1_m_d3 = new Mesh3D(in_current_path, "bettle_leg_behind1_L.obj");
        leg_1_m_d3->add_faces(&gold);
        leg_1_m_d3->set_material(&material_skin);
        Mesh3D* leg_2_m_d3 = new Mesh3D(in_current_path, "bettle_leg_behind2_L.obj");
        leg_2_m_d3->add_faces(&gold);
        leg_2_m_d3->set_material(&material_skin);
        Mesh3D* leg_3_m_d3 = new Mesh3D(in_current_path, "bettle_leg_behind3_L.obj");
        leg_3_m_d3->add_faces(&gold);
        leg_3_m_d3->set_material(&material_skin);
		
		
 

        // Torso y back
        root  = new SceneNode(0);
        head = new SceneNode(1, head_mesh);
		head->traslate(Vector3(0.0f, 0.0f, 0.2f), true);	
		
        body  = new SceneNode(2, body_mesh);

        // ---- NODOS IZQ 1 (original) ----
        leg_1 = new SceneNode(3, leg_1_mesh);
        leg_1->traslate(Vector3(-0.01f, 0.0f, 0.23f), true);	
		
        leg_2 = new SceneNode(4, leg_2_mesh);
        leg_2->traslate(Vector3(-0.15f, 0.0f,  0.07f), true);
		
        leg_3 = new SceneNode(5, leg_3_mesh);
        leg_3->traslate(Vector3(-0.09f, -0.04f, 0.187f), true);


        // ---- NODOS IZQ 2 ----
        leg_i2_1 = new SceneNode(6, leg_1_m_i2);
        leg_i2_1->traslate(Vector3(-0.055f, 0.0f, 0.19f), true);
		
        leg_i2_2 = new SceneNode(7, leg_2_m_i2);
        leg_i2_2->traslate(Vector3(-0.15f, 0.0f, 0.0f), true);
        leg_i2_3 = new SceneNode(8, leg_3_m_i2);
        leg_i2_3->traslate(Vector3(-0.172f, 0.04f, -0.18f), true);

        // ---- NODOS IZQ 3 ----
        leg_i3_1 = new SceneNode(9, leg_1_m_i3);
		leg_i3_1->traslate(Vector3(-0.065f, 0.0f, 0.030f), true);
		
		
        leg_i3_2 = new SceneNode(10, leg_2_m_i3);
        leg_i3_2->traslate(Vector3(-0.13f, 0.0f,  -0.075f), true);
        leg_i3_3 = new SceneNode(11, leg_3_m_i3);
        leg_i3_3->traslate(Vector3(-0.08f, -0.015f, -0.19f), true);

      






         // ---- NODOS DER 1 ----
        leg_d1_1 = new SceneNode(15, leg_1_m_d1);
        leg_d1_1->traslate(Vector3(0.06f, 0.0f, 0.23f), true);	
      
        leg_d1_2 = new SceneNode(16, leg_2_m_d1);
        leg_d1_2->traslate(Vector3(0.15f, 0.0f,  0.07f), true);
        leg_d1_3 = new SceneNode(17, leg_3_m_d1);
        leg_d1_3->traslate(Vector3(0.09f, -0.04f, 0.187f), true);
		

        // ---- NODOS DER 2 ----
        leg_d2_1 = new SceneNode(18, leg_1_m_d2);
        leg_d2_1->traslate(Vector3(0.1f, 0.0f, 0.19f), true);
		
        leg_d2_2 = new SceneNode(19, leg_2_m_d2);
        leg_d2_2->traslate(Vector3(0.15f, 0.0f, 0.0f), true);
        leg_d2_3 = new SceneNode(20, leg_3_m_d2);
        leg_d2_3->traslate(Vector3(0.172f, 0.04f, -0.18f), true);
		
        // ---- NODOS DER 3 ----
        leg_d3_1 = new SceneNode(21, leg_1_m_d3);
        leg_d3_1->traslate(Vector3(0.1f, 0.0f, 0.030f), true);
		
        leg_d3_2 = new SceneNode(22, leg_2_m_d3);
        leg_d3_2->traslate(Vector3(0.13f, 0.0f,  -0.075f), true);
        leg_d3_3 = new SceneNode(23, leg_3_m_d3);
        leg_d3_3->traslate(Vector3(0.08f, -0.015f, -0.19f), true);






        // ---- JERARQUÍA ----
        root->add_children(body);
        body->add_children(head);
        

        body->add_children(leg_1);
        leg_1->add_children(leg_2);
        leg_2->add_children(leg_3);

        body->add_children(leg_i2_1);
        leg_i2_1->add_children(leg_i2_2);
        leg_i2_2->add_children(leg_i2_3);

        body->add_children(leg_i3_1);
        leg_i3_1->add_children(leg_i3_2);
        leg_i3_2->add_children(leg_i3_3);




        body->add_children(leg_d1_1);
        leg_d1_1->add_children(leg_d1_2);
        leg_d1_2->add_children(leg_d1_3);

        body->add_children(leg_d2_1);
        leg_d2_1->add_children(leg_d2_2);
        leg_d2_2->add_children(leg_d2_3);

        body->add_children(leg_d3_1);
        leg_d3_1->add_children(leg_d3_2);
        leg_d3_2->add_children(leg_d3_3);


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
    SceneNode *root, *head, *body, *leg_1, *leg_2, *leg_3,
                                   *leg_i2_1, *leg_i2_2, *leg_i2_3,
                                   *leg_i3_1, *leg_i3_2, *leg_i3_3,
                                   *leg_d1_1, *leg_d1_2, *leg_d1_3,
                                   *leg_d2_1, *leg_d2_2, *leg_d2_3,
                                   *leg_d3_1, *leg_d3_2, *leg_d3_3
									;

    Color gold;
    Material material_skin;
};


#endif