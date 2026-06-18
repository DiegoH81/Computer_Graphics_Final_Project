#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

/*

Integrantes:
	Cornejo Castro, José Gabriel
	Hidalgo Machaca, Diego Alejandro
	Huarcaya Lizarraga, Astrid Judith


*/


#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cmath>
#include <thread>
#include <filesystem>

#include "utils.h"
#include "shader_list.h"
#include "animation_list.h"
#include "camera.h"
#include "texture_list.h"
#include "light_preset.h"

#include "gecko.h"
#include "spider.h"
#include "tadpole.h"
#include "butterfly.h"
#include "shrimp.h"
#include "bettle.h"
#include "mushroom.h"
#include "rock.h"
#include "rockCave.h"
#include "stump.h"
#include "bush.h"
#include "flower.h"
#include "algae.h"
#include "nenufar.h"
#include "bottle.h"
#include "terrain.h"
#include "table.h"
#include "creature_base.h"




#define BIG_MUSHROOM 1
#define LIL_MUSHROOM 0

#define NENUFAR_FLOWER 1
#define NENUFAR 0

#define WHITE 0
#define RED 1
#define YELLOW 2
#define BLUE 3

#define UNIDO 1
#define SEPARADO 0

#define BLOCK_1_DURATION 32.5f
#define BLOCK_2_DURATION 7.0f
#define BLOCK_3_DURATION 6.0f
#define BLOCK_4_DURATION 6.0f
#define BLOCK_5_DURATION 10.0f
#define BLOCK_6_DURATION 15.0f

// Path
std::filesystem::path current_path = std::filesystem::current_path().parent_path() / "ownProjects" / "COMPUTER_GRAPHICS_FINAL_PROJECT";
//current_path = current_path.parent_path();
//current_path = current_path / "ownProjects" / "COMPUTER_GRAPHICS_FINAL_PROJECT";

Color background_color(191, 133, 76, true);
Camera camera_world;
ShaderList shaders(current_path);

AnimationList camera_animations;
AnimationList light_animations;
AnimationList shrimp_animation;

std::vector<SceneNode*> nodes;
std::vector<LightPreset*> presets;

SceneNode* root = new SceneNode(0);
SceneNode* movable_root = new SceneNode(0);
SceneNode* glass_root = new SceneNode(1);
SceneNode* water_root = new SceneNode(2);

Shrimp* shrimpy = nullptr;

float offset = 1.0f;
float angle = 10.0f;
float sequence_timer = 0.0f;

bool is_moving = true;
bool sequence_running = false;
int width = 1920, height = 1080;

int  sequence_block   = 0;
int current_id = 0, preset_id = 0;


void traslate(const Vector3& in_m)
{
    for (auto &m_i : nodes)
    {
		if (m_i->id != current_id)
			continue;
		
        m_i->traslate(in_m, true);
    }
}

void scale(float factor)
{
    for (auto &m_i : nodes)
	{
		if (m_i->id != current_id)
			continue;

		m_i->scale(Vector3(factor, factor, factor), true);
	}
}

void rotate_c_x(float angle)
{
    for (auto &m_i : nodes)
    {
		if (m_i->id != current_id)
			continue;
        m_i->rotate_x_local(angle, true);
    }
}

void rotate_c_y(float angle)
{
    for (auto &m_i : nodes)
    {
		if (m_i->id != current_id)
			continue;
        m_i->rotate_y_local(angle, true);
    }
}

void rotate_c_z(float angle)
{
    for (auto &m_i : nodes)
    {
		if (m_i->id != current_id)
			continue;
        m_i->rotate_z_local(angle, true);
    }
}

void update_current_light(int in_id)
{
    // Delete current nodes from root
    for (auto ptr: presets[preset_id]->get_point_lights_ptr())
    {
        for (auto it = root->children.begin(); it != root->children.end(); it++)
        {
            if (*it == ptr)
            {
                root->children.erase(it);
                break;
            }
        }
    }

    preset_id = in_id;
    if (preset_id >= presets.size())
        preset_id = 0;


    // Add new light nodes from root
    for (auto ptr: presets[preset_id]->get_point_lights_ptr())
        root->add_children(ptr);
}

void block_1()
{
    update_current_light(0);

    // Light
    light_animations.add_animation({AnimationInfo(ALL_IDs, 360, "NONE", "PUBLIC")}, 17.5);
    light_animations.add_animation({AnimationInfo(ALL_IDs, 360, "ROTATE_C_Z", "PUBLIC")}, 3.5);

    // From camaroncin
    camera_world.set_pos(Point3(-10.0f, 15.5f, 0.0f));
    camera_world.set_objective(Point3(0.0f, 11.5f, 0.0f));

    camera_animations.add_animation({AnimationInfo(0, 0.0f, "NONE", "")}, 1.0);
    // To pecera
    camera_animations.add_animation({AnimationInfo(0, 10.0f, "ZOOM", "")}, 5.0);

    // De vuelta miramos al camaroncin
    camera_animations.add_animation({AnimationInfo(0, 180.0f, "ROTATE_Y", "")}, 3.0);
    camera_animations.add_animation({AnimationInfo(0, -25.0f, "ROTATE_Z", "")}, 1.5);
    camera_animations.add_animation({AnimationInfo(0, -8.0f, "ZOOM", "")}, 3.5);
    camera_animations.add_animation({AnimationInfo(0, 8.0f, "ROTATE_Z", "")}, 3.5);

    
    camera_animations.add_animation({AnimationInfo(0, 0.0f, "NONE", "")}, 3.5);

    // Zoom OUT
    camera_animations.add_animation({AnimationInfo(0, -20.0f, "ZOOM", ""),
                                     AnimationInfo(0, 15.0f, "ROTATE_Z", "")}, 4.5);
    
    // Orbita
    camera_animations.add_animation({AnimationInfo(0, 720, "ORBIT_Y_NO_SET", "")}, 7.0);
}

void block_2()
{
    update_current_light(4);
    camera_world.set_pos(Point3(0.0f, 15.0f, 30.0f));
    camera_world.set_objective(Point3(0.0f, 10.0f, 0.0f));

    camera_animations.add_animation({AnimationInfo(0, 720, "ORBIT_Y_NO_SET", ""),
                                     AnimationInfo(0, 10.0f, "ZOOM", "")}, 7.0);
}

void block_3()
{
    update_current_light(3);
    camera_world.set_pos(Point3(0.0f, 15.0f, 30.0f));
    camera_world.set_objective(Point3(0.0f, 10.0f, 0.0f));

    camera_animations.add_animation({AnimationInfo(0, 360, "ORBIT_Y_NO_SET", ""),
                                     AnimationInfo(0, 10.0f, "ZOOM", "")}, 6.0);
}

void block_4()
{
    auto projection_matrix = get_perspective(60.0f, float(width)/float(height), 0.1f, 100.0f);

    shaders.use_shader("UNIQUE");
    shaders.set_mat4("UNIQUE", "projection", projection_matrix);

    shaders.use_shader("LIGHT_SHADER");
    shaders.set_mat4("LIGHT_SHADER", "projection", projection_matrix);

    update_current_light(5);
    camera_world.set_pos(Point3(3.9f, 11.0f, 0.0f));
    camera_world.set_objective(Point3(0.0f, 11.0f, 0.0f));

    camera_animations.add_animation({AnimationInfo(0, 360, "ORBIT_Y_NO_SET", "")}, 6.0);
}

void block_5()
{
    auto projection_matrix = get_perspective(45.0f, float(width)/float(height), 0.1f, 100.0f);


    shaders.use_shader("UNIQUE");
    shaders.set_mat4("UNIQUE", "projection", projection_matrix);

    shaders.use_shader("LIGHT_SHADER");
    shaders.set_mat4("LIGHT_SHADER", "projection", projection_matrix);

    update_current_light(1);
    camera_world.set_pos(Point3(3.9f, 11.0f, 0.0f));
    camera_world.set_objective(Point3(0.0f, 11.0f, 0.0f));
    camera_animations.add_animation({AnimationInfo(0, 720, "ORBIT_Y_NO_SET", "")}, 10.0);
}

void block_6()
{
    update_current_light(2);
    shrimp_animation.add_animation({AnimationInfo(ALL_IDs, 1080, "ROTATE_Y", "PUBLIC")}, 15.0);
    camera_animations.add_animation({AnimationInfo(0, -7.0f, "ZOOM", "")}, 5.0);
}


void frame_buffer_size_call_back(GLFWwindow* in_window, int in_w, int in_h)
{
    glViewport(0, 0, in_w, in_h);

    width = in_w;
    height = in_h;

    auto projection_matrix = get_perspective(45.0f, float(in_w)/float(in_h), 0.1f, 100.0f);

    shaders.use_shader("UNIQUE");
    shaders.set_mat4("UNIQUE", "projection", projection_matrix);

    shaders.use_shader("LIGHT_SHADER");
    shaders.set_mat4("LIGHT_SHADER", "projection", projection_matrix);

}

void key_call_back(GLFWwindow* in_window, int key, int scan_code, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key ==GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(in_window, true);
        else if ( key == GLFW_KEY_A )
            camera_world.traslate(Vector3(-offset, 0.0f, 0.0f));
        else if ( key == GLFW_KEY_D)
            camera_world.traslate(Vector3(offset, 0.0f, 0.0f));
        else if ( key == GLFW_KEY_W)
            camera_world.traslate(Vector3(0.0f, offset, 0.0f));
        else if ( key == GLFW_KEY_S)
            camera_world.traslate(Vector3(0.0f, -offset, 0.0f));
        else if ( key == GLFW_KEY_I)
            camera_world.orbit_x(angle);
        else if ( key == GLFW_KEY_O)
            camera_world.orbit_x(-angle);
        else if ( key == GLFW_KEY_K)
            camera_world.orbit_y(angle);
        else if ( key == GLFW_KEY_L)
            camera_world.orbit_y(-angle);
        else if ( key == GLFW_KEY_N)
            camera_world.orbit_z(angle);
        else if ( key == GLFW_KEY_M)
            camera_world.orbit_z(-angle);
        else if ( key == GLFW_KEY_X)
            camera_world.zoom(offset);
        else if ( key == GLFW_KEY_C)
            camera_world.zoom(-offset);
        else if ( key == GLFW_KEY_T)
            is_moving = !is_moving;
        else if ( key == GLFW_KEY_1 )
        {
            block_1();
            sequence_timer  = 0.0f;
            sequence_block  = 0;
            sequence_running = true;
        }
        else if ( key  == GLFW_KEY_2 )
        {
            if (sequence_running)
                return;

            camera_world.set_pos(Point3(0.0f, 15.0f, 30.0f));
            camera_world.set_objective(Point3(0.0f, 10.0f, 0.0f));
        }
        else if ( key == GLFW_KEY_5 )
            shrimp_animation.add_animation({AnimationInfo(ALL_IDs, 1080, "ROTATE_Y", "PUBLIC")}, 15.0);
        else if ( key == GLFW_KEY_6 )
        {
            if (sequence_running)
                return;
            camera_world.set_pos(Point3(0.0f, 15.0f, 30.0f));
            camera_world.set_objective(Point3(0.0f, 10.0f, 0.0f));

            camera_animations.add_animation({AnimationInfo(0, 720, "ORBIT_Y_NO_SET", ""),
                                             AnimationInfo(0, 10.0f, "ZOOM", "")}, 7.0);
        }
        else if ( key == GLFW_KEY_7 )
        {
            if (sequence_running)
                return;
            camera_world.set_pos(Point3(3.9f, 11.0f, 0.0f));
            camera_world.set_objective(Point3(0.0f, 11.0f, 0.0f));

            camera_animations.add_animation({AnimationInfo(0, 720, "ORBIT_Y_NO_SET", "")}, 10.0);
        }
        else if ( key == GLFW_KEY_8 )
        {
            if (sequence_running)
                return;
            camera_world.set_pos(Point3(2.0f, 14.0f, 0.0f));
            camera_world.set_objective(Point3(0.0f, 10.0f, 0.0f));

            camera_animations.add_animation({AnimationInfo(0, 720, "ORBIT_Y_NO_SET", "")}, 10.0);
        }
        else if ( key == GLFW_KEY_9 )
        {
            if (sequence_running)
                return;
            camera_world.set_pos(Point3(-10.0f, 15.5f, 0.0f));
            camera_world.set_objective(Point3(0.0f, 11.5f, 0.0f));

            camera_animations.add_animation({AnimationInfo(0, 10.0f, "ZOOM", "")}, 5.0);

            camera_animations.add_animation({AnimationInfo(0, 180.0f, "ROTATE_Y", "")}, 3.0);
            camera_animations.add_animation({AnimationInfo(0, -25.0f, "ROTATE_Z", "")}, 1.5);
            camera_animations.add_animation({AnimationInfo(0, -8.0f, "ZOOM", "")}, 3.5);
            camera_animations.add_animation({AnimationInfo(0, 8.0f, "ROTATE_Z", "")}, 3.5);

            camera_animations.add_animation({AnimationInfo(0, 0.0f, "NONE", "")}, 3.5);

            camera_animations.add_animation({AnimationInfo(0, -20.0f, "ZOOM", ""),
                                             AnimationInfo(0, 15.0f, "ROTATE_Z", "")}, 4.5);
                                
            camera_animations.add_animation({AnimationInfo(0, 720, "ORBIT_Y_NO_SET", "")}, 7.0);
        }
        else if ( key == GLFW_KEY_0 )
        {
            if (sequence_running)
                return;
            light_animations.add_animation({AnimationInfo(ALL_IDs, 360, "ROTATE_C_Z", "PUBLIC")}, 6.0);
        }
        else if ( key == GLFW_KEY_G )
        {
            update_current_light(preset_id + 1);
            std::cout << "Current light preset: " << preset_id << "\n";
        }
    }	
}

int main()
{
    // Initialize
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(width, height, "Animation", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_call_back);
    glfwSetKeyCallback(window, key_call_back);

    // Init glad
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ***********************
    // SHADERS
    // ***********************
    
    // Normal Shader
    shaders.create_shader("UNIQUE", "normal_shader.vs", "normal_fragment.fs");
    // Light Shader
    shaders.create_shader("LIGHT_SHADER", "light_shader.vs", "light_fragment.fs");
    

    TextureList textures(current_path);
	

    LightPreset day = get_day();
    LightPreset night = get_night();
    LightPreset cyber_punk = get_cyberpunk();
    LightPreset desert = get_desert();
    LightPreset day_cicle = get_day_cicle();
    LightPreset bioluminiscente = get_bioluminiscente();
    LightPreset deep_sea = get_deep_sea();
    LightPreset candle_light = get_candlelight();

    presets.push_back(&day_cicle);
    presets.push_back(&day);
    presets.push_back(&night);
    presets.push_back(&cyber_punk);
    presets.push_back(&bioluminiscente);
    presets.push_back(&deep_sea);
    presets.push_back(&candle_light);
    
    
    
	
    // Colors
    Color pink(255.0f, 0.0f, 255.0f, true);
    Color blue(10.0f, 15.0f, 40.0f, true);
    Color mint(10.0f, 15.0f, 40.0f, true);
    Color lava(226.0f, 45.0f, 0.0f, true);
    Color radioactive(199.0f, 255.0f, 0.0f, true);
    Color turquesa(0.0f, 128.0f, 128.0f, true);
    Color purple(157.0f, 0.0f, 255.0f, true);
    Color golden(225.0f, 190.0f, 150.0f, true);
    Color le_lime(133.0f, 235.0f, 52.0f, true);
    Color red(255.0f, 0.0f, 0.0f, true);
    Color white(255.0f, 255.0f, 255.0f, true);

    // Camera
    camera_world.set_pos(Point3(0.0f, 15.0f, 30.0f));
    camera_world.set_objective(Point3(0.0f, 10.0f, 0.0f));


    // Figuras
	glLineWidth(10.0f);
    
	nodes.push_back(root);
	
    Cube cubito(0.3f);
    cubito.add_faces();
    cubito.set_face_color(0, &red);
    cubito.set_face_color(1, &radioactive);
    cubito.set_face_color(2, &red);
    cubito.set_face_color(3, &radioactive);
    cubito.set_face_color(4, &red);
    cubito.set_face_color(5, &radioactive);
    cubito.set_face_color(6, &red);
    cubito.set_face_color(7, &radioactive);

    cubito.add_edges(&le_lime);
    cubito.set_edge_color(0, &radioactive);
    cubito.set_edge_color(6, &radioactive);

    cubito.add_points(&purple);
    cubito.set_point_color(0, &radioactive);
    cubito.set_point_color(6, &radioactive);

    SceneNode* cubito_node = new SceneNode(1, &cubito);
    cubito_node->traslate(Vector3(-0.5f, 0.0f, 0.0f), true);

    Pyramid piramide(0.3f, 0.2f);
    piramide.add_faces(&golden);
    piramide.set_face_color(0, &pink);
    piramide.set_face_color(1, &radioactive);
    piramide.set_face_color(2, &turquesa);
    piramide.set_face_color(3, &radioactive);
    piramide.set_face_color(4, &pink);

    piramide.add_edges(&le_lime);
    piramide.add_points(&purple);
    SceneNode* piramide_node = new SceneNode(2, &piramide);
    piramide_node->traslate(Vector3(0.5f, 0.0f, 0.0f), true);


    Cone conito(40, 0.3f, 0.2f);
    conito.add_faces();
    conito.set_face_color(0, &pink);
    conito.set_face_color(1, &radioactive);

    conito.add_edges(&le_lime);
    conito.add_points(&purple);
    SceneNode* conito_node = new SceneNode(3, &conito);
    conito_node->traslate(Vector3(0.0f, -0.5f, 0.0f), true);

    Sphere esferita(40, 0.3f);
    esferita.add_faces(&golden);
    esferita.set_face_color(0, &pink);
    esferita.set_face_color(4, &pink);
    //esferita.add_edges(&le_lime);
    //esferita.add_points(&purple);

    SceneNode* sphere_node = new SceneNode(3, &esferita);
    sphere_node->traslate(Vector3(0.0f, 0.5f, 0.0f), true);
    
    Gecko geckito(current_path);

    //geckito.get_root()->traslate(Vector3(0.0f, 15.0f, -2.0f), true);
    geckito.get_root()->traslate(Vector3(0.0f, 0.0f, -2.0f), true);
    
    Spider aranita(current_path);
    aranita.get_root()->traslate(Vector3(0.7f, 15.0f, 0.0f), true);
	
	Butterfly mariposa(current_path);
    mariposa.get_root()->traslate(Vector3(0.0f, 15.0f, 0.0f), true);
	
	Bettle carabajito(current_path);
	carabajito.get_root()->traslate(Vector3(0.0f, 15.0f, 0.0f),true);
  
	
    Tadpole tadpolin(current_path, UNIDO);
	Terrain terreno(current_path);
	Table mesa(current_path);


	
//	Mushroom honguito1(current_path,LIL_MUSHROOM);
	
	Rock piedras1(current_path,UNIDO);
	RockCave cueva1(current_path,UNIDO);
	Stump tronco1(current_path,UNIDO);
	Algae alga(current_path,UNIDO); 


	Nenufar lilypad(current_path,NENUFAR,UNIDO); 
	
    //Nenufar lilypad_flor(current_path,NENUFAR_FLOWER); 
    //lilypad_flor.get_root()->traslate(Vector3(1.0f, -0.8f, 1.5f),true);

	Mushroom hongo1(current_path,BIG_MUSHROOM, UNIDO);
	Bush hojas0 (current_path, 1,UNIDO);
	Bush pasto(current_path, 0, UNIDO);
	Flower flor1(current_path,WHITE,UNIDO); 
    shrimpy = new Shrimp(current_path);

	Bottle botella(current_path); 
    //botella.get_root()->scale(Vector3(0.85f, 0.85f, 0.85f), true);
	

	/*
    root->add_children(cubito_node);
    root->add_children(piramide_node);
    root->add_children(conito_node);
    root->add_children(sphere_node);
    */


    for (auto ptr: presets[current_id]->get_point_lights_ptr())
        root->add_children(ptr);
	
	
    movable_root->add_children(geckito.get_root());
    movable_root->add_children(aranita.get_root());
	movable_root->add_children(mariposa.get_root());
	movable_root->add_children(carabajito.get_root());


    root->add_children(hongo1.get_root());

    root->add_children(tadpolin.get_root());
	root->add_children(shrimpy->get_root());
	root->add_children(flor1.get_root());
	root->add_children(hojas0.get_root());
	root->add_children(pasto.get_root());	
	root->add_children(piedras1.get_root());
	root->add_children(cueva1.get_root());	
	root->add_children(tronco1.get_root());	
	root->add_children(alga.get_root());
	root->add_children(lilypad.get_root());
	root->add_children(terreno.get_root());
	root->add_children(mesa.get_root());
	
	glass_root->add_children(botella.get_root());	
	water_root->add_children(terreno.get_water());
    
    // Bucle
	glPointSize(10.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);  

    float delta_time = 0.0f;
    float last_frame = 0.0f;
	
    auto projection_matrix = get_perspective(45.0f, float(width)/float(height), 0.1f, 100.0f);
    shaders.use_shader("UNIQUE");
    shaders.set_mat4("UNIQUE", "projection", projection_matrix);

    shaders.use_shader("LIGHT_SHADER");
    shaders.set_mat4("LIGHT_SHADER", "projection", projection_matrix);


    PlaneSurface plane(11);
    WaveSurface wave(10.5);
    MountainSurface mountain;

    while(!glfwWindowShouldClose(window))
    {
        float current_frame = glfwGetTime();
        delta_time = std::min(current_frame - last_frame, 0.05f);
        last_frame = current_frame;

        if (sequence_running)
        {
            sequence_timer += delta_time;

            if (sequence_block == 0 && sequence_timer >= BLOCK_1_DURATION)
            {
                block_2();
                sequence_block = 1;
            }
            else if (sequence_block == 1 && sequence_timer >= BLOCK_1_DURATION + BLOCK_2_DURATION)
            {
                block_3();
                sequence_block = 2;
            }
            else if (sequence_block == 2 && sequence_timer >= BLOCK_1_DURATION + BLOCK_2_DURATION + BLOCK_3_DURATION)
            {
                block_4();
                sequence_block = 3;
            }
            else if (sequence_block == 3 && sequence_timer >= BLOCK_1_DURATION + BLOCK_2_DURATION + BLOCK_3_DURATION + BLOCK_4_DURATION)
            {
                block_5();
                sequence_block = 4;
            }
            else if (sequence_block == 4 && sequence_timer >= BLOCK_1_DURATION + BLOCK_2_DURATION + BLOCK_3_DURATION + BLOCK_4_DURATION + BLOCK_5_DURATION)
            {
                block_6();
                sequence_block = 5;
                sequence_running = false;
                sequence_timer = 0.0f;
            }
        }

        camera_animations.process_animations_camera(camera_world, nodes, delta_time);
        light_animations.process_animations(presets[preset_id]->get_point_lights_ptr(), delta_time);
        shrimp_animation.process_animations({shrimpy->get_upper_root()}, delta_time);


        glClearColor(background_color.r, background_color.g, background_color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto view_matrix = camera_world.get_look_at();
        auto camera_pos = camera_world.pos;

        presets[preset_id]->apply(shaders, background_color);
        if (presets[preset_id]->has_animation)
            presets[preset_id]->update_cycle();

        shaders.use_shader("LIGHT_SHADER");
        shaders.set_mat4("LIGHT_SHADER", "view", view_matrix);

        shaders.use_shader("UNIQUE");
        shaders.set_mat4("UNIQUE", "view", view_matrix);
        shaders.set_vec3("UNIQUE", "view_pos", camera_pos.x, camera_pos.y, camera_pos.z);
        
		presets[preset_id]->apply(shaders, background_color);
		


        shaders.use_shader("LIGHT_SHADER");
        shaders.set_mat4("LIGHT_SHADER", "view", view_matrix);

		root->draw(shaders, textures, Matrix_4());
        movable_root->draw(shaders, textures, Matrix_4());

        geckito.wander(delta_time, wave, 1.5f);
        carabajito.wander(delta_time, wave, 0.75f);
        aranita.wander(delta_time, wave, 0.75);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);

        
        water_root->draw(shaders, textures, Matrix_4());
        

        glass_root->draw(shaders, textures, Matrix_4());
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);


        //shrimpy.get_upper_root()->rotate_y_local(90.0f * delta_time, true);
        //shrimpy.get_root()->rotate_y_global(90.0f * delta_time, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Delete - optional
    shaders.delete_programs();
    glfwTerminate();
    return 0;
}
