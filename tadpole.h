#ifndef TADPOLE_H
#define TADPOLE_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Tadpole
{
public:
    Tadpole(std::filesystem::path in_current_path):
        skin(110, 109, 85, true), black(0, 0, 0, false), material()
    {
        /*
        material.ambient = Vector3(0.3f, 0.2f, 0.1f);
        material.diffuse = Vector3(0.6f, 0.4f, 0.2f);
        material.specular = Vector3(0.1f, 0.1f, 0.1f);
        material.shininess = 8.0f;
        */

        in_current_path = in_current_path / "models" / "tadpole" ;

        Mesh3D* head_mesh = new Mesh3D(in_current_path, "TADPOLE_head.obj");
        head_mesh->add_faces(&skin);
        head_mesh->set_material(&material);


        Mesh3D* eyes_mesh = new Mesh3D(in_current_path, "TADPOLE_eyes.obj");
        eyes_mesh->add_faces(&black);
        eyes_mesh->set_material(&material);

        Mesh3D* tail_1_mesh = new Mesh3D(in_current_path, "TADPOLE_tail_1.obj");
        tail_1_mesh->add_faces(&skin);
        tail_1_mesh->set_material(&material);

        Mesh3D* tail_2_mesh = new Mesh3D(in_current_path, "TADPOLE_tail_2.obj");
        tail_2_mesh->add_faces(&skin);
        tail_2_mesh->set_material(&material);

        Mesh3D* tail_3_mesh = new Mesh3D(in_current_path, "TADPOLE_tail_3.obj");
        tail_3_mesh->add_faces(&skin);
        tail_3_mesh->set_material(&material);


        root = new SceneNode(0);
        head = new SceneNode(1, head_mesh);
        eyes = new SceneNode(2, eyes_mesh);
        tail_1 = new SceneNode(3, tail_1_mesh);
        tail_1->traslate(Vector3(0.0f, 0.0f, 0.0f), true);

        tail_2 = new SceneNode(4, tail_2_mesh);
        tail_2->traslate(Vector3(0.0f, -0.01f, 0.05f), true);

        tail_3 = new SceneNode(5, tail_3_mesh);
        tail_2->traslate(Vector3(0.0f, 0.01f, -0.1f), true);

        
        root->add_children(head);
        root->add_children(eyes);
        head->add_children(tail_1);
        tail_1->add_children(tail_2);
        tail_2->add_children(tail_3);


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
    SceneNode *root, *head, *eyes, *tail_1, *tail_2, *tail_3;

    Color skin, black;
    Material material;
};


#endif