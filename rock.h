#ifndef ROCK_H
#define ROCK_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Rock
{
public:
    Rock(std::filesystem::path in_current_path, bool mode):
        gray(128, 128, 128, true), material_stone()
    {
		material_stone.ambient = Vector3(0.10f, 0.11f, 0.08f);
		material_stone.diffuse = Vector3(0.42f, 0.40f, 0.32f);
		material_stone.specular = Vector3(0.08f, 0.08f, 0.06f);
		material_stone.shininess = 30.0f;


        std::filesystem::path base = in_current_path / "models" / "plants" / "dead_stuff";

		Mesh3D* body_mesh;
		
        if (mode)
            body_mesh = new Mesh3D(base / "UNIDO", "rocks.obj");
        else
            body_mesh = new Mesh3D(base / "SEPARADO", "rocas.obj");


        body_mesh->add_faces(&material_stone);

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

    Color gray;
    Material material_stone;
};


#endif