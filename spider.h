#ifndef SPIDER_H
#define SPIDER_H

#include <filesystem>

#include "scene.h"
#include "shape.h"


class Spider
{
public:
    Spider(std::filesystem::path in_current_path):
        green(84, 161, 69, true), black(0, 0, 0, false)
    {
        in_current_path = in_current_path / "models" / "spider" ;

        Mesh3D* torso_mesh = new Mesh3D(in_current_path, "spider_torso.obj");
        torso_mesh->add_faces(&green);

        Mesh3D* back_mesh = new Mesh3D(in_current_path, "spider_back.obj");
        back_mesh->add_faces(&green);

        Mesh3D* leg_1_mesh = new Mesh3D(in_current_path, "spider_leg1.obj");
        leg_1_mesh->add_faces(&black);

        Mesh3D* leg_2_mesh = new Mesh3D(in_current_path, "spider_leg2.obj");
        leg_2_mesh->add_faces(&green);

        Mesh3D* leg_3_mesh = new Mesh3D(in_current_path, "spider_leg3.obj");
        leg_3_mesh->add_faces(&green);
        

        // --- Crear nodos ---
        root = new SceneNode(0);
        root->scale(Vector3(0.005f, 0.005f, 0.005f), true);

        torso = new SceneNode(1, torso_mesh);
        back = new SceneNode(2, back_mesh);
        back->traslate(Vector3(0.0f, 0.0f, -17.5f), true);

        leg_1 = new SceneNode(3, leg_1_mesh);
        leg_1->traslate(Vector3(0.0f, 0.0f, 0.0f), true);

        leg_2 = new SceneNode(4, leg_2_mesh);
        leg_2->traslate(Vector3(0.0f, 0.0f, 0.0f), true);

        leg_3 = new SceneNode(5, leg_3_mesh);
        leg_3->traslate(Vector3(0.0f, 0.0f, -17.5f), true);
        


        // --- Jerarquía ---
        root->add_children(torso);
        torso->add_children(back);
        torso->add_children(leg_1);
        leg_1->add_children(leg_2);
        leg_2->add_children(leg_3);
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
    SceneNode *root, *torso, *back, *leg_1, *leg_2, *leg_3;



    Color green, black;
};


#endif