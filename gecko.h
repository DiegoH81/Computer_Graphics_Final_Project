#ifndef GECKO_H
#define GECKO_H

#include <filesystem>
#include "scene.h"
#include "shape.h"
#include "material.h"
#include "creature_base.h"

class Gecko : public CreatureBase<4>
{
public:
    Gecko(std::filesystem::path in_current_path) :
        green(84, 161, 69, true), black(0, 0, 0, false),
        skin_material(), eye_material()
    {
        skin_material.ambient   = Vector3(0.08f, 0.10f, 0.05f);
        skin_material.diffuse   = Vector3(0.35f, 0.42f, 0.18f);
        skin_material.specular  = Vector3(0.20f, 0.22f, 0.15f);
        skin_material.shininess = 30.0f;

        eye_material.ambient    = Vector3(0.05f, 0.05f, 0.05f);
        eye_material.diffuse    = Vector3(0.1f,  0.1f,  0.1f);
        eye_material.specular   = Vector3(0.9f,  0.9f,  0.9f);
        eye_material.shininess  = 80.0f;

        in_current_path = in_current_path / "models" / "gecko";

        auto make_skin = [&](const char* file) -> Mesh3D* {
            Mesh3D* m = new Mesh3D(in_current_path, file);
            m->add_faces(&green);
            m->set_material(&skin_material);
            return m;
        };

        Mesh3D* head_mesh = make_skin("cabeza_GECKO.obj");
        Mesh3D* tail_1_mesh = make_skin("cola_1_GECKO.obj");
        Mesh3D* tail_2_mesh = make_skin("cola_2_GECKO.obj");
        Mesh3D* tail_3_mesh = make_skin("cola_3_GECKO.obj");
        Mesh3D* torso_mesh = make_skin("torso_GECKO.obj");
        Mesh3D* pad1_mesh = make_skin("pata_A_D_1_GECKO.obj");
        Mesh3D* pad2_mesh = make_skin("pata_A_D_2_GECKO.obj");
        Mesh3D* pai1_mesh = make_skin("pata_A_I_1_GECKO.obj");
        Mesh3D* pai2_mesh = make_skin("pata_A_I_2_GECKO.obj");
        Mesh3D* ppd1_mesh = make_skin("pata_D_D_1_GECKO.obj");
        Mesh3D* ppd2_mesh = make_skin("pata_D_D_2_GECKO.obj");
        Mesh3D* ppi1_mesh = make_skin("pata_D_I_1_GECKO.obj");
        Mesh3D* ppi2_mesh = make_skin("pata_D_I_2_GECKO.obj");

        Mesh3D* eyes_mesh = new Mesh3D(in_current_path, "ojos_GECKO.obj");
        eyes_mesh->add_faces(&black);
        eyes_mesh->set_material(&eye_material);

        m_root = new SceneNode(0);
        m_torso = new SceneNode(1, torso_mesh);
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

        leg_A_D_1 = new SceneNode(7,  pad1_mesh);  leg_A_D_1->traslate(Vector3(-0.1f,  0.0f,  0.2f),  true);
        leg_A_D_2 = new SceneNode(8,  pad2_mesh);  leg_A_D_2->traslate(Vector3(-0.12f,-0.04f, 0.0f),  true);
        leg_A_I_1 = new SceneNode(9,  pai1_mesh);  leg_A_I_1->traslate(Vector3( 0.1f,  0.0f,  0.2f),  true);
        leg_A_I_2 = new SceneNode(10, pai2_mesh);  leg_A_I_2->traslate(Vector3( 0.12f,-0.04f, 0.0f),  true);
        leg_D_D_1 = new SceneNode(11, ppd1_mesh);  leg_D_D_1->traslate(Vector3(-0.07f, 0.0f, -0.2f),  true);
        leg_D_D_2 = new SceneNode(12, ppd2_mesh);  leg_D_D_2->traslate(Vector3(-0.10f,-0.02f,-0.1f),  true);
        leg_D_I_1 = new SceneNode(13, ppi1_mesh);  leg_D_I_1->traslate(Vector3( 0.12f,-0.05f,-0.1f),  true);
        leg_D_I_2 = new SceneNode(14, ppi2_mesh);  leg_D_I_2->traslate(Vector3( 0.07f, 0.0f, -0.05f), true);

        m_root->add_children(m_torso);
        m_torso->add_children(head);
        head->add_children(eyes);
        m_torso->add_children(tail_1);
        tail_1->add_children(tail_2);
        tail_2->add_children(tail_3);

        m_torso->add_children(leg_A_D_1);  leg_A_D_1->add_children(leg_A_D_2);
        m_torso->add_children(leg_A_I_1);  leg_A_I_1->add_children(leg_A_I_2);
        m_torso->add_children(leg_D_D_1);  leg_D_D_1->add_children(leg_D_D_2);
        m_torso->add_children(leg_D_I_1);  leg_D_I_1->add_children(leg_D_I_2);

        legs[0].init(leg_A_D_1, leg_A_D_2,
            Vector3(-0.28f,-0.08f, 0.20f), Vector3(-0.10f, 0.00f, 0.20f), 0.088f, 0.094f);
        legs[1].init(leg_A_I_1, leg_A_I_2,
            Vector3( 0.28f,-0.08f, 0.20f), Vector3( 0.10f, 0.00f, 0.20f), 0.087f, 0.092f);
        legs[2].init(leg_D_D_1, leg_D_D_2,
            Vector3(-0.24f,-0.08f,-0.28f), Vector3(-0.07f, 0.00f,-0.20f), 0.065f, 0.103f);
        legs[3].init(leg_D_I_1, leg_D_I_2,
            Vector3( 0.28f,-0.08f,-0.18f), Vector3( 0.12f, 0.00f,-0.10f), 0.127f, 0.109f);

        legs[0].step_range = (0.088f + 0.094f) * 0.40f;
        legs[1].step_range = (0.087f + 0.092f) * 0.40f;
        legs[2].step_range = (0.065f + 0.103f) * 0.40f;
        legs[3].step_range = (0.127f + 0.109f) * 0.40f;

        legs[0].yaw_offset = PI * 0.5f;
        legs[1].yaw_offset = -PI * 0.5f;
        legs[2].yaw_offset = PI * 0.75f;
        legs[3].yaw_offset = -2.1910f;

        legs[0].diagonal_pair = &legs[3];
        legs[3].diagonal_pair = &legs[0];
        legs[1].diagonal_pair = &legs[2];
        legs[2].diagonal_pair = &legs[1];

        legs[0].current_foot = legs[0].rest_offset + Vector3(-0.05f, 0.0f,  0.05f);
        legs[3].current_foot = legs[3].rest_offset + Vector3( 0.05f, 0.0f, -0.05f);
        legs[1].current_foot = legs[1].rest_offset;
        legs[2].current_foot = legs[2].rest_offset;
    }

    SceneNode* get_root()  override { return m_root; }
    SceneNode* get_torso() override { return m_torso; }
    float get_body_height() const override { return 0.08f; }

    void draw(ShaderList& shaders, TextureList& textures, const Matrix_4& mat) override
    {
        m_root->draw(shaders, textures, mat);
    }

private:
    SceneNode *m_root, *m_torso, *head, *eyes,
              *leg_A_D_1, *leg_A_D_2,
              *leg_A_I_1, *leg_A_I_2,
              *leg_D_D_1, *leg_D_D_2,
              *leg_D_I_1, *leg_D_I_2,
              *tail_1, *tail_2, *tail_3;

    Color    green, black;
    Material skin_material, eye_material;
};

#endif