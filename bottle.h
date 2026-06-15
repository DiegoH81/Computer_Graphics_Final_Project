#ifndef BOTTLE_H
#define BOTTLE_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Bottle
{
public:
    Bottle(std::filesystem::path in_current_path):
        white(250, 250, 250, true), material_glass()
    {
		material_glass.ambient = Vector3(0.52f, 0.52f, 0.52f);
		material_glass.diffuse = Vector3(0.85f, 0.85f, 0.85f);
		material_glass.specular = Vector3(0.90f, 0.90f, 0.90f);
		material_glass.shininess = 120.0f;
        material_glass.alpha_value = 0.1f;


        in_current_path = in_current_path / "models" ;

        Mesh3D* body_mesh = new Mesh3D(in_current_path, "bottle.obj");
        //body_mesh->shader_name = "GLASS_SHADER";
        body_mesh->add_faces(&white);
        body_mesh->set_material(&material_glass);


        root = new SceneNode(0);
        body = new SceneNode(1, body_mesh);



        root->add_children(body);
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
    SceneNode *root, *body;

    Color white;
    Material material_glass;
};


#endif