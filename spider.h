#ifndef SPIDER_H
#define SPIDER_H

#include "creature_base.h"
#include "material.h"
#include "scene.h"
#include "shape.h"
#include <filesystem>

class Spider : public CreatureBase<8>
{
  public:
    Spider(std::filesystem::path in_current_path) : gray(128, 128, 128, true), material_skin()
    {
        material_skin.ambient = Vector3(0.10f, 0.0f, 0.15f);
        material_skin.diffuse = Vector3(0.45f, 0.20f, 0.14f);
        material_skin.specular = Vector3(0.7f, 0.4f, 0.3f);
        material_skin.shininess = 80.0f;

        in_current_path = in_current_path / "models" / "spider";

        auto makeL = [&](const char* file) -> Mesh3D*
        {
            Mesh3D* m = new Mesh3D(in_current_path, file);
            m->add_faces(&gray);
            m->set_material(&material_skin);
            return m;
        };
        auto makeR = makeL;

        Mesh3D* torso_mesh = makeL("spider_torso.obj");
        Mesh3D* back_mesh = makeL("spider_back.obj");

        Mesh3D* li1_1 = makeL("spider_leg1_L.obj");
        Mesh3D* li1_2 = makeL("spider_leg2_L.obj");
        Mesh3D* li1_3 = makeL("spider_leg3_L.obj");
        Mesh3D* li2_1 = makeL("spider_leg1_L.obj");
        Mesh3D* li2_2 = makeL("spider_leg2_L.obj");
        Mesh3D* li2_3 = makeL("spider_leg3_L.obj");
        Mesh3D* li3_1 = makeL("spider_leg1_L.obj");
        Mesh3D* li3_2 = makeL("spider_leg2_L.obj");
        Mesh3D* li3_3 = makeL("spider_leg3_L.obj");
        Mesh3D* li4_1 = makeL("spider_leg1_L.obj");
        Mesh3D* li4_2 = makeL("spider_leg2_L.obj");
        Mesh3D* li4_3 = makeL("spider_leg3_L.obj");

        Mesh3D* ld1_1 = makeR("spider_leg1_R.obj");
        Mesh3D* ld1_2 = makeR("spider_leg2_R.obj");
        Mesh3D* ld1_3 = makeR("spider_leg3_R.obj");
        Mesh3D* ld2_1 = makeR("spider_leg1_R.obj");
        Mesh3D* ld2_2 = makeR("spider_leg2_R.obj");
        Mesh3D* ld2_3 = makeR("spider_leg3_R.obj");
        Mesh3D* ld3_1 = makeR("spider_leg1_R.obj");
        Mesh3D* ld3_2 = makeR("spider_leg2_R.obj");
        Mesh3D* ld3_3 = makeR("spider_leg3_R.obj");
        Mesh3D* ld4_1 = makeR("spider_leg1_R.obj");
        Mesh3D* ld4_2 = makeR("spider_leg2_R.obj");
        Mesh3D* ld4_3 = makeR("spider_leg3_R.obj");

        m_root = new SceneNode(0);
        m_torso = new SceneNode(1, torso_mesh);
        m_back = new SceneNode(2, back_mesh);

        ni[0][0] = new SceneNode(3, li1_1);
        ni[0][0]->traslate(Vector3(0.08f, 0.01f, 0.10f), true);
        ni[0][1] = new SceneNode(4, li1_2);
        ni[0][1]->traslate(Vector3(0.087f, 0.2f, 0.145f), true);
        ni[0][2] = new SceneNode(5, li1_3);
        ni[0][2]->traslate(Vector3(0.079f, -0.07f, 0.21f), true);

        ni[1][0] = new SceneNode(6, li2_1);
        ni[1][0]->traslate(Vector3(0.08f, 0.01f, 0.065f), true);
        ni[1][0]->rotate_y_local(40.0f, true);
        ni[1][1] = new SceneNode(7, li2_2);
        ni[1][1]->traslate(Vector3(0.087f, 0.2f, 0.145f), true);
        ni[1][2] = new SceneNode(8, li2_3);
        ni[1][2]->traslate(Vector3(0.079f, -0.07f, 0.21f), true);

        ni[2][0] = new SceneNode(9, li3_1);
        ni[2][0]->traslate(Vector3(0.08f, 0.01f, 0.030f), true);
        ni[2][0]->rotate_y_local(80.0f, true);
        ni[2][1] = new SceneNode(10, li3_2);
        ni[2][1]->traslate(Vector3(0.087f, 0.2f, 0.145f), true);
        ni[2][2] = new SceneNode(11, li3_3);
        ni[2][2]->traslate(Vector3(0.079f, -0.07f, 0.21f), true);

        ni[3][0] = new SceneNode(12, li4_1);
        ni[3][0]->traslate(Vector3(0.08f, 0.01f, -0.005f), true);
        ni[3][0]->rotate_y_local(120.0f, true);
        ni[3][1] = new SceneNode(13, li4_2);
        ni[3][1]->traslate(Vector3(0.087f, 0.2f, 0.145f), true);
        ni[3][2] = new SceneNode(14, li4_3);
        ni[3][2]->traslate(Vector3(0.079f, -0.07f, 0.21f), true);

        nd[0][0] = new SceneNode(15, ld1_1);
        nd[0][0]->traslate(Vector3(-0.082f, 0.01f, 0.10f), true);
        nd[0][1] = new SceneNode(16, ld1_2);
        nd[0][1]->traslate(Vector3(-0.067f, 0.2f, 0.135f), true);
        nd[0][2] = new SceneNode(17, ld1_3);
        nd[0][2]->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        nd[1][0] = new SceneNode(18, ld2_1);
        nd[1][0]->traslate(Vector3(-0.082f, 0.01f, 0.065f), true);
        nd[1][0]->rotate_y_local(-40.0f, true);
        nd[1][1] = new SceneNode(19, ld2_2);
        nd[1][1]->traslate(Vector3(-0.067f, 0.2f, 0.135f), true);
        nd[1][2] = new SceneNode(20, ld2_3);
        nd[1][2]->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        nd[2][0] = new SceneNode(21, ld3_1);
        nd[2][0]->traslate(Vector3(-0.082f, 0.01f, 0.030f), true);
        nd[2][0]->rotate_y_local(-80.0f, true);
        nd[2][1] = new SceneNode(22, ld3_2);
        nd[2][1]->traslate(Vector3(-0.067f, 0.2f, 0.135f), true);
        nd[2][2] = new SceneNode(23, ld3_3);
        nd[2][2]->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        nd[3][0] = new SceneNode(24, ld4_1);
        nd[3][0]->traslate(Vector3(-0.082f, 0.01f, -0.005f), true);
        nd[3][0]->rotate_y_local(-120.0f, true);
        nd[3][1] = new SceneNode(25, ld4_2);
        nd[3][1]->traslate(Vector3(-0.067f, 0.2f, 0.135f), true);
        nd[3][2] = new SceneNode(26, ld4_3);
        nd[3][2]->traslate(Vector3(-0.092f, -0.075f, 0.205f), true);

        m_root->add_children(m_torso);
        m_torso->add_children(m_back);

        for (int i = 0; i < 4; i++)
        {
            m_torso->add_children(ni[i][0]);
            ni[i][0]->add_children(ni[i][1]);
            ni[i][1]->add_children(ni[i][2]);

            m_torso->add_children(nd[i][0]);
            nd[i][0]->add_children(nd[i][1]);
            nd[i][1]->add_children(nd[i][2]);
        }

        const std::vector<float> lens = {0.185f, 0.207f, 0.110f};

        const float anchor_x_izq = 0.090f;
        const float anchor_x_der = -0.090f;
        const float anchor_y_sp = -0.015f;
        const float rest_x_izq = -0.95f;
        const float rest_x_der = 0.95f;
        const float rest_y_sp = -0.060f;
        const float step_r = 0.1f;

        const float anchor_zs[4] = {0.155f, 0.110f, 0.065f, 0.020f};

        const float yaw_base = 1.051f;
        const float yaw_step = 0.698f;
        const float yaw_izq[4] = {yaw_base, yaw_base + yaw_step, yaw_base + yaw_step * 2.0f,
                                  yaw_base + yaw_step * 3.0f};
        const float yaw_der[4] = {-yaw_base, -(yaw_base + yaw_step), -(yaw_base + yaw_step * 2.0f),
                                  -(yaw_base + yaw_step * 3.0f)};

        SceneNode*(*izq_nodes)[3] = ni;
        SceneNode*(*der_nodes)[3] = nd;

        for (int i = 0; i < 4; i++)
        {
            float az = anchor_zs[i];

            legs[i].init({izq_nodes[i][0], izq_nodes[i][1], izq_nodes[i][2]}, lens,
                         Vector3(rest_x_izq, rest_y_sp, az),
                         Vector3(anchor_x_izq, anchor_y_sp, az));
            legs[i].yaw_offset = yaw_izq[i];
            legs[i].step_range = step_r;

            legs[4 + i].init({der_nodes[i][0], der_nodes[i][1], der_nodes[i][2]}, lens,
                             Vector3(rest_x_der, rest_y_sp, az),
                             Vector3(anchor_x_der, anchor_y_sp, az));
            legs[4 + i].yaw_offset = yaw_der[i];
            legs[4 + i].step_range = step_r;
        }

        gait_group_A.members = {&legs[0], &legs[2], &legs[5], &legs[7]};
        gait_group_B.members = {&legs[1], &legs[3], &legs[4], &legs[6]};

        for (auto* l : gait_group_A.members)
        {
            l->gait_group = &gait_group_A;
        }
        for (auto* l : gait_group_B.members)
        {
            l->gait_group = &gait_group_B;
        }

        gait_group_A.current_turn = 0;
        gait_group_B.current_turn = 0;

        for (int i : {0, 2, 5, 7})
        {
            legs[i].current_foot = legs[i].rest_offset + Vector3(0.0f, 0.0f, -0.04f);
        }
    }

    SceneNode* get_root() override
    {
        return m_root;
    }
    SceneNode* get_torso() override
    {
        return m_torso;
    }
    float get_body_height() const override
    {
        return 0.060f;
    }

    void draw(ShaderList& shaders, TextureList& textures, const Matrix_4& mat) override
    {
        m_root->draw(shaders, textures, mat);
    }

  private:
    SceneNode* m_root;
    SceneNode* m_torso;
    SceneNode* m_back;
    SceneNode* ni[4][3];
    SceneNode* nd[4][3];

    Color gray;
    Material material_skin;

    LegController::GaitGroup gait_group_A;
    LegController::GaitGroup gait_group_B;
};

#endif