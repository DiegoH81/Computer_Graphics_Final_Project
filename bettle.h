#ifndef BETTLE_H
#define BETTLE_H

#include <filesystem>
#include "scene.h"
#include "shape.h"
#include "material.h"
#include "creature_base.h"

class Bettle : public CreatureBase<6>
{
public:
    Bettle(std::filesystem::path in_current_path) :
    gold(255, 200, 50, true),
    material_skin()
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

        Mesh3D* head_mesh = make("bettle_head.obj");
        Mesh3D* body_mesh = make("bettle_body.obj");
        Mesh3D* li_f1 = make("bettle_leg_front1.obj");
        Mesh3D* li_f2 = make("bettle_leg_front2.obj");
        Mesh3D* li_f3 = make("bettle_leg_front3.obj");
        Mesh3D* li_m1 = make("bettle_leg_middle1.obj");
        Mesh3D* li_m2 = make("bettle_leg_middle2.obj");
        Mesh3D* li_m3 = make("bettle_leg_middle3.obj");
        Mesh3D* li_b1 = make("bettle_leg_behind1.obj");
        Mesh3D* li_b2 = make("bettle_leg_behind2.obj");
        Mesh3D* li_b3 = make("bettle_leg_behind3.obj");
        Mesh3D* ld_f1 = make("bettle_leg_front1_L.obj");
        Mesh3D* ld_f2 = make("bettle_leg_front2_L.obj");
        Mesh3D* ld_f3 = make("bettle_leg_front3_L.obj");
        Mesh3D* ld_m1 = make("bettle_leg_middle1_L.obj");
        Mesh3D* ld_m2 = make("bettle_leg_middle2_L.obj");
        Mesh3D* ld_m3 = make("bettle_leg_middle3_L.obj");
        Mesh3D* ld_b1 = make("bettle_leg_behind1_L.obj");
        Mesh3D* ld_b2 = make("bettle_leg_behind2_L.obj");
        Mesh3D* ld_b3 = make("bettle_leg_behind3_L.obj");

        m_root = new SceneNode(0);
        m_body = new SceneNode(2, body_mesh);
        m_head = new SceneNode(1, head_mesh);

        m_head->traslate(Vector3(0.0f, 0.0f, 0.2f), true);

        n_li_f1 = new SceneNode(3, li_f1); n_li_f1->traslate(Vector3(-0.01f, 0.0f, 0.23f), true);
        n_li_f2 = new SceneNode(4, li_f2); n_li_f2->traslate(Vector3(-0.15f, 0.0f, 0.07f), true);
        n_li_f3 = new SceneNode(5, li_f3); n_li_f3->traslate(Vector3(-0.09f, -0.04f, 0.187f), true);
        n_li_m1 = new SceneNode(6, li_m1); n_li_m1->traslate(Vector3(-0.055f, 0.0f, 0.19f), true);
        n_li_m2 = new SceneNode(7, li_m2); n_li_m2->traslate(Vector3(-0.15f, 0.0f, 0.0f), true);
        n_li_m3 = new SceneNode(8, li_m3); n_li_m3->traslate(Vector3(-0.172f, 0.04f, -0.18f), true);
        n_li_b1 = new SceneNode(9, li_b1); n_li_b1->traslate(Vector3(-0.065f, 0.0f, 0.030f), true);
        n_li_b2 = new SceneNode(10, li_b2); n_li_b2->traslate(Vector3(-0.13f, 0.0f, -0.075f), true);
        n_li_b3 = new SceneNode(11, li_b3); n_li_b3->traslate(Vector3(-0.08f, -0.015f, -0.19f), true);

        n_ld_f1 = new SceneNode(15, ld_f1); n_ld_f1->traslate(Vector3(0.06f, 0.0f, 0.23f), true);
        n_ld_f2 = new SceneNode(16, ld_f2); n_ld_f2->traslate(Vector3(0.15f, 0.0f, 0.07f), true);
        n_ld_f3 = new SceneNode(17, ld_f3); n_ld_f3->traslate(Vector3(0.09f, -0.04f, 0.187f), true);
        n_ld_m1 = new SceneNode(18, ld_m1); n_ld_m1->traslate(Vector3(0.1f, 0.0f, 0.19f), true);
        n_ld_m2 = new SceneNode(19, ld_m2); n_ld_m2->traslate(Vector3(0.15f, 0.0f, 0.0f), true);
        n_ld_m3 = new SceneNode(20, ld_m3); n_ld_m3->traslate(Vector3(0.172f, 0.04f, -0.18f), true);
        n_ld_b1 = new SceneNode(21, ld_b1); n_ld_b1->traslate(Vector3(0.1f, 0.0f, 0.030f), true);
        n_ld_b2 = new SceneNode(22, ld_b2); n_ld_b2->traslate(Vector3(0.13f, 0.0f, -0.075f), true);
        n_ld_b3 = new SceneNode(23, ld_b3); n_ld_b3->traslate(Vector3(0.08f, -0.015f, -0.19f), true);

        m_root->add_children(m_body);
        m_body->add_children(m_head);
        m_body->add_children(n_li_f1); n_li_f1->add_children(n_li_f2); n_li_f2->add_children(n_li_f3);
        m_body->add_children(n_li_m1); n_li_m1->add_children(n_li_m2); n_li_m2->add_children(n_li_m3);
        m_body->add_children(n_li_b1); n_li_b1->add_children(n_li_b2); n_li_b2->add_children(n_li_b3);
        m_body->add_children(n_ld_f1); n_ld_f1->add_children(n_ld_f2); n_ld_f2->add_children(n_ld_f3);
        m_body->add_children(n_ld_m1); n_ld_m1->add_children(n_ld_m2); n_ld_m2->add_children(n_ld_m3);
        m_body->add_children(n_ld_b1); n_ld_b1->add_children(n_ld_b2); n_ld_b2->add_children(n_ld_b3);

        const std::vector<float> lens_front = { 0.186f, 0.219f, 0.171f };
        const std::vector<float> lens_middle = { 0.158f, 0.262f, 0.184f };
        const std::vector<float> lens_behind = { 0.183f, 0.204f, 0.158f };

        const float anchor_x_izq = -0.150f;
        const float anchor_x_der = 0.200f;
        const float anchor_y_sp = -0.108f;
        const float rest_y_sp = -0.148f;
        const float step_r = 0.1;
        const float anchor_zs[3] = { 0.230f, 0.000f, -0.200f };

        legs[0].init({ n_li_f1, n_li_f2, n_li_f3 }, lens_front, Vector3(-0.496f, rest_y_sp, anchor_zs[0]), Vector3(anchor_x_izq, anchor_y_sp, anchor_zs[0]));
        legs[0].yaw_offset = PI * 0.5f;
        legs[0].step_range = step_r;

        legs[1].init({ n_li_m1, n_li_m2, n_li_m3 }, lens_middle, Vector3(-0.513f, rest_y_sp, anchor_zs[1]), Vector3(anchor_x_izq, anchor_y_sp, anchor_zs[1]));
        legs[1].yaw_offset = PI * 0.5f;
        legs[1].step_range = step_r;

        legs[2].init({ n_li_b1, n_li_b2, n_li_b3 }, lens_behind, Vector3(-0.477f, rest_y_sp, anchor_zs[2]), Vector3(anchor_x_izq, anchor_y_sp, anchor_zs[2]));
        legs[2].yaw_offset = PI * 0.6f;
        legs[2].step_range = step_r;

        legs[3].init({ n_ld_f1, n_ld_f2, n_ld_f3 }, lens_front, Vector3(0.546f, rest_y_sp, anchor_zs[0]), Vector3(anchor_x_der, anchor_y_sp, anchor_zs[0]));
        legs[3].yaw_offset = -PI * 0.5f;
        legs[3].step_range = step_r;

        legs[4].init({ n_ld_m1, n_ld_m2, n_ld_m3 }, lens_middle, Vector3(0.563f, rest_y_sp, anchor_zs[1]), Vector3(anchor_x_der, anchor_y_sp, anchor_zs[1]));
        legs[4].yaw_offset = -PI * 0.5f;
        legs[4].step_range = step_r;

        legs[5].init({ n_ld_b1, n_ld_b2, n_ld_b3 }, lens_behind, Vector3(0.527f, rest_y_sp, anchor_zs[2]), Vector3(anchor_x_der, anchor_y_sp, anchor_zs[2]));
        legs[5].yaw_offset = -PI * 0.6f;
        legs[5].step_range = step_r;

        legs[0].diagonal_pair = &legs[4]; legs[4].diagonal_pair = &legs[0];
        legs[2].diagonal_pair = &legs[3]; legs[3].diagonal_pair = &legs[2];
        legs[1].diagonal_pair = &legs[5]; legs[5].diagonal_pair = &legs[1];

        legs[0].current_foot = legs[0].rest_offset + Vector3(0.12f, 0.0f, 0.0f);
        legs[4].current_foot = legs[4].rest_offset + Vector3(-0.12f, 0.0f, 0.0f);
        legs[2].current_foot = legs[2].rest_offset + Vector3(0.12f, 0.0f, 0.0f);
        legs[1].current_foot = legs[1].rest_offset;
        legs[3].current_foot = legs[3].rest_offset;
        legs[5].current_foot = legs[5].rest_offset;
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

    SceneNode *n_li_f1, *n_li_f2, *n_li_f3;
    SceneNode *n_li_m1, *n_li_m2, *n_li_m3;
    SceneNode *n_li_b1, *n_li_b2, *n_li_b3;

    SceneNode *n_ld_f1, *n_ld_f2, *n_ld_f3;
    SceneNode *n_ld_m1, *n_ld_m2, *n_ld_m3;
    SceneNode *n_ld_b1, *n_ld_b2, *n_ld_b3;

    Color gold;
    Material material_skin;
};

#endif