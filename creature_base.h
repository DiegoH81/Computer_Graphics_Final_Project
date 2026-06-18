#ifndef CREATURE_BASE_H
#define CREATURE_BASE_H

#include "leg_controller.h"
#include "matrix.h"
#include "scene.h"
#include "surface.h"
#include "vector.h"
#include <algorithm>
#include <cmath>

template <int N> class CreatureBase
{
  public:
    LegController legs[N];

    CreatureBase() {}

    virtual ~CreatureBase() {}

    virtual SceneNode* get_root() = 0;

    virtual SceneNode* get_torso() = 0;

    virtual void draw(ShaderList& shaders, TextureList& textures, const Matrix_4& mat) = 0;

    void update(float dt, const SurfaceFunction& surface)
    {
        SceneNode* root_node = get_root();
        SceneNode* torso_node = get_torso();

        torso_node->parent_transform = root_node->parent_transform * root_node->public_transform;

        for (int i = 0; i < N; i++)
        {
            legs[i].update(dt, torso_node->parent_transform, surface);
        }

        align_torso_to_surface(surface);
    }

    void move(const Vector3& local_delta, const SurfaceFunction* surface = nullptr)
    {
        SceneNode* root = get_root();
        Matrix_4& M = root->public_transform;

        Vector3 world_delta(
            M.matrix[0] * local_delta.x + M.matrix[1] * local_delta.y + M.matrix[2] * local_delta.z,
            M.matrix[4] * local_delta.x + M.matrix[5] * local_delta.y + M.matrix[6] * local_delta.z,
            M.matrix[8] * local_delta.x + M.matrix[9] * local_delta.y +
                M.matrix[10] * local_delta.z);

        root->traslate(world_delta, true);

        if (surface)
        {
            Vector3 t = root->public_transform.get_translation();
            SurfaceHit hit = surface->project(t.x, t.z);
            float snapped_y = hit.position.y + get_body_height();

            root->public_transform.set_translation_y(snapped_y);
            root->private_transform.set_translation_y(snapped_y);
        }
    }

    void wander(float dt, const SurfaceFunction& surface, float speed = 0.75f,
                float rotation_speed = 60.0f)
    {
        move(Vector3(0.0f, 0.0f, dt * speed), &surface);
        update(dt, surface);
    }

    void rotate(float angle_deg)
    {
        get_root()->rotate_y_local(angle_deg, true);
    }

    void align_torso_to_surface(const SurfaceFunction& surface)
    {
        SceneNode* root_node = get_root();
        SceneNode* torso_node = get_torso();

        Vector3 avg_normal(0, 0, 0);
        float avg_y = 0.0f;

        for (int i = 0; i < N; i++)
        {
            SurfaceHit hit = surface.project(legs[i].current_foot);
            avg_normal = avg_normal + hit.normal;
        }
        avg_normal = normalize(avg_normal);

        for (int i = 0; i < N; i++)
        {
            avg_y += legs[i].current_foot.y;
        }
        avg_y /= (float)N;

        Vector3 up(0, 1, 0);
        Vector3 axis = cross(up, avg_normal);
        float axis_len = vec_length(axis);

        Matrix_4 R;
        if (axis_len > 0.001f)
        {
            axis = normalize(axis);
            float cos_a = dot_product(up, avg_normal);
            cos_a = std::max(-1.0f, std::min(1.0f, cos_a));

            R.rotate_axis(axis, std::acos(cos_a));
        }

        torso_node->set_full_transform(R);

        float body_height = get_body_height();

        root_node->public_transform.set_translation_y(avg_y + body_height);
        root_node->private_transform.set_translation_y(avg_y + body_height);
    }

    virtual float get_body_height() const
    {
        return 0.08f;
    }
};

#endif