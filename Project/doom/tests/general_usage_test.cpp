#include "aur.hpp"
#include "entities/monster.h"
#include "entities/weapon.h"
#include "objects/wall.h"
#include "objects/lamp.h"
#include <chrono>

using namespace aur;

static const float CAMERA_SPEED{0.3f};
static const float CAMERA_SENSITIVITY{0.001f};

static const int SPRITE_FRAMES{ 11 };
static const int SPRITE_DYING_STARTING_FRAME{ 4 };

static const int MONSTER_SIZE{6 };
static const float MONSTER_MOVEMENT_SPEED{0.02f };

static const float WALL_WIDTH = 50.0f;
static const float WALL_HEIGHT = 12.5f;
static const float WALL_Y_SHIFT = 3.75f;

static const std::string WALL_TEXTURE_FILE = "data/images/WALL_4.png";
static const std::string FLOOR_TEXTURE_FILE = "data/images/CEILING.png";
static const std::string CEILING_TEXTURE_FILE = "data/images/CEILING.png";

static const std::string WALL_TEXTURE_NORMALS_FILE = "data/images/texture_nosrmals.png";
static const std::string FLOOR_TEXTURE_NORMALS_FILE = "data/images/texture_nosrmals.png";
static const std::string CEILING_TEXTURE_NORMALS_FILE = "data/images/texture_nosrmals.png";


const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};
const glm::vec4 RIGHT{1.0f, 0.0f, 0.0f, 0.0f};

[[noreturn]]
int main(int argc, char **argv)
{
    // Window
    auto window = std::make_shared<SDLWindow>("DOOM (NOT) ETERNAL", 1280, 720);
    window->set_capture_mouse_enabled(true);
    window->set_relative_mouse_mode_enabled(true);

    // Ground
    glm::mat4 texture1_transformation_matrix{ glm::vec4{15.0, 0.0, 0.0, 0.0}, glm::vec4{0.0, 15.0, 0.0, 0.0} ,
                                              glm::vec4{0.0, 0.0, 1.0, 0.0} , glm::vec4{0.0, 0.0, 0.0, 1.0} };
    auto floor = std::make_shared<Wall>(FLOOR_TEXTURE_FILE, glm::vec3(0.0f, -2.5f, 0.0f), 50, 50);
    floor->set_rotation(glm::vec3(.0f, -M_PI / 2.0f, 0.0f));
    floor->set_specular_exponent(1.0f);
    floor->set_specular_color(glm::vec3{0.5f});
    floor->set_diffuse_color(glm::vec4{0.5f});
    floor->set_transformation_matrix(texture1_transformation_matrix);

    // Walls
    auto front_wall = std::make_shared<Wall>(WALL_TEXTURE_FILE, glm::vec3(0.0f, WALL_Y_SHIFT, -25.0f), WALL_WIDTH, WALL_HEIGHT);
    auto right_wall = std::make_shared<Wall>(WALL_TEXTURE_FILE, glm::vec3(25.0f, WALL_Y_SHIFT, 0.0f), WALL_WIDTH, WALL_HEIGHT);
    right_wall->set_rotation(glm::vec3(-M_PI / 2.0f, .0f, .0f));

    auto left_wall = std::make_shared<Wall>(WALL_TEXTURE_FILE, glm::vec3(-25.0f, WALL_Y_SHIFT, 0.0f), WALL_WIDTH, WALL_HEIGHT);
    left_wall->set_rotation(glm::vec3(M_PI / 2.0f, .0f, .0f));

    auto back_wall = std::make_shared<Wall>(WALL_TEXTURE_FILE, glm::vec3(0.0f, WALL_Y_SHIFT, 25.0f), WALL_WIDTH, WALL_HEIGHT);
    back_wall->set_rotation(glm::vec3(0.0f, -M_PI, 0.0f));

    auto ceiling = std::make_shared<Wall>(CEILING_TEXTURE_FILE, glm::vec3(0.0f, 10.0f, 0.0f), 50, 50);
    ceiling->set_rotation(glm::vec3(0.0f, M_PI / 2.0f, 0.0f));

    // Monsters
    auto monster_1 = std::make_shared<Monster>(glm::vec3(-15.0f, -.5f, 2.0f), MONSTER_SIZE, MONSTER_MOVEMENT_SPEED,
                                               std::make_tuple("data/images/heads.png", SPRITE_FRAMES, SPRITE_DYING_STARTING_FRAME));
    auto monster_2 = std::make_shared<Monster>(glm::vec3(5.0f, -.5f, 0.0f), MONSTER_SIZE, MONSTER_MOVEMENT_SPEED,
                                               std::make_tuple("data/images/heads.png", SPRITE_FRAMES, SPRITE_DYING_STARTING_FRAME));
    auto monster_3 = std::make_shared<Monster>(glm::vec3(10.0f, -.5f, 6.0f), MONSTER_SIZE, MONSTER_MOVEMENT_SPEED,
                                               std::make_tuple("data/images/heads.png", SPRITE_FRAMES, SPRITE_DYING_STARTING_FRAME));

    std::vector<std::shared_ptr<Monster>> enemies{monster_1, monster_2, monster_3 };

     auto weapon = std::make_shared<Weapon>( glm::vec3(0.0f, -2.0f, 0.0f), 3, std::make_tuple("data/images/guns.png", 6, 1) );

    // Scene Objects
    std::vector<std::shared_ptr<Object>> objects{
            floor->get_mesh(),
            monster_1->get_mesh(),
            monster_2->get_mesh(),
            monster_3->get_mesh(),
            weapon->get_mesh(),
            front_wall->get_mesh(),
            left_wall->get_mesh(),
            right_wall->get_mesh(),
            back_wall->get_mesh(),
            ceiling->get_mesh()
    };
    auto scene = std::make_shared<Scene>(objects);

    // Light
    auto lamp_obj_1 = std::make_shared<Lamp>(
            0.2f, 4000.0f, 0.0f, 0.2f, 0.8f, true, glm::vec3(-25.0f, 0.0f, -25.0f));
    auto lamp_obj_2 = std::make_shared<Lamp>(
            0.2f, 4000.0f, 0.0f, 0.2f, 0.8f, true, glm::vec3(25.0f, 0.0f, -25.0f));
    auto lamp_obj_3 = std::make_shared<Lamp>(
            0.2f, 4000.0f, 0.0f, 0.2f, 0.8f, true, glm::vec3(25.0f, 0.0f, 25.0f));
    auto lamp_obj_4 = std::make_shared<Lamp>(
            0.2f, 4000.0f, 0.0f, 0.2f, 0.8f, true, glm::vec3(-25.0f, 0.0f, 25.0f));

    lamp_obj_3->make_child_of(scene);
    lamp_obj_2->make_child_of(scene);
    lamp_obj_1->make_child_of(scene);
    lamp_obj_4->make_child_of(scene);

    // Camera
    auto camera = scene->get_camera();
    camera->set_position(glm::vec3(0.0f, 0.0f, 20.0f));
    camera->set_zoom(3.0f);

    monster_1->set_target(camera);
    monster_2->set_target(camera);
    monster_3->set_target(camera);


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
        camera->add_to_rotation_x(static_cast<float>(-x_rel)* CAMERA_SENSITIVITY);
        camera->add_to_rotation_y(static_cast<float>(-y_rel)* CAMERA_SENSITIVITY);
    });

    window->set_on_mouse_down([&](int button, int x, int y) {
        int cx = static_cast<int>(window->get_width() / 2);
        int cy = static_cast<int>(window->get_height() / 2);
        Ray ray = camera->world_ray_from_screen_point(cx, cy, static_cast<int>(window->get_width()), static_cast<int>(window->get_height()));

        weapon->shoot_animation();

        for (auto &enemy : enemies) {
            if (enemy->intersects_with_ray(ray)) {
                enemy->die();
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

        weapon->update();

        for (auto &enemy : enemies) {
            enemy->update(delta_time);
        }

        renderer.render();
    }
}
