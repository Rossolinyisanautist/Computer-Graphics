//
//  scene_graph_test.cpp
//  scene_graph_test
//
//  Created by Isa on 3/8/20.
//

#include "aur.hpp"
#include <chrono>

// TODO: Extract other constants !

static const float CAMERA_ROT_SPEED = 0.03f;
static const float CAMERA_SPEED = 0.5f;

static const glm::vec4 FORWARD = { .0f, .0f, 1.0f, .0f};

static const float ROOT_ROTATION_SPEED = 0.01f;

static const float ROOT_SPHERE_RADIUS = 1.0f;
static const int ROOT_SPHERE_SEGMENTS = 10;
static const int ROOT_SPHERE_RINGS = 10;
static const glm::vec4 ROOT_SPHERE_COLOR = {1.0f, 0.0f, 0.0f, 1.0f};

static const float MIN_SEC_POINTS_AMOUNT = 60.0f;
static const float MIN_SEC_POINTS_RADIUS = 0.25f;
static const int MIN_SEC_POINTS_SEGMENTS = 5;
static const int MIN_SEC_POINTS_RINGS = 5;

static const float CLOCK_RADIUS = 34.0f;

static const float SEC_ARROW_WIDTH = .3f;
static const float MIN_ARROW_WIDTH = SEC_ARROW_WIDTH * 2;
static const float HOUR_ARROW_WIDTH = SEC_ARROW_WIDTH * 3;

static const float SEC_ARROW_STEP = (2.0f * M_PI) / (MIN_SEC_POINTS_AMOUNT);
static const float MIN_ARROW_STEP = SEC_ARROW_STEP / MIN_SEC_POINTS_AMOUNT;
static const float HOUR_ARROW_STEP = MIN_ARROW_STEP / 12.0f;

int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // TODO
    
    auto root_object = std::make_shared<Object>();
    
    // sphere
    auto sphere_geometry_data = geometry_generators::generate_sphere_geometry_data(ROOT_SPHERE_RADIUS, ROOT_SPHERE_RINGS, ROOT_SPHERE_SEGMENTS);
    auto sphere_geometry = std::make_shared<ES2Geometry>(sphere_geometry_data.first, sphere_geometry_data.second);
    sphere_geometry->set_type(Geometry::Type::TriangleFan);
    auto sphere_material = std::make_shared<ES2ConstantMaterial>();
    sphere_material->set_emission_color( ROOT_SPHERE_COLOR );
    auto sphere_mesh = std::make_shared<Mesh>(sphere_geometry, sphere_material, glm::vec3{0.0f, 0.0f, 0.0f} );
    sphere_mesh->set_scale( glm::vec3{.5f} );
    
    // arrow material
    auto arrow_material = std::make_shared<ES2ConstantMaterial>();
    arrow_material->set_emission_color(glm::vec4{1.0f, .0f, .0f, 1.0f} );

    // sec arrow
    auto sec_arrow_geometry_data = geometry_generators::generate_plane_geometry_data(SEC_ARROW_WIDTH, CLOCK_RADIUS - 2.0f, 1.0f, 10);
    auto sec_arrow_geometry = std::make_shared<ES2Geometry>(sec_arrow_geometry_data.first, sec_arrow_geometry_data.second);
    sec_arrow_geometry->set_type(Geometry::Type::TriangleFan);
    auto sec_arrow_mesh = std::make_shared<Mesh>(sec_arrow_geometry, arrow_material, glm::vec3{.0f, 17.0f, .0f});
    
    auto sec_empty_object = std::make_shared<Object>();
    
    // min arrow
    auto min_arrow_geometry_data = geometry_generators::generate_plane_geometry_data(MIN_ARROW_WIDTH, CLOCK_RADIUS * 2.0f / 3.0f, 1.0f, 10);
    auto min_arrow_geometry = std::make_shared<ES2Geometry>(min_arrow_geometry_data.first, min_arrow_geometry_data.second);
    min_arrow_geometry->set_type(Geometry::Type::TriangleFan);
    auto min_arrow_mesh = std::make_shared<Mesh>(min_arrow_geometry, arrow_material, glm::vec3{.0f, (34.0 * 2.0f / 3.0f) / 2.0f, .0f});
    
    auto min_empty_object = std::make_shared<Object>();
    
    // hour arrow
    auto hour_arrow_geometry_data = geometry_generators::generate_plane_geometry_data(HOUR_ARROW_WIDTH, CLOCK_RADIUS / 3.0f, 1.0f, 10);
    auto hour_arrow_geometry = std::make_shared<ES2Geometry>(hour_arrow_geometry_data.first, hour_arrow_geometry_data.second);
    hour_arrow_geometry->set_type(Geometry::Type::TriangleFan);
    auto hour_arrow_mesh = std::make_shared<Mesh>(hour_arrow_geometry, arrow_material, glm::vec3{.0f, (34.0f / 3.0f) / 2.0f, .0f});
    
    auto hour_empty_object = std::make_shared<Object>();
    
    // relations
    root_object->add_child(sphere_mesh);
    sphere_mesh->add_child(sec_empty_object);
    sphere_mesh->add_child(min_empty_object);
    sphere_mesh->add_child(hour_empty_object);
    
    sec_empty_object->add_child(sec_arrow_mesh);
    min_empty_object->add_child(min_arrow_mesh);
    hour_empty_object->add_child(hour_arrow_mesh);
    
    min_empty_object->set_rotation_z(min_empty_object->get_z() + 5.0f);
    hour_empty_object->set_rotation_z(hour_empty_object->get_z() - 5.0f);
    // min/sec points
    auto point_geometry_data = geometry_generators::generate_sphere_geometry_data(MIN_SEC_POINTS_RADIUS, MIN_SEC_POINTS_SEGMENTS, MIN_SEC_POINTS_RINGS);
    auto point_geometry = std::make_shared<ES2Geometry>(point_geometry_data.first, point_geometry_data.second);
    point_geometry->set_type(Geometry::Type::LineLoop);
    auto point_material = std::make_shared<ES2ConstantMaterial>();
    point_material->set_emission_color(glm::vec4 {.5f, .5f, .5f, 1.0f} );
    
    // hour points
    auto hour_point_geometry_data = geometry_generators::generate_plane_geometry_data(.7f, .7f, 1, 1);
    auto hour_point_geometry = std::make_shared<ES2Geometry>(hour_point_geometry_data.first, hour_point_geometry_data.second);
    hour_point_geometry->set_type(Geometry::Type::TriangleFan);
    auto hour_point_material = std::make_shared<ES2ConstantMaterial>();
    hour_point_material->set_emission_color(glm::vec4 {1.0f, .5f, .5f, 0.0f} );
    
    // mid points
    auto mid_point_geometry_data = geometry_generators::generate_plane_geometry_data(1.5f, 1.5f, 1, 1);
    auto mid_point_geometry = std::make_shared<ES2Geometry>(mid_point_geometry_data.first, mid_point_geometry_data.second);
    mid_point_geometry->set_type(Geometry::Type::TriangleFan);
    auto mid_point_material = std::make_shared<ES2ConstantMaterial>();
    mid_point_material->set_emission_color(glm::vec4 {1.0f, .0f, .0f, 0.0f} );
    
    
    for (int i = 0; i < (int) MIN_SEC_POINTS_AMOUNT; i++) {
        float angle = ((2.0f * M_PI) / MIN_SEC_POINTS_AMOUNT) * i;
        float cos = cosf(angle);
        float sin = sinf(angle);
        
        if(i % 5 == 0) {
            float x = cos * CLOCK_RADIUS / 1.85f;
            float y = sin * CLOCK_RADIUS / 1.85f;
            auto hour_point_mesh = std::make_shared<Mesh>(hour_point_geometry, hour_point_material, glm::vec3{x, y, -0.2f});
            hour_point_mesh->set_rotation_z(hour_point_mesh->get_rotation_z() + M_PI / 4.0f);
            root_object->add_child(hour_point_mesh);
        }
        
        if(i % 15 == 0) {
            float x = cos * CLOCK_RADIUS / 1.85f;
            float y = sin * CLOCK_RADIUS / 1.85f;
            auto mid_point_mesh = std::make_shared<Mesh>(mid_point_geometry, mid_point_material, glm::vec3{x, y, -1.0f});
            mid_point_mesh->set_rotation_z(mid_point_mesh->get_rotation_z() + M_PI / 4.0f);
            root_object->add_child(mid_point_mesh);
        }
        
        float x = cos * CLOCK_RADIUS / 2.0f;
        float y = sin * CLOCK_RADIUS / 2.0f;
        auto point_mesh = std::make_shared<Mesh>(point_geometry, point_material, glm::vec3{x, y, .0f});
        root_object->add_child(point_mesh);
    }

    std::vector<std::shared_ptr<Object>> objects { root_object };
    auto scene = std::make_shared<Scene>(objects);
    
    auto camera = scene->get_camera();
    camera->set_z(40.0f);

    window->set_on_key([&](int key) {
        switch (key) {
            case SDLK_w: camera->set_rotation_x(camera->get_rotation_x() + CAMERA_ROT_SPEED); break;
            case SDLK_a: camera->set_rotation_y(camera->get_rotation_y() + CAMERA_ROT_SPEED); break;
            case SDLK_s: camera->set_rotation_x(camera->get_rotation_x() - CAMERA_ROT_SPEED); break;
            case SDLK_d: camera->set_rotation_y(camera->get_rotation_y() - CAMERA_ROT_SPEED); break;
            case SDLK_e: camera->set_y(camera->get_y() + CAMERA_ROT_SPEED); break;
            case SDLK_q: camera->set_y(camera->get_y() - CAMERA_ROT_SPEED); break;
            case SDLK_UP: camera->set_position(camera->get_position() - glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_DOWN: camera->set_position(camera->get_position() + glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_ESCAPE: exit(0); break;
            default: break;
        }
    });
    
    ES2Renderer renderer(scene, window);
    
    int sec_prev = 0;
    
    while (true) {
        window->poll();
        
        std::time_t total_seconds = time(0);

        int seconds = localtime(&total_seconds)->tm_sec;

        if(seconds == sec_prev + 1 || (sec_prev == 59 && seconds == 0))
        {
//            system("CLS");
            sec_empty_object->set_rotation_z(sec_empty_object->get_rotation_z() - SEC_ARROW_STEP);
            min_empty_object->set_rotation_z(min_empty_object->get_rotation_z() - MIN_ARROW_STEP);
            hour_empty_object->set_rotation_z(hour_empty_object->get_rotation_z() - HOUR_ARROW_STEP);
        }
        sec_prev = seconds;
        root_object->set_rotation_y(root_object->get_rotation_y() + ROOT_ROTATION_SPEED);
        renderer.render();
    }
}
