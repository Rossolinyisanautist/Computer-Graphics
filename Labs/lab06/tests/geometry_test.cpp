//
//  geometry_test.cpp
//  geometry_test
//
//  Created by Isa on 3/8/20.
//


#include "aur.hpp"

static const float CAMERA_SPEED{ 0.1f };
static const float CAMERA_ROT_SPEED{ 0.05f };

static const glm::vec4 FORWARD{ 0.0f, 0.0f, 1.0f, 0.0f };
static const float ROT_SPEED = 0.05f;

int main(int argc, char** argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    auto root_empty_object = std::make_shared<Object>();
    
    // CIRCLES
    auto circle_geometry_1_data = geometry_generators::generate_circle_geometry_data(0.5f, 15);
    auto circle_geometry_1 = std::make_shared<ES2Geometry>(circle_geometry_1_data.first, circle_geometry_1_data.second);
    circle_geometry_1->set_type(Geometry::Type::TriangleFan);
    auto circle_material_1 = std::make_shared<ES2ConstantMaterial>();
    circle_material_1->set_emission_color(glm::vec4(1.0f, 0.0f, 1.0f, 0.0f));
    auto circle_mesh_1 = std::make_shared<Mesh>(circle_geometry_1, circle_material_1, glm::vec3(-3.0f,  2.0f, 0.0f));


    auto circle_geometry_2_data = geometry_generators::generate_circle_geometry_data(0.5f, 15);
    auto circle_geometry_2 = std::make_shared<ES2Geometry>(circle_geometry_2_data.first, circle_geometry_2_data.second);
    circle_geometry_2->set_type(Geometry::Type::LineLoop);
    auto circle_material_2 = std::make_shared<ES2ConstantMaterial>();
    circle_material_2->set_emission_color(glm::vec4(0.9f, 1.0f, 0.3f, 0.0f));
    auto circle_mesh_2 = std::make_shared<Mesh>(circle_geometry_2, circle_material_2, glm::vec3(0.0f,  2.0f, 0.0f));

    
    auto circle_geometry_3_data = geometry_generators::generate_circle_geometry_data(0.5f, 15);
    auto circle_geometry_3 = std::make_shared<ES2Geometry>(circle_geometry_3_data.first, circle_geometry_3_data.second);
    circle_geometry_3->set_type(Geometry::Type::Points);
    auto circle_material_3 = std::make_shared<ES2ConstantMaterial>();
    circle_material_3->set_emission_color(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
    auto circle_mesh_3 = std::make_shared<Mesh>(circle_geometry_3, circle_material_3, glm::vec3(3.0f,  2.0f, 0.0f));
    
    // CIRCLES PARENTING
    root_empty_object->add_child(circle_mesh_1);
    root_empty_object->add_child(circle_mesh_2);
    root_empty_object->add_child(circle_mesh_3);
    
    // SPHERES
    auto sphere_geometry_data_1 = geometry_generators::generate_sphere_geometry_data(.5f, 10, 10);
    auto sphere_geometry_1 = std::make_shared<ES2Geometry>(sphere_geometry_data_1.first, sphere_geometry_data_1.second);
    sphere_geometry_1->set_type(Geometry::Type::TriangleFan);
    auto sphere_material_1 = std::make_shared<ES2ConstantMaterial>();
    sphere_material_1->set_emission_color(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));
    auto sphere_mesh_1 = std::make_shared<Mesh>(sphere_geometry_1, sphere_material_1, glm::vec3(-3.0f,  0.0f, 0.0f));
    
    // SPHERES PARENTING
    root_empty_object->add_child(sphere_mesh_1);
    
    // PLANES
    auto plane_geometry_data_1 = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 10, 10);
    auto plane_geometry_1 = std::make_shared<ES2Geometry>(plane_geometry_data_1.first, plane_geometry_data_1.second);
    plane_geometry_1->set_type(Geometry::Type::TriangleFan);
    auto plane_material_1 = std::make_shared<ES2ConstantMaterial>();
    plane_material_1->set_emission_color(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    auto plane_mesh_1 = std::make_shared<Mesh>(plane_geometry_1, plane_material_1, glm::vec3(-3.0f,  -2.0f, 0.0f));
    
    
    // PLANES PARENTING
    root_empty_object->add_child(plane_mesh_1);
    
    std::vector<std::shared_ptr<Object>> objects { root_empty_object };
    auto scene = std::make_shared<Scene>(objects);
    
    auto camera = scene->get_camera();
    camera->set_z(5.0f);
    
    window->set_on_key([&](int key) {
        switch (key) {
            case SDLK_w: camera->set_rotation_x(camera->get_rotation_x() + CAMERA_ROT_SPEED); break;
            case SDLK_a: camera->set_rotation_y(camera->get_rotation_y() + CAMERA_ROT_SPEED); break;
            case SDLK_s: camera->set_rotation_x(camera->get_rotation_x() - CAMERA_ROT_SPEED); break;
            case SDLK_d: camera->set_rotation_y(camera->get_rotation_y() - CAMERA_ROT_SPEED); break;
            case SDLK_e: camera->set_y(camera->get_y() + CAMERA_ROT_SPEED); break;
            case SDLK_q: camera->set_y(camera->get_y() - CAMERA_ROT_SPEED); break;
            case SDLK_UP: camera->set_position(camera->get_position() - glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED));   break;
            case SDLK_DOWN: camera->set_position(camera->get_position() + glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_ESCAPE: exit(0); break;
            default: break;
        }
    });
    
    ES2Renderer renderer(scene, window);
    while (1) {
        window->poll();

        // TODO
        // CIRCLES ROTATION
        circle_mesh_1->set_rotation_y(circle_mesh_1->get_rotation_y() + ROT_SPEED);
        circle_mesh_1->set_rotation_x(circle_mesh_1->get_rotation_x() - ROT_SPEED);
        
        circle_mesh_2->set_rotation_y(circle_mesh_2->get_rotation_y() - ROT_SPEED);
        circle_mesh_2->set_rotation_x(circle_mesh_2->get_rotation_x() + ROT_SPEED);
        
        circle_mesh_3->set_rotation_y(circle_mesh_3->get_rotation_y() - ROT_SPEED);
        circle_mesh_3->set_rotation_x(circle_mesh_3->get_rotation_x() - ROT_SPEED);
        
        // SPHERES ROTATION
        sphere_mesh_1->set_rotation_y(sphere_mesh_1->get_rotation_y() - ROT_SPEED);
        sphere_mesh_1->set_rotation_x(sphere_mesh_1->get_rotation_x() - ROT_SPEED);
        // TODO: COPY AND PASTE REMAINING SPHERES
        
        // PLANES ROTATION
        
        plane_mesh_1->set_rotation_y(plane_mesh_1->get_rotation_y() - ROT_SPEED);
        plane_mesh_1->set_rotation_x(plane_mesh_1->get_rotation_x() - ROT_SPEED);
        // TODO: COPY AND PASTE REMAINING PLANES
        
        renderer.render();
       
    }
    
}


