#ifndef SPIDER_H
#define SPIDER_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Spider
{
public:
    Spider(std::filesystem::path in_current_path):
        gray(128, 128, 128, true), material_skin()
    {
        in_current_path = in_current_path / "models" / "spider" ;

        
        material_skin.ambient = Vector3(0.10f, 0.0f,  0.15f);
        material_skin.diffuse = Vector3(0.45f, 0.20f, 0.14f);
        material_skin.specular = Vector3(0.7f, 0.4f, 0.3f);
        material_skin.shininess = 80.0f;
        

        Mesh3D* torso_mesh = new Mesh3D(in_current_path, "spider_torso.obj");
        torso_mesh->add_faces(&gray);
        torso_mesh->set_material(&material_skin);
        
        Mesh3D* back_mesh = new Mesh3D(in_current_path, "spider_back.obj");
        back_mesh->add_faces(&gray);
        back_mesh->set_material(&material_skin);

        // Pata IZQ 1 (original)
        Mesh3D* leg_1_mesh = new Mesh3D(in_current_path, "spider_leg1_L.obj");
        leg_1_mesh->add_faces(&gray);
        leg_1_mesh->set_material(&material_skin);
		
        Mesh3D* leg_2_mesh = new Mesh3D(in_current_path, "spider_leg2_L.obj");
        leg_2_mesh->add_faces(&gray);
        leg_2_mesh->set_material(&material_skin);
		
        Mesh3D* leg_3_mesh = new Mesh3D(in_current_path, "spider_leg3_L.obj");
        leg_3_mesh->add_faces(&gray);
        leg_3_mesh->set_material(&material_skin);
		
		
	
        // Pata IZQ 2
        Mesh3D* leg_1_m_i2 = new Mesh3D(in_current_path, "spider_leg1_L.obj");
        leg_1_m_i2->add_faces(&gray);
        leg_1_m_i2->set_material(&material_skin);
        Mesh3D* leg_2_m_i2 = new Mesh3D(in_current_path, "spider_leg2_L.obj");
        leg_2_m_i2->add_faces(&gray);
        leg_2_m_i2->set_material(&material_skin);
        Mesh3D* leg_3_m_i2 = new Mesh3D(in_current_path, "spider_leg3_L.obj");
        leg_3_m_i2->add_faces(&gray);
        leg_3_m_i2->set_material(&material_skin);
		
			
		
		
		
        // Pata IZQ 3
        Mesh3D* leg_1_m_i3 = new Mesh3D(in_current_path, "spider_leg1_L.obj");
        leg_1_m_i3->add_faces(&gray);
        leg_1_m_i3->set_material(&material_skin);
        Mesh3D* leg_2_m_i3 = new Mesh3D(in_current_path, "spider_leg2_L.obj");
        leg_2_m_i3->add_faces(&gray);
        leg_2_m_i3->set_material(&material_skin);
        Mesh3D* leg_3_m_i3 = new Mesh3D(in_current_path, "spider_leg3_L.obj");
        leg_3_m_i3->add_faces(&gray);
        leg_3_m_i3->set_material(&material_skin);
		

		
        // Pata IZQ 4
        Mesh3D* leg_1_m_i4 = new Mesh3D(in_current_path, "spider_leg1_L.obj");
        leg_1_m_i4->add_faces(&gray);
        leg_1_m_i4->set_material(&material_skin);
        Mesh3D* leg_2_m_i4 = new Mesh3D(in_current_path, "spider_leg2_L.obj");
        leg_2_m_i4->add_faces(&gray);
        leg_2_m_i4->set_material(&material_skin);
        Mesh3D* leg_3_m_i4 = new Mesh3D(in_current_path, "spider_leg3_L.obj");
        leg_3_m_i4->add_faces(&gray);
        leg_3_m_i4->set_material(&material_skin);
		
				
        // Pata DER 1
        Mesh3D* leg_1_m_d1 = new Mesh3D(in_current_path, "spider_leg1_R.obj");
        leg_1_m_d1->add_faces(&gray);
        leg_1_m_d1->set_material(&material_skin);
        Mesh3D* leg_2_m_d1 = new Mesh3D(in_current_path, "spider_leg2_R.obj");
        leg_2_m_d1->add_faces(&gray);
        leg_2_m_d1->set_material(&material_skin);
        Mesh3D* leg_3_m_d1 = new Mesh3D(in_current_path, "spider_leg3_R.obj");
        leg_3_m_d1->add_faces(&gray);
        leg_3_m_d1->set_material(&material_skin);
		
		
        // Pata DER 2
        Mesh3D* leg_1_m_d2 = new Mesh3D(in_current_path, "spider_leg1_R.obj");
        leg_1_m_d2->add_faces(&gray);
        leg_1_m_d2->set_material(&material_skin);
        Mesh3D* leg_2_m_d2 = new Mesh3D(in_current_path, "spider_leg2_R.obj");
        leg_2_m_d2->add_faces(&gray);
        leg_2_m_d2->set_material(&material_skin);
        Mesh3D* leg_3_m_d2 = new Mesh3D(in_current_path, "spider_leg3_R.obj");
        leg_3_m_d2->add_faces(&gray);
        leg_3_m_d2->set_material(&material_skin);
		
		
        // Pata DER 3
        Mesh3D* leg_1_m_d3 = new Mesh3D(in_current_path, "spider_leg1_R.obj");
        leg_1_m_d3->add_faces(&gray);
        leg_1_m_d3->set_material(&material_skin);
        Mesh3D* leg_2_m_d3 = new Mesh3D(in_current_path, "spider_leg2_R.obj");
        leg_2_m_d3->add_faces(&gray);
        leg_2_m_d3->set_material(&material_skin);
        Mesh3D* leg_3_m_d3 = new Mesh3D(in_current_path, "spider_leg3_R.obj");
        leg_3_m_d3->add_faces(&gray);
        leg_3_m_d3->set_material(&material_skin);
		
		
       // Pata DER 4
        Mesh3D* leg_1_m_d4 = new Mesh3D(in_current_path, "spider_leg1_R.obj");
        leg_1_m_d4->add_faces(&gray);
        leg_1_m_d4->set_material(&material_skin);
        Mesh3D* leg_2_m_d4 = new Mesh3D(in_current_path, "spider_leg2_R.obj"); 
        leg_2_m_d4->add_faces(&gray);
        leg_2_m_d4->set_material(&material_skin);
        Mesh3D* leg_3_m_d4 = new Mesh3D(in_current_path, "spider_leg3_R.obj");
        leg_3_m_d4->add_faces(&gray);
		leg_3_m_d4->set_material(&material_skin);	

        // Torso y back
        root  = new SceneNode(0);
        torso = new SceneNode(1, torso_mesh);
        back  = new SceneNode(2, back_mesh);

        // ---- NODOS IZQ 1 (original) ----
        leg_1 = new SceneNode(3, leg_1_mesh);
        leg_1->traslate(Vector3(0.08f, 0.01f, 0.1f), true);	
		
        leg_2 = new SceneNode(4, leg_2_mesh);
        leg_2->traslate(Vector3(0.087f, 0.2f,  0.145f), true);
		
        leg_3 = new SceneNode(5, leg_3_mesh);
        leg_3->traslate(Vector3(0.079f, -0.07f, 0.21f), true);

        // ---- NODOS IZQ 2 ----
        leg_i2_1 = new SceneNode(6, leg_1_m_i2);
        leg_i2_1->traslate(Vector3(0.08f, 0.01f, 0.065f), true);
		leg_i2_1->rotate_y_local(40.0f, true);
		
        leg_i2_2 = new SceneNode(7, leg_2_m_i2);
        leg_i2_2->traslate(Vector3(0.087f, 0.2f,  0.145f), true);
        leg_i2_3 = new SceneNode(8, leg_3_m_i2);
        leg_i2_3->traslate(Vector3(0.079f, -0.07f, 0.21f), true);

        // ---- NODOS IZQ 3 ----
        leg_i3_1 = new SceneNode(9, leg_1_m_i3);
		leg_i3_1->traslate(Vector3(0.08f, 0.01f, 0.030f), true);
		leg_i3_1->rotate_y_local(80.0f, true);
		
		
        leg_i3_2 = new SceneNode(10, leg_2_m_i3);
        leg_i3_2->traslate(Vector3(0.087f, 0.2f,  0.145f), true);
        leg_i3_3 = new SceneNode(11, leg_3_m_i3);
        leg_i3_3->traslate(Vector3(0.079f, -0.07f, 0.21f), true);

       // ---- NODOS IZQ 4 ----
        leg_i4_1 = new SceneNode(12, leg_1_m_i4);
        leg_i4_1->traslate(Vector3(0.08f, 0.01f, -0.005f), true);
		leg_i4_1->rotate_y_local(120.0f, true);
		
        leg_i4_2 = new SceneNode(13, leg_2_m_i4);
        leg_i4_2->traslate(Vector3(0.087f, 0.2f,  0.145f), true);
        leg_i4_3 = new SceneNode(14, leg_3_m_i4);
        leg_i4_3->traslate(Vector3(0.079f, -0.07f, 0.21f), true);









         // ---- NODOS DER 1 ----
        leg_d1_1 = new SceneNode(15, leg_1_m_d1);
        leg_d1_1->traslate(Vector3(-0.082f, 0.01f, 0.1f), true);	
      
        leg_d1_2 = new SceneNode(16, leg_2_m_d1);
        leg_d1_2->traslate(Vector3(-0.067f, 0.2f,  0.135f), true);
        leg_d1_3 = new SceneNode(17, leg_3_m_d1);
        leg_d1_3->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        // ---- NODOS DER 2 ----
        leg_d2_1 = new SceneNode(18, leg_1_m_d2);
        leg_d2_1->traslate(Vector3(-0.082f, 0.01f, 0.065f), true);	
        leg_d2_1->rotate_y_local(-40.0f, true);
		
        leg_d2_2 = new SceneNode(19, leg_2_m_d2);
        leg_d2_2->traslate(Vector3(-0.067f, 0.2f,  0.135f), true);
        leg_d2_3 = new SceneNode(20, leg_3_m_d2);
        leg_d2_3->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        // ---- NODOS DER 3 ----
        leg_d3_1 = new SceneNode(21, leg_1_m_d3);
        leg_d3_1->traslate(Vector3(-0.082f, 0.01f, 0.030f), true);	
		leg_d3_1->rotate_y_local(-80.0f, true);
		
        leg_d3_2 = new SceneNode(22, leg_2_m_d3);
        leg_d3_2->traslate(Vector3(-0.067f, 0.2f,  0.135f), true);
        leg_d3_3 = new SceneNode(23, leg_3_m_d3);
        leg_d3_3->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        // ---- NODOS DER 4 ----
        leg_d4_1 = new SceneNode(24, leg_1_m_d4);
        leg_d4_1->traslate(Vector3(-0.082f, 0.01f, -0.005f), true);	
        leg_d4_1->rotate_y_local(-120.0f, true);
		
        leg_d4_2 = new SceneNode(25, leg_2_m_d4);
        leg_d4_2->traslate(Vector3(-0.067f, 0.2f,  0.135f), true);
        leg_d4_3 = new SceneNode(26, leg_3_m_d4);
        leg_d4_3->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        // ---- JERARQUÍA ----
        root->add_children(torso);
        torso->add_children(back);
        

        torso->add_children(leg_1);
        leg_1->add_children(leg_2);
        leg_2->add_children(leg_3);

        torso->add_children(leg_i2_1);
        leg_i2_1->add_children(leg_i2_2);
        leg_i2_2->add_children(leg_i2_3);

        torso->add_children(leg_i3_1);
        leg_i3_1->add_children(leg_i3_2);
        leg_i3_2->add_children(leg_i3_3);

       torso->add_children(leg_i4_1);
        leg_i4_1->add_children(leg_i4_2);
        leg_i4_2->add_children(leg_i4_3);

        torso->add_children(leg_d1_1);
        leg_d1_1->add_children(leg_d1_2);
        leg_d1_2->add_children(leg_d1_3);

        torso->add_children(leg_d2_1);
        leg_d2_1->add_children(leg_d2_2);
        leg_d2_2->add_children(leg_d2_3);

        torso->add_children(leg_d3_1);
        leg_d3_1->add_children(leg_d3_2);
        leg_d3_2->add_children(leg_d3_3);

        torso->add_children(leg_d4_1);
        leg_d4_1->add_children(leg_d4_2);
        leg_d4_2->add_children(leg_d4_3);


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
    SceneNode *root, *torso, *back, *leg_1, *leg_2, *leg_3,
                                  *leg_i2_1, *leg_i2_2, *leg_i2_3,
                                      *leg_i3_1, *leg_i3_2, *leg_i3_3,
                                    *leg_i4_1, *leg_i4_2, *leg_i4_3,
                                    *leg_d1_1, *leg_d1_2, *leg_d1_3,
                                    *leg_d2_1, *leg_d2_2, *leg_d2_3,
                                    *leg_d3_1, *leg_d3_2, *leg_d3_3,
                                    *leg_d4_1, *leg_d4_2, *leg_d4_3;

    Color gray;
    Material material_skin;
};


#endif