#ifndef BUSH_H
#define BUSH_H

#include <filesystem>

#include "scene.h"
#include "shape.h"
#include "material.h"

class Bush
{
public:
    Bush(std::filesystem::path in_current_path, int type, bool mode):
	green_grass (108,  118,  72, true), green_small (115, 128, 68, true), green_medium(82, 105, 48, true),  
	green_big   (52,  60,  28, true), material_grass(), material_small(), material_medium(), material_big()
    {
	
		material_grass.specular = Vector3(0.02f, 0.03f, 0.01f);
		material_grass.shininess = 5.0f;



		material_grass.ambient = Vector3(0.08f, 0.09f, 0.04f);
		material_grass.diffuse = Vector3(0.30f, 0.36f, 0.16f);
		material_grass.specular = Vector3(0.02f, 0.02f, 0.01f);
		material_grass.shininess = 5.0f;

		material_small.ambient = Vector3(0.10f, 0.12f, 0.05f);
		material_small.diffuse = Vector3(0.40f, 0.46f, 0.20f);  
		material_small.specular  = Vector3(0.03f, 0.03f, 0.01f);
		material_small.shininess = 10.0f;

		material_medium.ambient = Vector3(0.07f, 0.10f, 0.04f);
		material_medium.diffuse  = Vector3(0.26f, 0.38f, 0.16f);  
		material_medium.specular = Vector3(0.03f, 0.04f, 0.01f);
		material_medium.shininess = 10.0f;

		material_big.ambient = Vector3(0.04f, 0.05f, 0.02f);
		material_big.diffuse = Vector3(0.14f, 0.18f, 0.08f);  
		material_big.specular = Vector3(0.01f, 0.02f, 0.01f);
		material_big.shininess  = 10.0f;

        std::filesystem::path base = in_current_path / "models" / "plants" / "bushes";
		
		
		Mesh3D* bush_mesh1;
		Mesh3D* bush_mesh2;
		Mesh3D* bush_mesh3;
		Mesh3D* bush_mesh4;
		root = new SceneNode(0);
		
		
		if (mode)
		{			
			bush_mesh1 = new Mesh3D(base / "UNIDO", "grass.obj"); 
			bush_mesh2 = new Mesh3D(base / "UNIDO", "small_bush.obj");  
			bush_mesh3 = new Mesh3D(base / "UNIDO", "medium_bush.obj"); 
			bush_mesh4 = new Mesh3D(base / "UNIDO", "big_bush.obj");   
			
			bush_mesh1->add_faces(&green_grass); 
			bush_mesh2->add_faces(&green_small); 
			bush_mesh3->add_faces(&green_medium);
			bush_mesh4->add_faces(&green_big);
			
			bush_mesh1->set_material(&material_grass);
			bush_mesh2->set_material(&material_small);
			bush_mesh3->set_material(&material_medium);			   
			bush_mesh4->set_material(&material_big);
			
			bush1 = new SceneNode(1, bush_mesh1);
			bush2 = new SceneNode(2, bush_mesh2);
			bush3 = new SceneNode(3, bush_mesh3);
			bush4 = new SceneNode(4, bush_mesh4);
	
			root->add_children(bush1);
			root->add_children(bush2);
			root->add_children(bush3);
			root->add_children(bush4);
		}
		else
		{
			switch (type)
			{
				case 0: 
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "pasto.obj"); 
					break;
				case 1: 
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas1.obj"); 
					break;
				case 2:
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas2.obj"); 
					break;
				case 3: 
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas3.obj"); 
					break;
				case 4: 
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas4.obj"); 
					break;
				case 5: 
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas5.obj"); 
					break;
				case 6: 
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas6.obj"); 
					break;
				case 7: 
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas7.obj"); 
					break;
				case 8:
					bush_mesh1 = new Mesh3D(base / "SEPARADO", "hierva_hojas8.obj"); 
					break;
			}
			
			bush_mesh1->add_faces(&green_big);  
			bush_mesh1->set_material(&material_grass);
			bush1 = new SceneNode(1, bush_mesh1);
			root->add_children(bush1);
		}
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
    SceneNode *root, *bush1, *bush2, *bush3, *bush4;

    Color green_grass, green_small, green_medium, green_big;
	Material material_grass, material_small, material_medium, material_big;
};


#endif