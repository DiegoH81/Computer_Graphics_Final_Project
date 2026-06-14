#ifndef GECKO_H
#define GECKO_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Gecko
{
public:
    Gecko(std::filesystem::path in_current_path):
        green(84, 161, 69, true), black(0, 0, 0, false), skin_material(), eye_material()
    {
        skin_material.ambient = Vector3(0.08f, 0.10f, 0.05f);
        skin_material.diffuse = Vector3(0.35f, 0.42f, 0.18f);
        skin_material.specular = Vector3(0.20f, 0.22f, 0.15f);
        skin_material.shininess = 30.0f;
		
		
        eye_material.ambient = Vector3(0.05f, 0.05f, 0.05f);
        eye_material.diffuse = Vector3(0.1f, 0.1f, 0.1f);
        eye_material.specular = Vector3(0.9f, 0.9f, 0.9f);
        eye_material.shininess = 80.0f;

        in_current_path = in_current_path / "models" / "gecko" ;

        Mesh3D* head_mesh = new Mesh3D(in_current_path, "cabeza_GECKO.obj");
        head_mesh->add_faces(&green);
        head_mesh->set_material(&skin_material);

        Mesh3D* eyes_mesh = new Mesh3D(in_current_path, "ojos_GECKO.obj");
        eyes_mesh->add_faces(&black);
        eyes_mesh->set_material(&eye_material);

        Mesh3D* tail_1_mesh = new Mesh3D(in_current_path, "cola_1_GECKO.obj");
        tail_1_mesh->add_faces(&green);
        tail_1_mesh->set_material(&skin_material);

        Mesh3D* tail_2_mesh = new Mesh3D(in_current_path, "cola_2_GECKO.obj");
        tail_2_mesh->add_faces(&green);
        tail_2_mesh->set_material(&skin_material);

        Mesh3D* tail_3_mesh = new Mesh3D(in_current_path, "cola_3_GECKO.obj");
        tail_3_mesh->add_faces(&green);
        tail_3_mesh->set_material(&skin_material);

        Mesh3D* torso_mesh = new Mesh3D(in_current_path, "torso_GECKO.obj");
        torso_mesh->add_faces(&green);
        torso_mesh->set_material(&skin_material);

        Mesh3D* pata_A_D_1_mesh = new Mesh3D(in_current_path, "pata_A_D_1_GECKO.obj");
        pata_A_D_1_mesh->add_faces(&green);
        pata_A_D_1_mesh->set_material(&skin_material);

        Mesh3D* pata_A_D_2_mesh = new Mesh3D(in_current_path, "pata_A_D_2_GECKO.obj");
        pata_A_D_2_mesh->add_faces(&green);
        pata_A_D_2_mesh->set_material(&skin_material);

        Mesh3D* pata_A_I_1_mesh = new Mesh3D(in_current_path, "pata_A_I_1_GECKO.obj");
        pata_A_I_1_mesh->add_faces(&green);
        pata_A_I_1_mesh->set_material(&skin_material);

        Mesh3D* pata_A_I_2_mesh = new Mesh3D(in_current_path, "pata_A_I_2_GECKO.obj");
        pata_A_I_2_mesh->add_faces(&green);
        pata_A_I_2_mesh->set_material(&skin_material);

        Mesh3D* pata_D_D_1_mesh = new Mesh3D(in_current_path, "pata_D_D_1_GECKO.obj");
        pata_D_D_1_mesh->add_faces(&green);
        pata_D_D_1_mesh->set_material(&skin_material);

        Mesh3D* pata_D_D_2_mesh = new Mesh3D(in_current_path, "pata_D_D_2_GECKO.obj");
        pata_D_D_2_mesh->add_faces(&green);
        pata_D_D_2_mesh->set_material(&skin_material);

        Mesh3D* pata_D_I_1_mesh = new Mesh3D(in_current_path, "pata_D_I_1_GECKO.obj");
        pata_D_I_1_mesh->add_faces(&green);
        pata_D_I_1_mesh->set_material(&skin_material);

        Mesh3D* pata_D_I_2_mesh = new Mesh3D(in_current_path, "pata_D_I_2_GECKO.obj");
        pata_D_I_2_mesh->add_faces(&green);
        pata_D_I_2_mesh->set_material(&skin_material);


        // --- Crear nodos ---
        root = new SceneNode(0);
        torso = new SceneNode(1, torso_mesh);
        head = new SceneNode(2, head_mesh);
        head->traslate(Vector3(0.0f, 0.0f, 0.4f), true);

        eyes = new SceneNode(3, eyes_mesh);
        eyes->scale(Vector3(1.1f, 1.1f, 1.1f), true);

        tail_1 = new SceneNode(4, tail_1_mesh);
        tail_1->traslate(Vector3(0.0f, 0.0f, -0.25f), true);

        tail_2 = new SceneNode(5, tail_2_mesh);
        tail_2->traslate(Vector3(0.0f, 0.0f, -0.23f), true);

        tail_3 = new SceneNode(6, tail_3_mesh);
        tail_3->traslate(Vector3(0.0f, 0.0f, -0.3f), true);


        leg_A_D_1 = new SceneNode(7, pata_A_D_1_mesh);
        leg_A_D_1->traslate(Vector3(-0.1f, 0.0f, 0.2f), true);

        leg_A_D_2 = new SceneNode(8, pata_A_D_2_mesh);
        leg_A_D_2->traslate(Vector3(-0.12f, -0.04f, 0.0f), true);

        leg_A_I_1 = new SceneNode(9, pata_A_I_1_mesh);
        leg_A_I_1->traslate(Vector3(0.1f, 0.0f, 0.2f), true);

        leg_A_I_2 = new SceneNode(10, pata_A_I_2_mesh);
        leg_A_I_2->traslate(Vector3(0.12f, -0.04f, 0.0f), true);

        leg_D_D_1 = new SceneNode(11, pata_D_D_1_mesh);
        leg_D_D_1->traslate(Vector3(-0.07f, 0.0f, -0.2f), true);

        leg_D_D_2 = new SceneNode(12, pata_D_D_2_mesh);
        leg_D_D_2->traslate(Vector3(-0.10f, -0.02f, -0.1f), true);

        leg_D_I_1 = new SceneNode(13, pata_D_I_1_mesh);
        leg_D_I_1->traslate(Vector3(0.12f, -0.05f, -0.1f), true);

        leg_D_I_2 = new SceneNode(14, pata_D_I_2_mesh);
        leg_D_I_2->traslate(Vector3(0.07f, 0.0f, -0.05f), true);

        // --- Jerarquía ---
        root->add_children(torso);
        torso->add_children(head);
        head->add_children(eyes);
        torso->add_children(tail_1);
        tail_1->add_children(tail_2);
        tail_2->add_children(tail_3);

        torso->add_children(leg_A_D_1);
        leg_A_D_1->add_children(leg_A_D_2);

        torso->add_children(leg_A_I_1);
        leg_A_I_1->add_children(leg_A_I_2);

        torso->add_children(leg_D_D_1);
        leg_D_D_1->add_children(leg_D_D_2);

        torso->add_children(leg_D_I_1);
        leg_D_I_1->add_children(leg_D_I_2);
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
    SceneNode *root, *head, *eyes, *torso, *leg_A_D_1, *leg_A_D_2,
                                 *leg_A_I_1, *leg_A_I_2,
                                 *leg_D_D_1, *leg_D_D_2,
                                 *leg_D_I_1, *leg_D_I_2,
                                 *tail_1, *tail_2, *tail_3;

    Color green, black;
    Material skin_material, eye_material;
};


#endif