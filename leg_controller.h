#ifndef LEG_CONTROLLER_H
#define LEG_CONTROLLER_H

#include "scene.h"
#include "surface.h"
#include "vector.h"
#include "matrix.h"
#include <cmath>

inline Point3 extract_world_pos(const Matrix_4& m)
{
    return Point3(m.matrix[3], m.matrix[7], m.matrix[11]);
}

class LegController
{
public:
    Vector3 rest_offset;
    Vector3 anchor_offset;

    float thigh_len;
    float shin_len;
    float step_range;
    float step_speed;
    float step_height;

    Point3 prev_torso_pos;
    bool   has_prev = false;

    SceneNode* thigh;
    SceneNode* shin;

    Point3 current_foot;
    Point3 target_foot;
    bool   is_stepping;
    float yaw_offset = 0.0f;  // corrige dirección natural del mesh
    float  step_t          = 0.0f;
    float  step_total_dist = 1.0f;
    Point3 start_foot;

    LegController() :
        thigh_len(0.15f), shin_len(0.12f),
        step_range(0.52f), step_speed(3.0f), step_height(0.08f),
        thigh(nullptr), shin(nullptr),
        current_foot(), target_foot(),
        is_stepping(false)
    {}

    void init(SceneNode* in_thigh, SceneNode* in_shin,
              Vector3 in_rest_offset, Vector3 in_anchor_offset,
              float in_thigh_len, float in_shin_len)
    {
        thigh         = in_thigh;
        shin          = in_shin;
        rest_offset   = in_rest_offset;
        anchor_offset = in_anchor_offset;
        thigh_len     = in_thigh_len;
        shin_len      = in_shin_len;

        // Guardar traslacion inicial — es lo unico que hay en private/public
        // al momento del init (el constructor solo llama traslate)
        thigh_t_priv = { thigh->private_transform.matrix[3],
                         thigh->private_transform.matrix[7],
                         thigh->private_transform.matrix[11] };
        thigh_t_pub  = { thigh->public_transform.matrix[3],
                         thigh->public_transform.matrix[7],
                         thigh->public_transform.matrix[11] };
        shin_t_priv  = { shin->private_transform.matrix[3],
                         shin->private_transform.matrix[7],
                         shin->private_transform.matrix[11] };
        shin_t_pub   = { shin->public_transform.matrix[3],
                         shin->public_transform.matrix[7],
                         shin->public_transform.matrix[11] };

        current_foot = in_rest_offset;
    }

    void update(float dt, const Matrix_4& torso_world, const SurfaceFunction& surface)
{
    Point3 torso_pos    = extract_world_pos(torso_world);
    Point3 anchor_world = torso_pos + anchor_offset;

    // Velocidad del torso
    Vector3 torso_vel(0,0,0);
    if (has_prev)
    {
        torso_vel.x = (torso_pos.x - prev_torso_pos.x) / dt;
        torso_vel.z = (torso_pos.z - prev_torso_pos.z) / dt;
    }
    prev_torso_pos = torso_pos;
    has_prev       = true;

    // Lookahead en direccion de movimiento
    float lookahead = 0.18f;
    Point3 rest_world = Point3(
        torso_pos.x + rest_offset.x + torso_vel.x * lookahead,
        torso_pos.y + rest_offset.y,
        torso_pos.z + rest_offset.z + torso_vel.z * lookahead
    );

    SurfaceHit rest_hit = surface.project(rest_world);
    Point3 rest_on_surf = rest_hit.position;

    // --- Decidir si dar un paso ---
    if (!is_stepping)
    {
        float dx = current_foot.x - rest_on_surf.x;
        float dz = current_foot.z - rest_on_surf.z;
        if (std::sqrt(dx*dx + dz*dz) > step_range)
        {
            start_foot      = current_foot;
            target_foot     = rest_on_surf;
            step_t          = 0.0f;
            step_total_dist = std::sqrt(dx*dx + dz*dz);
            if (step_total_dist < 0.001f) step_total_dist = 0.001f;
            is_stepping     = true;
        }
    }

    // --- Avanzar el paso ---
    if (is_stepping)
    {
        float dx        = target_foot.x - current_foot.x;
        float dz        = target_foot.z - current_foot.z;
        float remaining = std::sqrt(dx*dx + dz*dz);
        float move      = step_speed * dt;

        if (move >= remaining)
        {
            current_foot = target_foot;
            is_stepping  = false;
            step_t       = 1.0f;
        }
        else
        {
            float ratio  = move / remaining;
            current_foot.x += dx * ratio;
            current_foot.z += dz * ratio;

            step_t += dt * step_speed / step_total_dist;
            step_t  = std::min(step_t, 1.0f);

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

    solve_ik(anchor_world, current_foot);
}
private:
    // Traslaciones iniciales guardadas en init()
    Vector3 thigh_t_priv, thigh_t_pub;
    Vector3 shin_t_priv,  shin_t_pub;

    // Escribe T * R en ambas transforms del nodo, sin acumular
    void write_transform(SceneNode* node,
                         const Vector3& t_priv, const Vector3& t_pub,
                         float r00, float r01, float r02,
                         float r10, float r11, float r12,
                         float r20, float r21, float r22)
    {
        node->private_transform.set_matrix({
            r00, r01, r02, t_priv.x,
            r10, r11, r12, t_priv.y,
            r20, r21, r22, t_priv.z,
              0,   0,   0, 1
        });
        node->public_transform.set_matrix({
            r00, r01, r02, t_pub.x,
            r10, r11, r12, t_pub.y,
            r20, r21, r22, t_pub.z,
              0,   0,   0, 1
        });
    }

    void solve_ik(const Point3& anchor, const Point3& foot)
    {
        if (!thigh || !shin) return;

        Vector3 dir = foot - anchor;
        float dist  = vec_length(dir);

        float max_reach = thigh_len + shin_len - 0.001f;
        if (dist > max_reach) dist = max_reach;
        if (dist < 0.001f)    dist = 0.001f;

        float L1 = thigh_len, L2 = shin_len;

        float cos_knee = (L1*L1 + L2*L2 - dist*dist) / (2.0f * L1 * L2);
        cos_knee = std::max(-1.0f, std::min(1.0f, cos_knee));
        float knee_rad = std::acos(cos_knee);

        float cos_hip = (L1*L1 + dist*dist - L2*L2) / (2.0f * L1 * dist);
        cos_hip = std::max(-1.0f, std::min(1.0f, cos_hip));
        float hip_rad = std::acos(cos_hip);

        float yaw = std::atan2(dir.x, dir.z) + yaw_offset;
        float pitch = std::atan2(-dir.y,
                        std::sqrt(dir.x*dir.x + dir.z*dir.z));

        // Construir R_thigh = Ry(yaw) * Rx(pitch + hip)
        float ry = yaw, rx = pitch + hip_rad;
        float cy = std::cos(ry), sy = std::sin(ry);
        float cx = std::cos(rx), sx = std::sin(rx);

        write_transform(thigh, thigh_t_priv, thigh_t_pub,
             cy,      sy*sx,  sy*cx,
             0,       cx,    -sx,
            -sy,      cy*sx,  cy*cx);

        // Construir R_shin = Rx(knee - pi)  (dobla la rodilla)
        float rk = knee_rad - 3.14159265f;
        float ck = std::cos(rk), sk = std::sin(rk);

        write_transform(shin, shin_t_priv, shin_t_pub,
            1,  0,   0,
            0,  ck, -sk,
            0,  sk,  ck);
    }
};

#endif