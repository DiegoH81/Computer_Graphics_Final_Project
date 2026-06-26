#ifndef STUMP_H
#define STUMP_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Stump
{
public:
    Stump(std::filesystem::path in_current_path, bool mode):
        brown(101, 67, 33, true), material_trunk()
    {
		material_trunk.ambient = Vector3(0.10f, 0.06f, 0.02f);
		material_trunk.diffuse = Vector3(0.38f, 0.22f, 0.10f);
		material_trunk.specular = Vector3(0.05f, 0.04f, 0.02f);
		material_trunk.shininess = 4.0f;


        std::filesystem::path base = in_current_path / "models" / "plants" / "dead_stuff";

		Mesh3D* body_mesh;
		
        if (mode)
            body_mesh = new Mesh3D(base / "UNIDO", "stump.obj");
        else
            body_mesh = new Mesh3D(base / "SEPARADO", "tronco.obj");

        body_mesh->add_faces(&material_trunk);
    

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
    SceneNode *root, *body, *hat;

    Color brown;
    Material material_trunk;
};


#endif