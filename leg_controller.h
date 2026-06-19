#ifndef LEG_CONTROLLER_H
#define LEG_CONTROLLER_H

#include "fabrik.h"
#include "matrix.h"
#include "scene.h"
#include "surface.h"
#include "vector.h"
#include <cmath>
#include <vector>

class LegController
{
  public:
    Vector3 rest_offset;
    Vector3 anchor_offset;
    float step_range = 0.52f;
    float step_speed = 3.0f;
    float step_height = 0.08f;

    float yaw_offset = 0.0f;

    Point3 current_foot;
    Point3 target_foot;
    Point3 start_foot;
    bool is_stepping = false;
    float step_t = 0.0f;
    float step_total_dist = 1.0f;

    LegController* diagonal_pair = nullptr;

    struct GaitGroup
    {
        std::vector<LegController*> members;
        int current_turn = 0;

        bool any_stepping() const
        {
            for (auto* m : members)
            {
                if (m && m->is_stepping)
                {
                    return true;
                }
            }
            return false;
        }

        bool is_my_turn(const LegController* leg) const
        {
            if (members.empty())
            {
                return true;
            }
            return members[current_turn] == leg;
        }

        void advance()
        {
            if (!members.empty())
            {
                current_turn = (current_turn + 1) % (int)members.size();
            }
        }
    };

    GaitGroup* gait_group = nullptr;

    std::vector<SceneNode*> nodes;

    std::vector<Vector3> t_priv_offsets;
    std::vector<Vector3> t_pub_offsets;

    Fabrik fabrik;

    void init(const std::vector<SceneNode*>& in_nodes, const std::vector<float>& in_lengths,
              Vector3 in_rest_offset, Vector3 in_anchor_offset)
    {
        nodes = in_nodes;
        rest_offset = in_rest_offset;
        anchor_offset = in_anchor_offset;
        current_foot = in_rest_offset;

        fabrik.init(in_lengths);

        t_priv_offsets.resize(nodes.size());
        t_pub_offsets.resize(nodes.size());

        for (int i = 0; i < (int)nodes.size(); i++)
        {
            t_priv_offsets[i] = nodes[i]->private_transform.get_translation();
            t_pub_offsets[i] = nodes[i]->public_transform.get_translation();
        }
    }

    void update(float dt, const Matrix_4& torso_world, const SurfaceFunction& surface)
    {
        Vector3 torso_t = torso_world.get_translation();
        Point3 torso_pos(torso_t.x, torso_t.y, torso_t.z);
        Point3 anchor_world = torso_pos + anchor_offset;

        Vector3 torso_vel(0, 0, 0);
        if (has_prev)
        {
            torso_vel.x = (torso_pos.x - prev_torso_pos.x) / dt;
            torso_vel.z = (torso_pos.z - prev_torso_pos.z) / dt;
        }
        prev_torso_pos = torso_pos;
        has_prev = true;

        float lookahead = 0.18f;
        Point3 rest_world(torso_pos.x + rest_offset.x + torso_vel.x * lookahead,
                          torso_pos.y + rest_offset.y,
                          torso_pos.z + rest_offset.z + torso_vel.z * lookahead);

        SurfaceHit rest_hit = surface.project(rest_world);
        Point3 rest_surf = rest_hit.position;

        if (!is_stepping)
        {
            bool blocked = false;
            if (gait_group)
            {
                blocked = gait_group->any_stepping() || !gait_group->is_my_turn(this);
            }
            else if (diagonal_pair)
            {
                blocked = diagonal_pair->is_stepping;
            }

            float dx = current_foot.x - rest_surf.x;
            float dz = current_foot.z - rest_surf.z;
            float d = std::sqrt(dx * dx + dz * dz);
            if (!blocked && d > step_range)
            {
                start_foot = current_foot;
                target_foot = rest_surf;
                step_t = 0.0f;
                step_total_dist = (d < 0.001f) ? 0.001f : d;
                is_stepping = true;
            }
        }

        if (is_stepping)
        {
            float dx = target_foot.x - current_foot.x;
            float dz = target_foot.z - current_foot.z;
            float remaining = std::sqrt(dx * dx + dz * dz);
            float move = step_speed * dt;

            if (move >= remaining)
            {
                current_foot = target_foot;
                is_stepping = false;
                step_t = 1.0f;
                if (gait_group)
                {
                    gait_group->advance();
                }
            }
            else
            {
                float ratio = move / remaining;
                current_foot.x += dx * ratio;
                current_foot.z += dz * ratio;
                step_t += dt * step_speed / step_total_dist;
                step_t = std::min(step_t, 1.0f);
                current_foot.y = start_foot.y + (target_foot.y - start_foot.y) * step_t +
                                 step_height * std::sin(step_t * 3.14159265f);
            }
        }
        else
        {
            SurfaceHit hit = surface.project(current_foot);
            current_foot.y = hit.position.y;
        }

        solve_ik_fabrik(anchor_world, current_foot);
    }

  private:
    Point3 prev_torso_pos;
    bool has_prev = false;

    void solve_ik_fabrik(const Point3& anchor, const Point3& foot)
    {
        if (nodes.empty())
        {
            return;
        }

        fabrik.solve(anchor, foot);

        Vector3 leg_dir = foot - anchor;
        float base_yaw = std::atan2(leg_dir.x, leg_dir.z);
        std::vector<Point3> jp = fabrik.joint_positions;

        for (int i = 0; i < (int)nodes.size(); i++)
        {
            Vector3 from(jp[i].x, jp[i].y, jp[i].z);
            Vector3 to(jp[i + 1].x, jp[i + 1].y, jp[i + 1].z);

            Vector3 dir = to - from;
            float len = vec_length(dir);

            if (len < 0.0001f)
            {
                continue;
            }

            float forward_x = std::sin(base_yaw);
            float forward_z = std::cos(base_yaw);

            float dist_xz = dir.x * forward_x + dir.z * forward_z;

            float pitch = std::atan2(-dir.y, dist_xz);
            float final_yaw = base_yaw + yaw_offset;

            float cy = std::cos(final_yaw);
            float sy = std::sin(final_yaw);
            float cx = std::cos(pitch);
            float sx = std::sin(pitch);

            SceneNode* node = nodes[i];
            const Vector3& t_priv = t_priv_offsets[i];
            const Vector3& t_pub = t_pub_offsets[i];

            node->private_transform.set_matrix({cy, sy * sx, sy * cx, t_priv.x, 0, cx, -sx,
                                                t_priv.y, -sy, cy * sx, cy * cx, t_priv.z, 0, 0, 0,
                                                1});

            if (t_priv.x == t_pub.x && t_priv.y == t_pub.y && t_priv.z == t_pub.z)
            {
                node->public_transform = node->private_transform;
            }
            else
            {
                node->public_transform.set_matrix({cy, sy * sx, sy * cx, t_pub.x, 0, cx, -sx,
                                                   t_pub.y, -sy, cy * sx, cy * cx, t_pub.z, 0, 0, 0,
                                                   1});
            }
        }
    }
};

#endif