#ifndef BUSH_H
#define BUSH_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Bush
{
public:
    Bush(std::filesystem::path in_current_path, int type):
        green(85, 130, 50, true), material_leaf()
    {
		material_leaf.ambient = Vector3(0.05f, 0.10f, 0.03f);
        material_leaf.diffuse = Vector3(0.20f, 0.45f, 0.10f);
        material_leaf.specular = Vector3(0.05f, 0.08f, 0.03f);
        material_leaf.shininess = 10.0f;

        in_current_path = in_current_path / "models" / "plants" / "bushes";
		
		
		Mesh3D* body_mesh;

        switch(type)
        {
			case 0: 
				body_mesh = new Mesh3D(in_current_path,  "pasto.obj"); 
				break;
			case 1: 
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas1.obj"); 
				break;
            case 2:
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas2.obj"); 
				break;
            case 3: 
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas3.obj"); 
				break;
            case 4: 
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas4.obj"); 
				break;
            case 5: 
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas5.obj"); 
				break;
            case 6: 
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas6.obj"); 
				break;
            case 7: 
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas7.obj"); 
				break;
            case 8:
				body_mesh = new Mesh3D(in_current_path,  "hierva_hojas8.obj"); 
				break;
        }
        

        body_mesh->add_faces(&green);
        body_mesh->set_material(&material_leaf);


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

    Color green;
    Material material_leaf;
};


#endif