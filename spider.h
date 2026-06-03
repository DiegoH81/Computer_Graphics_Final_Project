#ifndef SPIDER_H
#define SPIDER_H

#include <filesystem>

#include "scene.h"
#include "shape.h"


class Spider
{
public:
    Spider(std::filesystem::path in_current_path):
        purple(97, 49, 130, true)
    {
        in_current_path = in_current_path / "models" / "spider" ;

        Mesh3D* torso_mesh = new Mesh3D(in_current_path, "spider_torso.obj");
        torso_mesh->add_faces(&purple);
        
        Mesh3D* back_mesh = new Mesh3D(in_current_path, "spider_back.obj");
        back_mesh->add_faces(&purple);

        // Pata IZQ 1 (original)
        Mesh3D* leg_1_mesh = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_mesh->add_faces(&purple);
        Mesh3D* leg_2_mesh = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_mesh->add_faces(&purple);
        Mesh3D* leg_3_mesh = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_mesh->add_faces(&purple);
        // Pata IZQ 2
        Mesh3D* leg_1_m_i2 = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_m_i2->add_faces(&purple);
        Mesh3D* leg_2_m_i2 = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_m_i2->add_faces(&purple);
        Mesh3D* leg_3_m_i2 = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_m_i2->add_faces(&purple);
        // Pata IZQ 3
        Mesh3D* leg_1_m_i3 = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_m_i3->add_faces(&purple);
        Mesh3D* leg_2_m_i3 = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_m_i3->add_faces(&purple);
        Mesh3D* leg_3_m_i3 = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_m_i3->add_faces(&purple);
        // Pata IZQ 4
        Mesh3D* leg_1_m_i4 = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_m_i4->add_faces(&purple);
        Mesh3D* leg_2_m_i4 = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_m_i4->add_faces(&purple);
        Mesh3D* leg_3_m_i4 = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_m_i4->add_faces(&purple);
        // Pata DER 1
        Mesh3D* leg_1_m_d1 = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_m_d1->add_faces(&purple);
        Mesh3D* leg_2_m_d1 = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_m_d1->add_faces(&purple);
        Mesh3D* leg_3_m_d1 = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_m_d1->add_faces(&purple);
        // Pata DER 2
        Mesh3D* leg_1_m_d2 = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_m_d2->add_faces(&purple);
        Mesh3D* leg_2_m_d2 = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_m_d2->add_faces(&purple);
        Mesh3D* leg_3_m_d2 = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_m_d2->add_faces(&purple);
        // Pata DER 3
        Mesh3D* leg_1_m_d3 = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_m_d3->add_faces(&purple);
        Mesh3D* leg_2_m_d3 = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_m_d3->add_faces(&purple);
        Mesh3D* leg_3_m_d3 = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_m_d3->add_faces(&purple);
        // Pata DER 4
        Mesh3D* leg_1_m_d4 = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_m_d4->add_faces(&purple);
        Mesh3D* leg_2_m_d4 = new Mesh3D(in_current_path, "spider_leg2.obj"); 
        leg_2_m_d4->add_faces(&purple);
        Mesh3D* leg_3_m_d4 = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_m_d4->add_faces(&purple);


        // Torso y back
        root  = new SceneNode(0);
        torso = new SceneNode(1, torso_mesh);
        back  = new SceneNode(2, back_mesh);

        // ---- NODOS IZQ 1 (original) ----
        leg_1 = new SceneNode(3, leg_1_mesh);
        leg_1->traslate(Vector3(-0.02f, 0.0f, 0.10f), true);
        leg_1->rotate_y_local(15.0f, true);
        leg_2 = new SceneNode(4, leg_2_mesh);
        leg_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_3 = new SceneNode(5, leg_3_mesh);
        leg_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

        // ---- NODOS IZQ 2 ----
        leg_i2_1 = new SceneNode(6, leg_1_m_i2);
        leg_i2_1->traslate(Vector3(-0.02f, 0.0f, 0.06f), true);
        leg_i2_1->rotate_y_local(13.0f, true);
        leg_i2_2 = new SceneNode(7, leg_2_m_i2);
        leg_i2_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_i2_3 = new SceneNode(8, leg_3_m_i2);
        leg_i2_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

        // ---- NODOS IZQ 3 ----
        leg_i3_1 = new SceneNode(9, leg_1_m_i3);
        leg_i3_1->traslate(Vector3(-0.02f, 0.0f, 0.04f), true);
        leg_i3_1->rotate_y_local(10.0f, true);
        leg_i3_2 = new SceneNode(10, leg_2_m_i3);
        leg_i3_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_i3_3 = new SceneNode(11, leg_3_m_i3);
        leg_i3_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

        // ---- NODOS IZQ 4 ----
        leg_i4_1 = new SceneNode(12, leg_1_m_i4);
        leg_i4_1->traslate(Vector3(-0.02f, 0.0f, 0.02f), true);
        leg_i4_2 = new SceneNode(13, leg_2_m_i4);
        leg_i4_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_i4_3 = new SceneNode(14, leg_3_m_i4);
        leg_i4_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

        // ---- NODOS DER 1 ----
        leg_d1_1 = new SceneNode(15, leg_1_m_d1);
        leg_d1_1->traslate(Vector3(-0.02f, 0.0f, 0.10f), true);
        leg_d1_1->scale(Vector3(-1.0f, 1.0f, 1.0f), true);
        leg_d1_1->rotate_y_local(15.0f, true);
        leg_d1_2 = new SceneNode(16, leg_2_m_d1);
        leg_d1_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_d1_3 = new SceneNode(17, leg_3_m_d1);
        leg_d1_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

        // ---- NODOS DER 2 ----
        leg_d2_1 = new SceneNode(18, leg_1_m_d2);
        leg_d2_1->traslate(Vector3(-0.02f, 0.0f, 0.06f), true);
        leg_d2_1->scale(Vector3(-1.0f, 1.0f, 1.0f), true);
        leg_d2_1->rotate_y_local(13.0f, true);
        leg_d2_2 = new SceneNode(19, leg_2_m_d2);
        leg_d2_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_d2_3 = new SceneNode(20, leg_3_m_d2);
        leg_d2_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

        // ---- NODOS DER 3 ----
        leg_d3_1 = new SceneNode(21, leg_1_m_d3);
        leg_d3_1->traslate(Vector3(-0.02f, 0.0f, 0.04f), true);
        leg_d3_1->scale(Vector3(-1.0f, 1.0f, 1.0f), true);
        leg_d3_2 = new SceneNode(22, leg_2_m_d3);
        leg_d3_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_d3_3 = new SceneNode(23, leg_3_m_d3);
        leg_d3_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

        // ---- NODOS DER 4 ----
        leg_d4_1 = new SceneNode(24, leg_1_m_d4);
        leg_d4_1->traslate(Vector3(-0.02f, 0.0f, 0.02f), true);
        leg_d4_1->scale(Vector3(-1.0f, 1.0f, 1.0f), true);
        leg_d4_1->rotate_y_local(10.0f, true);
        leg_d4_2 = new SceneNode(25, leg_2_m_d4);
        leg_d4_2->traslate(Vector3(-0.23f, 0.14f, -0.08f), true);
        leg_d4_3 = new SceneNode(26, leg_3_m_d4);
        leg_d4_3->traslate(Vector3(-0.17f, 0.0f, -0.08f), true);

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



    Color purple;
};


#endif