#ifndef BETTLE_H
#define BETTLE_H

#include "creature_base.h"
#include "material.h"
#include "scene.h"
#include "shape.h"
#include <filesystem>

class Bettle : public CreatureBase<6>
{
  public:
    Bettle(std::filesystem::path in_current_path) : gold(255, 200, 50, true), material_skin()
    {
        material_skin.ambient = Vector3(0.15f, 0.10f, 0.00f);
        material_skin.diffuse = Vector3(0.60f, 0.50f, 0.10f);
        material_skin.specular = Vector3(0.90f, 0.80f, 0.40f);
        material_skin.shininess = 100.0f;

        in_current_path = in_current_path / "models" / "bettle";

        auto make = [&](const char* file) -> Mesh3D*
        {
            Mesh3D* m = new Mesh3D(in_current_path, file);
            m->add_faces(&gold);
            m->set_material(&material_skin);
            return m;
        };

        const char* izq_files[3][3] = {
            {"bettle_leg_front1.obj", "bettle_leg_front2.obj", "bettle_leg_front3.obj"},
            {"bettle_leg_middle1.obj", "bettle_leg_middle2.obj", "bettle_leg_middle3.obj"},
            {"bettle_leg_behind1.obj", "bettle_leg_behind2.obj", "bettle_leg_behind3.obj"},
        };
        const char* der_files[3][3] = {
            {"bettle_leg_front1_L.obj", "bettle_leg_front2_L.obj", "bettle_leg_front3_L.obj"},
            {"bettle_leg_middle1_L.obj", "bettle_leg_middle2_L.obj", "bettle_leg_middle3_L.obj"},
            {"bettle_leg_behind1_L.obj", "bettle_leg_behind2_L.obj", "bettle_leg_behind3_L.obj"},
        };

        const Vector3 izq_offsets[3][3] = {
            {{-0.010f, 0.000f, 0.230f}, {-0.150f, 0.000f, 0.070f}, {-0.090f, -0.040f, 0.187f}},
            {{-0.055f, 0.000f, 0.190f}, {-0.150f, 0.000f, 0.000f}, {-0.172f, 0.040f, -0.180f}},
            {{-0.065f, 0.000f, 0.030f}, {-0.130f, 0.000f, -0.075f}, {-0.080f, -0.015f, -0.190f}},
        };
        const Vector3 der_offsets[3][3] = {
            {{0.060f, 0.000f, 0.230f}, {0.150f, 0.000f, 0.070f}, {0.090f, -0.040f, 0.187f}},
            {{0.100f, 0.000f, 0.190f}, {0.150f, 0.000f, 0.000f}, {0.172f, 0.040f, -0.180f}},
            {{0.100f, 0.000f, 0.030f}, {0.130f, 0.000f, -0.075f}, {0.080f, -0.015f, -0.190f}},
        };

        m_root = new SceneNode(0);
        m_body = new SceneNode(2, make("bettle_body.obj"));
        m_head = new SceneNode(1, make("bettle_head.obj"));
        m_head->traslate(Vector3(0.0f, 0.0f, 0.2f), true);

        int node_id = 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                ni[i][j] = new SceneNode(node_id++, make(izq_files[i][j]));
                ni[i][j]->traslate(izq_offsets[i][j], true);
            }
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                nd[i][j] = new SceneNode(node_id++, make(der_files[i][j]));
                nd[i][j]->traslate(der_offsets[i][j], true);
            }

        m_root->add_children(m_body);
        m_body->add_children(m_head);

        for (int i = 0; i < 3; i++)
        {
            m_body->add_children(ni[i][0]);
            ni[i][0]->add_children(ni[i][1]);
            ni[i][1]->add_children(ni[i][2]);

            m_body->add_children(nd[i][0]);
            nd[i][0]->add_children(nd[i][1]);
            nd[i][1]->add_children(nd[i][2]);
        }

        const std::vector<float> lens[3] = {
            {0.186f, 0.219f, 0.171f},
            {0.158f, 0.262f, 0.184f},
            {0.183f, 0.204f, 0.158f},
        };

        const float anchor_x_izq = 0.090f;
        const float anchor_x_der = -0.090f;
        const float anchor_y_sp = -0.015f;
        const float rest_x_izq = -0.95f;
        const float rest_x_der = 0.95f;
        const float rest_y_sp = -0.060f;
        const float step_r = 0.955f;
        const float yaw_base = 1.051f;
        const float yaw_step = 0.698f;
        const float yaw_izq[4] = {yaw_base, yaw_base + yaw_step, yaw_base + yaw_step * 2.0f,
                                  yaw_base + yaw_step * 3.0f};

        const float yaw_der[4] = {-yaw_base, -(yaw_base + yaw_step), -(yaw_base + yaw_step * 2.0f),
                                  -(yaw_base + yaw_step * 3.0f)};
        const float anchor_zs[3] = {0.230f, 0.000f, -0.200f};

        for (int i = 0; i < 3; i++)
        {
            float az = anchor_zs[i];

            legs[i].init({ni[i][0], ni[i][1], ni[i][2]}, lens[i],
                         Vector3(rest_x_izq, rest_y_sp, az),
                         Vector3(anchor_x_izq, anchor_y_sp, az));
            legs[i].yaw_offset = yaw_izq[i];
            legs[i].step_range = step_r;

            legs[3 + i].init({nd[i][0], nd[i][1], nd[i][2]}, lens[i],
                             Vector3(rest_x_der, rest_y_sp, az),
                             Vector3(anchor_x_der, anchor_y_sp, az));
            legs[3 + i].yaw_offset = yaw_der[i];
            legs[3 + i].step_range = step_r;
        }

        gait_group_A.members = {&legs[0], &legs[2], &legs[4]};
        gait_group_B.members = {&legs[1], &legs[3], &legs[5]};

        for (auto* l : gait_group_A.members)
            l->gait_group = &gait_group_A;
        for (auto* l : gait_group_B.members)
            l->gait_group = &gait_group_B;

        gait_group_A.current_turn = 0;
        gait_group_B.current_turn = 0;

        for (int i : {0, 2})
            legs[i].current_foot = legs[i].rest_offset + Vector3(0.12f, 0.0f, 0.0f);
        legs[4].current_foot = legs[4].rest_offset + Vector3(-0.12f, 0.0f, 0.0f);
        for (int i : {1, 3, 5})
            legs[i].current_foot = legs[i].rest_offset;
    }

    SceneNode* get_root() override
    {
        return m_root;
    }
    SceneNode* get_torso() override
    {
        return m_body;
    }
    float get_body_height() const override
    {
        return 0.064f;
    }

    void draw(ShaderList& shaders, TextureList& textures, const Matrix_4& mat) override
    {
        m_root->draw(shaders, textures, mat);
    }

  private:
    SceneNode* m_root;
    SceneNode* m_body;
    SceneNode* m_head;

    SceneNode* ni[3][3];
    SceneNode* nd[3][3];

    Color gold;
    Material material_skin;

    LegController::GaitGroup gait_group_A;
    LegController::GaitGroup gait_group_B;
};

#endif