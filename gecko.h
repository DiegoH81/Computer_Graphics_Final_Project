#ifndef GECKO_H
#define GECKO_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

#include "leg_controller.h"

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

legs[0].init(leg_A_D_1, leg_A_D_2,
             Vector3(-0.28f, -0.08f,  0.20f),  // A_D: pie en -X
             Vector3(-0.10f,  0.00f,  0.20f),
             0.088f, 0.094f);

legs[1].init(leg_A_I_1, leg_A_I_2,
             Vector3( 0.28f, -0.08f,  0.20f),  // A_I: pie en +X
             Vector3( 0.10f,  0.00f,  0.20f),
             0.087f, 0.092f);

legs[2].init(leg_D_D_1, leg_D_D_2,
             Vector3(-0.24f, -0.08f, -0.28f),  // D_D: pie en -X y -Z
             Vector3(-0.07f,  0.00f, -0.20f),
             0.065f, 0.103f);

legs[3].init(leg_D_I_1, leg_D_I_2,
             Vector3( 0.28f, -0.08f, -0.18f),  // D_I: pie en +X y -Z
             Vector3( 0.12f, -0.05f, -0.10f),
             0.127f, 0.109f);

legs[0].yaw_offset =  PI * 0.5f;      // A_D:  90°
legs[1].yaw_offset = -PI * 0.5f;      // A_I: -90°
legs[2].yaw_offset =  PI * 0.75f;     // D_D:  135°
legs[3].yaw_offset = -2.1910f;        // D_I: -125.5°


    }

    void draw(ShaderList& in_shaders, TextureList& in_texturs, const Matrix_4& in_mat)
    {
        root->draw(in_shaders, in_texturs, in_mat);
    }

    SceneNode* get_root()
    {
        return root;
    }

    void update(float dt, const SurfaceFunction& surface)
    {
        // torso->parent_transform es válido después del draw del frame anterior
        for (int i = 0; i < 4; i++)
            legs[i].update(dt, torso->parent_transform, surface);

    }

    void move(const Vector3& delta)
    {
        get_root()->traslate(delta, true);
    }

    void rotate(float angle_deg)
    {
        get_root()->rotate_y_local(angle_deg, true);
    }

    void align_torso_to_surface(const SurfaceFunction& surface)
    {
        // Promedio de las 4 normales bajo cada pie
        Vector3 avg_normal(0, 0, 0);
        for (int i = 0; i < 4; i++)
        {
            SurfaceHit hit = surface.project(legs[i].current_foot);
            avg_normal = avg_normal + hit.normal;
        }
        avg_normal = normalize(avg_normal);

        // Altura del torso = promedio de alturas de los 4 pies + offset
        float avg_y = 0.0f;
        for (int i = 0; i < 4; i++)
            avg_y += legs[i].current_foot.y;
        avg_y /= 4.0f;

        float body_height = 0.08f;  // cuánto sube el torso sobre los pies

        // Extraer posición XZ actual del root (traslación acumulada)
        float root_x = root->public_transform.matrix[3];
        float root_z = root->public_transform.matrix[11];

        // Construir la rotación que alinea Y con avg_normal
        // usando dos vectores: up=(0,1,0) → avg_normal
        Vector3 up(0, 1, 0);
        Vector3 axis = cross(up, avg_normal);
        float   axis_len = vec_length(axis);

        // Construir matriz de rotación del torso
        Matrix_4 R;
        if (axis_len > 0.001f)
        {
            axis = normalize(axis);
            float cos_a = dot_product(up, avg_normal);
            cos_a = std::max(-1.0f, std::min(1.0f, cos_a));
            float sin_a = axis_len;

            float x = axis.x, y = axis.y, z = axis.z;
            float c = cos_a, s = sin_a, t = 1.0f - c;

            R.set_matrix({
                t*x*x+c,   t*x*y-s*z, t*x*z+s*y, 0,
                t*x*y+s*z, t*y*y+c,   t*y*z-s*x, 0,
                t*x*z-s*y, t*y*z+s*x, t*z*z+c,   0,
                0,         0,         0,          1
            });
        }

        // Aplicar: T(pos) * R(normal) al torso
        // Preservar XZ del root, ajustar Y a la superficie
        float tx = root->public_transform.matrix[3];
        float tz = root->public_transform.matrix[11];

        torso->private_transform = R;
        torso->public_transform  = R;

        // Ajustar Y del root para que el cuerpo quede sobre la superficie
        root->public_transform.matrix[7]  = avg_y + body_height;
        root->private_transform.matrix[7] = avg_y + body_height;
    }

    LegController legs[4];

    SceneNode *root, *head, *eyes, *torso, *leg_A_D_1, *leg_A_D_2,
                                 *leg_A_I_1, *leg_A_I_2,
                                 *leg_D_D_1, *leg_D_D_2,
                                 *leg_D_I_1, *leg_D_I_2,
                                 *tail_1, *tail_2, *tail_3;

    Color green, black;
    Material skin_material, eye_material;
};


#endif