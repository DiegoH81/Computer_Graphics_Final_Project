#ifndef TEAPOT_H
#define TEAPOT_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Teapot
{
public:
    Teapot(std::filesystem::path in_current_path):
        teapot_material()
    {
        teapot_material.ambient = Vector3(0.25f, 0.25f, 0.25f);
        teapot_material.diffuse = Vector3(0.752941, 0.752941, 0.752941);
        teapot_material.specular = Vector3(1.0f, 1.0f, 1.0f);
        teapot_material.shininess = 32.0f;
        
        in_current_path = in_current_path / "models";
		
		
		Mesh3D* teapot_mesh;
        teapot_mesh = new Mesh3D(in_current_path, "teapot.obj");


        teapot_mesh->add_faces(&teapot_material);
		

        root = new SceneNode(0);
        teapot = new SceneNode(1, teapot_mesh);

        root->add_children(teapot);
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

    SceneNode *root, *teapot;

    Material teapot_material;
};


#endif