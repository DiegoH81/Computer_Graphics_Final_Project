#ifndef LEG_CONTROLLER_H
#define LEG_CONTROLLER_H

#include "scene.h"
#include "surface.h"
#include "vector.h"
#include "matrix.h"
#include "fabrik.h"
#include <vector>
#include <cmath>

inline Point3 extract_world_pos(const Matrix_4& m)
{
    return Point3(m.matrix[3], m.matrix[7], m.matrix[11]);
}

inline Matrix_4 make_rotation_to_dir(const Vector3& dir, float yaw_offset)
{
    float yaw = std::atan2(dir.x, dir.z) + yaw_offset;
    float pitch = std::atan2(-dir.y, std::sqrt(dir.x * dir.x + dir.z * dir.z));

    float cy = std::cos(yaw);
    float sy = std::sin(yaw);
    float cx = std::cos(pitch);
    float sx = std::sin(pitch);

    Matrix_4 R;
    R.set_matrix({
        cy, sy * sx, sy * cx, 0,
        0, cx, -sx, 0,
        -sy, cy * sx, cy * cx, 0,
        0, 0, 0, 1
    });
    return R;
}

inline void write_segment_transform(SceneNode* node,
                                    const Vector3& t_priv,
                                    const Vector3& t_pub,
                                    const Vector3& from,
                                    const Vector3& to,
                                    float yaw_offset = 0.0f)
{
    Vector3 dir = to - from;
    float len = vec_length(dir);
    if (len < 0.0001f)
    {
        return;
    }

    float yaw = std::atan2(dir.x, dir.z) + yaw_offset;
    float pitch = std::atan2(-dir.y, std::sqrt(dir.x * dir.x + dir.z * dir.z));

    float cy = std::cos(yaw);
    float sy = std::sin(yaw);
    float cx = std::cos(pitch);
    float sx = std::sin(pitch);

    node->private_transform.set_matrix({
        cy, sy * sx, sy * cx, t_priv.x,
        0, cx, -sx, t_priv.y,
        -sy, cy * sx, cy * cx, t_priv.z,
        0, 0, 0, 1
    });
    node->public_transform.set_matrix({
        cy, sy * sx, sy * cx, t_pub.x,
        0, cx, -sx, t_pub.y,
        -sy, cy * sx, cy * cx, t_pub.z,
        0, 0, 0, 1
    });
}

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

    FABRIKSolver fabrik;

    bool use_analytic_2bone = false;
    float thigh_len = 0.15f;
    float shin_len = 0.12f;

    LegController()
    {
    }

    void init(const std::vector<SceneNode*>& in_nodes,
              const std::vector<float>& in_lengths,
              Vector3 in_rest_offset,
              Vector3 in_anchor_offset)
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
            t_priv_offsets[i] = {
                nodes[i]->private_transform.matrix[3],
                nodes[i]->private_transform.matrix[7],
                nodes[i]->private_transform.matrix[11]
            };
            t_pub_offsets[i] = {
                nodes[i]->public_transform.matrix[3],
                nodes[i]->public_transform.matrix[7],
                nodes[i]->public_transform.matrix[11]
            };
        }
    }

    void init(SceneNode* in_thigh,
              SceneNode* in_shin,
              Vector3 in_rest_offset,
              Vector3 in_anchor_offset,
              float in_thigh_len,
              float in_shin_len)
    {
        use_analytic_2bone = true;
        thigh_len = in_thigh_len;
        shin_len = in_shin_len;

        nodes = { in_thigh, in_shin };
        rest_offset = in_rest_offset;
        anchor_offset = in_anchor_offset;
        current_foot = in_rest_offset;

        t_priv_offsets.resize(2);
        t_pub_offsets.resize(2);

        for (int i = 0; i < 2; i++)
        {
            t_priv_offsets[i] = {
                nodes[i]->private_transform.matrix[3],
                nodes[i]->private_transform.matrix[7],
                nodes[i]->private_transform.matrix[11]
            };
            t_pub_offsets[i] = {
                nodes[i]->public_transform.matrix[3],
                nodes[i]->public_transform.matrix[7],
                nodes[i]->public_transform.matrix[11]
            };
        }
    }

    void update(float dt, const Matrix_4& torso_world, const SurfaceFunction& surface)
    {
        Point3 torso_pos = extract_world_pos(torso_world);
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
        Point3 rest_world(
            torso_pos.x + rest_offset.x + torso_vel.x * lookahead,
            torso_pos.y + rest_offset.y,
            torso_pos.z + rest_offset.z + torso_vel.z * lookahead
        );

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
                current_foot.y = start_foot.y
                               + (target_foot.y - start_foot.y) * step_t
                               + step_height * std::sin(step_t * 3.14159265f);
            }
        }
        else
        {
            SurfaceHit hit = surface.project(current_foot);
            current_foot.y = hit.position.y;
        }

        if (use_analytic_2bone)
        {
            solve_ik_2bone(anchor_world, current_foot);
        }
        else
        {
            solve_ik_fabrik(anchor_world, current_foot);
        }
    }

private:
    Point3 prev_torso_pos;
    bool has_prev = false;

    inline void write_segment_transform_fixed_yaw(SceneNode* node,
                                              const Vector3& t_priv,
                                              const Vector3& t_pub,
                                              const Vector3& from,
                                              const Vector3& to,
                                              float base_yaw,
                                              float yaw_offset = 0.0f)
    {
        Vector3 dir = to - from;
        float len = vec_length(dir);
        if (len < 0.0001f)
        {
            return;
        }

        // Calcular el vector de dirección frontal en el plano XZ basado en el yaw
        float forward_x = std::sin(base_yaw);
        float forward_z = std::cos(base_yaw);
        
        // Proyectar la dirección del hueso sobre este vector frontal.
        // Esto da una distancia firmada que permite que la rodilla se doble sin retorcerse.
        float dist_xz = dir.x * forward_x + dir.z * forward_z;
        
        float pitch = std::atan2(-dir.y, dist_xz);
        float final_yaw = base_yaw + yaw_offset;

        float cy = std::cos(final_yaw);
        float sy = std::sin(final_yaw);
        float cx = std::cos(pitch);
        float sx = std::sin(pitch);

        node->private_transform.set_matrix({
            cy, sy * sx, sy * cx, t_priv.x,
            0, cx, -sx, t_priv.y,
            -sy, cy * sx, cy * cx, t_priv.z,
            0, 0, 0, 1
        });
        node->public_transform.set_matrix({
            cy, sy * sx, sy * cx, t_pub.x,
            0, cx, -sx, t_pub.y,
            -sy, cy * sx, cy * cx, t_pub.z,
            0, 0, 0, 1
        });
    }

    void solve_ik_2bone(const Point3& anchor, const Point3& foot)
    {
        Vector3 dir = foot - anchor;
        float dist = vec_length(dir);

        float max_reach = thigh_len + shin_len - 0.001f;
        if (dist > max_reach)
        {
            dist = max_reach;
        }
        if (dist < 0.001f)
        {
            dist = 0.001f;
        }

        float L1 = thigh_len;
        float L2 = shin_len;

        float cos_knee = (L1 * L1 + L2 * L2 - dist * dist) / (2.0f * L1 * L2);
        cos_knee = std::max(-1.0f, std::min(1.0f, cos_knee));
        float knee_rad = std::acos(cos_knee);

        float cos_hip = (L1 * L1 + dist * dist - L2 * L2) / (2.0f * L1 * dist);
        cos_hip = std::max(-1.0f, std::min(1.0f, cos_hip));
        float hip_rad = std::acos(cos_hip);

        float yaw = std::atan2(dir.x, dir.z) + yaw_offset;
        float pitch = std::atan2(-dir.y, std::sqrt(dir.x * dir.x + dir.z * dir.z));

        float ry = yaw;
        float rx = pitch + hip_rad;
        float cy = std::cos(ry);
        float sy = std::sin(ry);
        float cx = std::cos(rx);
        float sx = std::sin(rx);

        auto write = [&](SceneNode* node, const Vector3& tp, const Vector3& tpu,
                         float r00, float r01, float r02,
                         float r10, float r11, float r12,
                         float r20, float r21, float r22) {
            node->private_transform.set_matrix({ r00, r01, r02, tp.x, r10, r11, r12, tp.y, r20, r21, r22, tp.z, 0, 0, 0, 1 });
            node->public_transform.set_matrix({ r00, r01, r02, tpu.x, r10, r11, r12, tpu.y, r20, r21, r22, tpu.z, 0, 0, 0, 1 });
        };

        write(nodes[0], t_priv_offsets[0], t_pub_offsets[0],
              cy, sy * sx, sy * cx,
              0, cx, -sx,
              -sy, cy * sx, cy * cx);

        float rk = knee_rad - 3.14159265f;
        float ck = std::cos(rk);
        float sk = std::sin(rk);

        write(nodes[1], t_priv_offsets[1], t_pub_offsets[1],
              1, 0, 0,
              0, ck, -sk,
              0, sk, ck);
    }

    void solve_ik_fabrik(const Point3& anchor, const Point3& foot)
    {
        if (nodes.empty())
        {
            return;
        }

        fabrik.solve(anchor, foot);

        // NUEVO: Calcular el yaw base para TODA la pierna, igual que en el 2-bone IK
        Vector3 leg_dir = foot - anchor;
        float base_yaw = std::atan2(leg_dir.x, leg_dir.z);

        const auto& jp = fabrik.joint_positions;
        for (int i = 0; i < (int)nodes.size(); i++)
        {
            Vector3 from(jp[i].x, jp[i].y, jp[i].z);
            Vector3 to(jp[i + 1].x, jp[i + 1].y, jp[i + 1].z);

            // NUEVO: Usar la función con el yaw bloqueado
            write_segment_transform_fixed_yaw(nodes[i],
                                            t_priv_offsets[i], t_pub_offsets[i],
                                            from, to, base_yaw, yaw_offset);
        }
    }
};

#endif