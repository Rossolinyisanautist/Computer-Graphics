//
//  lightning_test.cpp
//  lightning_test
//
//  Created by Isa on 3/8/20.
//

#include "aur.hpp"
 
static const float CAMERA_SPEED{ 0.1f };
static const float CAMERA_ROT_SPEED{ 0.05f };
static const glm::vec4 FORWARD{ 0.0f, 0.0f, 1.0f, 0.0f };

static const float PLANE_WIDTH = 300.0f;
static const float PLANE_HEIGHT = 300.0f;
static const int PLANE_WIDTH_SEGMENTS = 100;
static const int PLANE_HEIGHT_SEGMENTS = 100;
static const glm::vec4 PLANE_EMISSION_COLOR = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
static const float PLANE_SPECULAR_EXPONENT = 10.0f;
static const glm::vec3 PLANE_POSITION = glm::vec3{ .0f, -2.0f, .0f };

static const float CENTER_SPHERE_RADIUS = .5f;
static const float CENTER_SPHERE_SEGMENTS = 30;
static const float CENTER_SPHERE_RINGS = 30;
static const glm::vec3 CENTER_SPHERE_POSITION = glm::vec3{ 0.0f };
static const float CENTER_SPHERE_SPECULAR_EXPONENT = 5.0f;
static const glm::vec4 CENTER_SPHERE_EMMISION_COLOR = glm::vec4{ 1.0f, 0.8f, 0.5f, 1.0f };

static const glm::vec3 LIGHT_SOURCE_0_DIFFUSE_COLOR = glm::vec3(1.0f, .8f, .5f);
static const glm::vec3 LIGHT_SOURCE_0_SPECULAR_COLOR = glm::vec3(1.0f, .8f, .5f);

static const float LIGHT_SPHERE_1_RADIUS = .2f;
static const float LIGHT_SPHERE_1_SEGMENTS = 20;
static const float LIGHT_SPHERE_1_RINGS = 20;
static const float LIGHT_SPHERE_1_ROT_SPEED = 0.02f;
static const glm::vec3 LIGHT_SPHERE_1_POSITION = glm::vec3(2.0f, 0.0f, 0.0f);
static const glm::vec4 LIGHT_SPHERE_1_EMMISION_COLOR = glm::vec4(.5f, .5f, .6f, .5f);

static const glm::vec3 LIGHT_SOURCE_1_DIFFUSE_COLOR = glm::vec3(.5f, .5f, .7f);
static const glm::vec3 LIGHT_SOURCE_1_SPECULAR_COLOR = glm::vec3(0.8f, .8f, 1.0f);

static const float LIGHT_SPHERE_2_RADIUS = .2f;
static const float LIGHT_SPHERE_2_SEGMENTS = 20;
static const float LIGHT_SPHERE_2_RINGS = 20;
static const float LIGHT_SPHERE_2_ROT_SPEED = 0.02f;
static const glm::vec3 LIGHT_SPHERE_2_POSITION = glm::vec3(4.0f, 0.0f, 0.0f);
static const glm::vec4 LIGHT_SPHERE_2_EMMISION_COLOR = glm::vec4(.5f, .5f, .5f, 1.0f);

static const glm::vec3 LIGHT_SOURCE_2_DIFFUSE_COLOR = glm::vec3(.5f, .5f, .5f);
static const glm::vec3 LIGHT_SOURCE_2_SPECULAR_COLOR = glm::vec3(.9f, .9f, .9f);

int main(int argc, char **argv)
{
    using namespace aur;


    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // TODO
    
    
    auto root_empty_obj = std::make_shared<Object>();
    
    // plane
    auto plane_geometry_data = geometry_generators::generate_plane_geometry_data(PLANE_WIDTH, PLANE_HEIGHT, PLANE_WIDTH_SEGMENTS, PLANE_HEIGHT_SEGMENTS);
    auto plane_geometry = std::make_shared<ES2Geometry>(plane_geometry_data.first, plane_geometry_data.second);
    auto plane_material = std::make_shared<ES2PhongMaterial>();
    plane_material->set_emission_color(PLANE_EMISSION_COLOR);
    plane_material->set_specular_exponent(PLANE_SPECULAR_EXPONENT);
    auto plane = std::make_shared<Mesh>(plane_geometry, plane_material, PLANE_POSITION);
    plane->set_rotation_x(plane->get_rotation_x() - (M_PI / 2.0f));
    

    // center sphere
    auto center_sphere_geometry_data = geometry_generators::generate_sphere_geometry_data(CENTER_SPHERE_RADIUS, CENTER_SPHERE_SEGMENTS, CENTER_SPHERE_RINGS);
    auto center_sphere_geometry = std::make_shared<ES2Geometry>(center_sphere_geometry_data.first, center_sphere_geometry_data.second);
//    center_sphere_geometry->set_type(Geometry::Type::TriangleFan);
    auto center_sphere_material = std::make_shared<ES2PhongMaterial>();
//    center_sphere_material->set_ambient_color(glm::vec3{0.5f});
    center_sphere_material->set_specular_exponent(CENTER_SPHERE_SPECULAR_EXPONENT);
    center_sphere_material->set_emission_color(glm::vec4{ CENTER_SPHERE_EMMISION_COLOR } );
    auto center_sphere = std::make_shared<Mesh>(center_sphere_geometry, center_sphere_material, CENTER_SPHERE_POSITION);
    
    auto light_source_0 = std::make_shared<PointLight>();
    light_source_0->set_diffuse_color(LIGHT_SOURCE_0_DIFFUSE_COLOR);
    light_source_0->set_specular_color(LIGHT_SOURCE_0_SPECULAR_COLOR);
    light_source_0->set_intensity(0.60f);
//    light_source_0->set_x(light_source_1->get_x() - .05f);

    
    // first light sphere
    auto light_sphere_1_empty_obj = std::make_shared<Object>();
    
    auto light_sphere_1_geometry_data = geometry_generators::generate_sphere_geometry_data(LIGHT_SPHERE_1_RADIUS, LIGHT_SPHERE_1_SEGMENTS, LIGHT_SPHERE_1_RINGS);
    auto light_sphere_1_geometry = std::make_shared<ES2Geometry>(light_sphere_1_geometry_data.first, light_sphere_1_geometry_data.second);
    auto light_sphere_1_material = std::make_shared<ES2PhongMaterial>();
//    light_sphere_1_material->set_specular_exponent(CENTER_SPHERE_SPECULAR_EXPONENT);
    light_sphere_1_material->set_emission_color(LIGHT_SPHERE_1_EMMISION_COLOR);
    auto light_sphere_1 = std::make_shared<Mesh>(light_sphere_1_geometry, light_sphere_1_material, LIGHT_SPHERE_1_POSITION);
    // first light source
    auto light_source_1 = std::make_shared<PointLight>();
    light_source_1->set_diffuse_color(LIGHT_SOURCE_1_DIFFUSE_COLOR);
    light_source_1->set_specular_color(LIGHT_SOURCE_1_SPECULAR_COLOR);
    light_source_1->set_intensity(0.45f);
    light_source_1->set_x(light_source_1->get_x() - .05f);
    
    // second light sphere
    auto light_sphere_2_empty_obj = std::make_shared<Object>();

    auto light_sphere_2_geometry_data = geometry_generators::generate_sphere_geometry_data(LIGHT_SPHERE_2_RADIUS, LIGHT_SPHERE_2_SEGMENTS, LIGHT_SPHERE_2_RINGS);
    auto light_sphere_2_geometry = std::make_shared<ES2Geometry>(light_sphere_2_geometry_data.first, light_sphere_2_geometry_data.second);
    auto light_sphere_2_material = std::make_shared<ES2PhongMaterial>();
    light_sphere_2_material->set_emission_color(LIGHT_SPHERE_2_EMMISION_COLOR);
    auto light_sphere_2 = std::make_shared<Mesh>(light_sphere_2_geometry, light_sphere_2_material, LIGHT_SPHERE_2_POSITION);
    // second light source
    auto light_source_2 = std::make_shared<PointLight>();
    light_source_2->set_diffuse_color(LIGHT_SOURCE_2_DIFFUSE_COLOR);
    light_source_2->set_specular_color(LIGHT_SOURCE_2_SPECULAR_COLOR);
    light_source_2->set_intensity(0.36f);
    light_source_2->set_x(light_source_2->get_x() - .05f);
    
    // parenting
    root_empty_obj->add_child(center_sphere);
    root_empty_obj->add_child(plane);
    root_empty_obj->add_child(light_source_0);
    center_sphere->add_child(light_sphere_1_empty_obj);
    center_sphere->add_child(light_sphere_2_empty_obj);
    
    light_sphere_1_empty_obj->add_child(light_sphere_1);
    light_sphere_2_empty_obj->add_child(light_sphere_2);
    
    light_sphere_1->add_child(light_source_1);
    light_sphere_2->add_child(light_source_2);
    
    
    std::vector<std::shared_ptr<Object>> objects{ root_empty_obj };
    auto scene = std::make_shared<Scene>(objects);
   
 
    auto camera = scene->get_camera();
    camera->set_z(7.0f);
    camera->set_y(7.0f);
    camera->set_rotation_x(-.8f);
 
    scene->get_point_lights().clear();
    scene->get_directional_lights().clear();
 
    scene->get_point_lights().push_back(light_source_0);
    scene->get_point_lights().push_back(light_source_1);
    scene->get_point_lights().push_back(light_source_2);
 
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
 
        renderer.render();
        
        light_sphere_1_empty_obj->set_rotation_y(light_sphere_1_empty_obj->get_rotation_y() - LIGHT_SPHERE_1_ROT_SPEED);
        light_sphere_2_empty_obj->set_rotation_y(light_sphere_2_empty_obj->get_rotation_y() + LIGHT_SPHERE_2_ROT_SPEED);
    }
}
