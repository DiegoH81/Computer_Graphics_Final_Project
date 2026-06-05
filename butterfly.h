#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"


class Butterfly
{
public:
    Butterfly(std::filesystem::path in_current_path):
        sky_blue(60, 168, 232, true), black(0, 0, 0, false), material()
    {
        in_current_path = in_current_path / "models" / "butterfly" ;

        /*
        material.ambient = Vector3(0.0f, 0.0f, 0.15f);
        material.diffuse = Vector3(0.05f, 0.05f, 0.6f);
        material.specular = Vector3(0.2f, 0.2f, 0.2f);
        material.shininess = 16.0f;
        */

        Mesh3D* torso_mesh = new Mesh3D(in_current_path, "torso_BUTTERFLY.obj");
        torso_mesh->add_faces(&black);
        torso_mesh->set_material(&material);

        Mesh3D* antenitas_mesh = new Mesh3D(in_current_path, "antenitas_BUTTERFLY.obj");
        antenitas_mesh->add_faces(&black);
        antenitas_mesh->set_material(&material);

        Mesh3D* ala_izq_mesh = new Mesh3D(in_current_path, "ala_izq_BUTTERFLY.obj");
        ala_izq_mesh->add_faces(&sky_blue);
        ala_izq_mesh->set_material(&material);

        Mesh3D* ala_der_mesh = new Mesh3D(in_current_path, "ala_der_BUTTERFLY.obj");
        ala_der_mesh->add_faces(&sky_blue);
        ala_der_mesh->set_material(&material);


        root = new SceneNode(0);
        torso = new SceneNode(1, torso_mesh);
        antenitas = new SceneNode(2, antenitas_mesh);
        ala_right = new SceneNode(3, ala_der_mesh);
        ala_left = new SceneNode(4, ala_izq_mesh);

        
        root->add_children(torso);
        root->add_children(antenitas);
        torso->add_children(ala_left);
        torso->add_children(ala_right);
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
    SceneNode *root, *torso, *antenitas, *ala_right, *ala_left;

    Color sky_blue, black;
    Material material;
};


#endif