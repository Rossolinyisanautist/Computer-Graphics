#include "aur.hpp"
#include "Monster.h"
#include "Gun.h"
#include <chrono>

using namespace aur;

static const float CAMERA_SPEED{0.3f};
static const float CAMERA_SENSITIVITY{0.001f};

static const int SPRITE_FRAMES{ 11 };
static const int SPRITE_DYING_STARTING_FRAME{ 4 };

static const int ENEMY_SIZE{ 6 };
static const float ENEMY_SPEED{ 0.04f };

const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};
const glm::vec4 RIGHT{1.0f, 0.0f, 0.0f, 0.0f};


[[noreturn]]
int main(int argc, char **argv)
{
    // Window

    auto window = std::make_shared<SDLWindow>("DOOM", 1280, 720);
    window->set_capture_mouse_enabled(true);
    window->set_relative_mouse_mode_enabled(true);

    // Ground

    auto[room_ground_indices, room_ground_vertices] = geometry_generators::generate_plane_geometry_data(50, 50, 1, 1);
    auto room_ground_geometry = std::make_shared<ES2Geometry>(room_ground_indices, room_ground_vertices);
    auto room_ground_material = std::make_shared<ES2PhongMaterial>();
    auto [image0_data, image0_width, image0_height, image0_channels] = file_utilities::read_image_file("data/images/city.jpg");
    auto texture_ground = std::make_shared<ES2Texture>(image0_data, image0_width, image0_height, image0_channels);

    Texture::WrapMode texture1_wrap_mode_s{ Texture::WrapMode::Repeat };
    Texture::WrapMode texture1_wrap_mode_t{ Texture::WrapMode::Repeat };
    texture_ground->set_transformation_enabled(true);
    glm::mat4 texture1_transformation_matrix{ glm::vec4{15.0, 0.0, 0.0, 0.0}, glm::vec4{0.0, 15.0, 0.0, 0.0} ,
                                              glm::vec4{0.0, 0.0, 1.0, 0.0} , glm::vec4{0.0, 0.0, 0.0, 1.0} };
    texture_ground->set_wrap_mode_s(texture1_wrap_mode_s);
    texture_ground->set_wrap_mode_t(texture1_wrap_mode_t);
    texture_ground->set_transformation_matrix(texture1_transformation_matrix);


    room_ground_material->set_texture_1(texture_ground);
    room_ground_material->set_specular_exponent(1.0f);
    room_ground_material->set_specular_color(glm::vec3{0.0f});
    room_ground_material->set_diffuse_color(glm::vec4{0.25f});
    auto room_ground = std::make_shared<Mesh>(room_ground_geometry, room_ground_material);
    room_ground->set_position(glm::vec3(0.0f, -2.5f, 0.0f));
    room_ground->set_rotation(glm::vec3(-M_PI / 2.0f, 0.0f, 0.0f));

    // Monsters

    auto enemy1 = std::make_shared<Monster>(glm::vec3(-5.0f, 1.0f, 2.0f), ENEMY_SIZE, ENEMY_SPEED,
                                          std::make_tuple("data/images/heads.png", SPRITE_FRAMES, SPRITE_DYING_STARTING_FRAME));
    auto enemy2 = std::make_shared<Monster>(glm::vec3(5.0f, 1.0f, 0.0f), ENEMY_SIZE, ENEMY_SPEED,
                                          std::make_tuple("data/images/heads.png", SPRITE_FRAMES, SPRITE_DYING_STARTING_FRAME));

    auto enemy3 = std::make_shared<Monster>(glm::vec3(0.0f, 1.0f, 3.0f), ENEMY_SIZE, ENEMY_SPEED,
                                          std::make_tuple("data/images/heads.png", SPRITE_FRAMES, SPRITE_DYING_STARTING_FRAME));

    // Enemies vector

    std::vector<std::shared_ptr<Monster>> enemies{ enemy1, enemy2 };

    // Gun

    Gun gun{ glm::vec3(0.0f, -2.0f, 0.0f), 3, std::make_tuple("data/images/guns.png", 6, 1) };

    // Lamps

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.2f, 20, 20);
    auto lamp_sphere_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp3 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp4 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);

    // Front wall

    auto [plane1_indices, plane1_vertices] = geometry_generators::generate_plane_geometry_data(50, 20, 2, 2);
    auto plane1_geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
    auto plane1_material = std::make_shared<ES2PhongMaterial>();
    auto [image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/city.jpg");
    auto texture1 = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    glm::mat4 texture1_transformation_matrix2{ glm::vec4{8.0, 0.0, 0.0, 0.0}, glm::vec4{0.0, 4.0, 0.0, 0.0} ,
                                               glm::vec4{0.0, 0.0, 1.0, 0.0} , glm::vec4{0.0, 0.0, 0.0, 1.0} };
    texture1->set_transformation_enabled(true);
    texture1->set_wrap_mode_s(Texture::WrapMode::Repeat);
    texture1->set_wrap_mode_t(Texture::WrapMode::Repeat);
    texture1->set_transformation_matrix(texture1_transformation_matrix2);
    plane1_material->set_texture_1(texture1);
    plane1_material->set_specular_exponent(20.0f);
    auto plane1 = std::make_shared<Mesh>(plane1_geometry, plane1_material);
    plane1->set_position(glm::vec3(0.0f, 0.0f, -25.0f));

    // Right wall

    auto [plane2_indices, plane2_vertices] = geometry_generators::generate_plane_geometry_data(50, 20, 2, 2);
    auto plane2_geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
    auto plane2_material = std::make_shared<ES2PhongMaterial>();
    plane2_material->set_texture_1(texture1);
    plane2_material->set_specular_exponent(20.0f);
    auto plane2 = std::make_shared<Mesh>(plane2_geometry, plane2_material);
    plane2->set_rotation(glm::vec3(0.0f, -M_PI / 2.0f, 0.0f));
    plane2->set_position(glm::vec3(25.0f, 0.0f, 0.0f));

    // Left wall

    auto [plane3_indices, plane3_vertices] = geometry_generators::generate_plane_geometry_data(50, 20, 2, 2);
    auto plane3_geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
    auto plane3_material = std::make_shared<ES2PhongMaterial>();
    plane3_material->set_texture_1(texture1);
    plane3_material->set_specular_exponent(20.0f);
    auto plane3 = std::make_shared<Mesh>(plane3_geometry, plane3_material);
    plane3->set_rotation(glm::vec3(0.0f, M_PI / 2.0f, 0.0f));
    plane3->set_position(glm::vec3(-25.0f, 0.0f, 0.0f));

    // Back wall

    auto [plane4_indices, plane4_vertices] = geometry_generators::generate_plane_geometry_data(50, 20, 2, 2);
    auto plane4_geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
    auto plane4_material = std::make_shared<ES2PhongMaterial>();
    plane4_material->set_texture_1(texture1);
    plane4_material->set_specular_exponent(20.0f);
    auto plane4 = std::make_shared<Mesh>(plane4_geometry, plane4_material);
    plane4->set_rotation(glm::vec3(0.0f, -M_PI, 0.0f));
    plane4->set_position(glm::vec3(0.0f, 0.0f, 25.0f));

    // Ceiling

    auto [plane5_indices, plane5_vertices] = geometry_generators::generate_plane_geometry_data(50, 50, 1, 1);
    auto plane5_geometry = std::make_shared<ES2Geometry>(plane5_indices, plane5_vertices);
    auto plane5_material = std::make_shared<ES2PhongMaterial>();
    auto [image5_data, image5_width, image5_height, image5_channels] = file_utilities::read_image_file("data/images/city.jpg");
    auto texture_ceiling = std::make_shared<ES2Texture>(image5_data, image5_width, image5_height, image5_channels);
    texture_ceiling->set_wrap_mode_s(Texture::WrapMode::Repeat);
    texture_ceiling->set_wrap_mode_t(Texture::WrapMode::Repeat);
    texture_ceiling->set_transformation_enabled(true);
    texture_ceiling->set_transformation_matrix(texture1_transformation_matrix2);
    plane5_material->set_texture_1(texture_ceiling);
    plane5_material->set_specular_exponent(20.0f);
    auto plane5 = std::make_shared<Mesh>(plane5_geometry, plane5_material);
    plane5->set_position(glm::vec3(0.0f, 10.0f, 0.0f));
    plane5->set_rotation(glm::vec3(M_PI / 2.0f, 0.0f, 0.0f));

    // Objects vector

    std::vector<std::shared_ptr<Object>> objects{room_ground, enemy1->get_mesh(), enemy2->get_mesh(),
                                                 gun.get_mesh(),
                                                 plane1, plane2, plane3, plane4, plane5 };
    auto scene = std::make_shared<Scene>(objects);

    // Point Lights

    auto point_light1 = std::make_shared<PointLight>();
    point_light1->set_intensity(4000.0f);
    point_light1->set_constant_attenuation(0.0f);
    point_light1->set_linear_attenuation(0.2f);
    point_light1->set_quadratic_attenuation(0.8f);
    point_light1->set_two_sided(true);
    point_light1->set_position(glm::vec3(-25.0f, 4.0f, 25.0f));
    point_light1->add_child(lamp1);
    scene->get_root()->add_child(point_light1);
    scene->get_point_lights().push_back(point_light1);

    auto point_light2 = std::make_shared<PointLight>();
    point_light2->set_intensity(4000.0f);
    point_light2->set_constant_attenuation(0.0f);
    point_light2->set_linear_attenuation(0.2f);
    point_light2->set_quadratic_attenuation(0.8f);
    point_light2->set_two_sided(true);
    point_light2->set_position(glm::vec3(25.0f, 4.0f, 25.0f));
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light2);

    auto point_light3 = std::make_shared<PointLight>();
    point_light3->set_intensity(4000.0f);
    point_light3->set_constant_attenuation(0.0f);
    point_light3->set_linear_attenuation(0.2f);
    point_light3->set_quadratic_attenuation(0.8f);
    point_light3->set_two_sided(true);
    point_light3->set_position(glm::vec3(25.0f, 4.0f, -25.0f));
    point_light3->add_child(lamp3);
    scene->get_root()->add_child(point_light3);
    scene->get_point_lights().push_back(point_light3);

    auto point_light4 = std::make_shared<PointLight>();
    point_light4->set_intensity(4000.0f);
    point_light4->set_constant_attenuation(0.0f);
    point_light4->set_linear_attenuation(0.2f);
    point_light4->set_quadratic_attenuation(0.8f);
    point_light4->set_two_sided(true);
    point_light4->set_position(glm::vec3(-25.0f, 4.0f, -25.0f));
    point_light4->add_child(lamp4);
    scene->get_root()->add_child(point_light4);
    scene->get_point_lights().push_back(point_light4);

    // Camera

    auto camera = scene->get_camera();
    camera->set_position(glm::vec3(0.0f, 0.0f, 20.0f));
    camera->set_zoom(3.0f);

    enemy1->set_target(camera);
    enemy2->set_target(camera);


    // Input

    window->set_on_key_down([&](int key) {
        glm::mat4 model_matrix = camera->get_model_matrix();

        switch (key) {
            case SDLK_w: camera->add_to_position(-glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)); break;
            case SDLK_a: camera->add_to_position(-glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)); break;
            case SDLK_s: camera->add_to_position(glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)); break;
            case SDLK_d: camera->add_to_position(glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)); break;
            case SDLK_e: camera->add_to_y(CAMERA_SPEED); break;
            case SDLK_q: camera->add_to_y(-CAMERA_SPEED); break;
            case SDLK_ESCAPE: exit(0);
            default: break;
        }
    });

    window->set_on_mouse_move([&](int x, int y, int x_rel, int y_rel) {
        camera->add_to_rotation_y(static_cast<float>(-x_rel)* CAMERA_SENSITIVITY);
    });

    window->set_on_mouse_down([&](int button, int x, int y) {
        int cx = static_cast<int>(window->get_width() / 2);
        int cy = static_cast<int>(window->get_height() / 2);
        Ray ray = camera->world_ray_from_screen_point(cx, cy, static_cast<int>(window->get_width()), static_cast<int>(window->get_height()));

        gun.shoot();

        for (auto &enemy : enemies) {
            if (enemy->intersects_with_ray(ray)) {
                enemy->kill();
            }
        }

    });

    // Rendering

    auto prev_frame_time = std::chrono::high_resolution_clock::now();

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        auto current_frame_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> time_span = current_frame_time - prev_frame_time;
        float delta_time = time_span.count() / 1000.0f;

        gun.update();

        for (auto &enemy : enemies) {
            enemy->update(delta_time);
        }

        renderer.render();
        //prev_frame_time = current_frame_time;
    }
}
