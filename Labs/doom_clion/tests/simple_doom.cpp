#include "aur.hpp"

const static float CAMERA_SPEED = 0.5f;
const static float CAMERA_ROT_SPEED = .05f;
const static float PLANE_ROT_SPEED = .001f;
const static float MOUSE_SENCITIVITY = .001f;

// TODO: add backward&left
const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};
const glm::vec4 RIGHT{1.0f, 0.0f, 0.0f, 0.0f};
const glm::vec4 UP{0.0f, 1.0f, 0.0f, 0.0f};

[[noreturn]]
int main(int argc, char** argv) {
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // Room Ground

    auto[room_ground_indices, room_ground_vertices] = geometry_generators::generate_plane_geometry_data(50, 50, 2, 2);
    auto room_ground_geometry = std::make_shared<ES2Geometry>(room_ground_indices, room_ground_vertices);
    auto room_ground_material = std::make_shared<ES2PhongMaterial>();
    room_ground_material-> set_specular_exponent(1.0f);
    room_ground_material-> set_specular_color(glm::vec3{0.0f});
    room_ground_material-> set_diffuse_color(glm::vec4{0.25f});
    auto room_ground = std::make_shared<Mesh>(room_ground_geometry, room_ground_material);
    room_ground-> set_position(glm::vec3(0.0f, -2.5f, 0.0f));
    room_ground-> set_rotation(glm::vec3(-M_PI / 2.0f, 0.0f, 0.0f));

    // Billboard

    auto[billboard_indices, billboard_vertices] = geometry_generators::generate_plane_geometry_data(9, 9, 2, 2);
    for(auto &vertex : billboard_vertices) {
        vertex.color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    auto billboard_geometry = std::make_shared<ES2Geometry>(billboard_indices, billboard_vertices);
    auto billboard_material = std::make_shared<ES2ConstantMaterial>();
    // TODO: Add image
    auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/city.jpg");
    auto texture1 = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    // сглаживание
    texture1-> set_minification_filter(Texture::FilterType::Nearest);
    texture1-> set_magnification_filter(Texture::FilterType::Nearest);
    texture1-> set_mode(Texture::Mode::Addition);
    billboard_material-> set_texture_1(texture1);
    billboard_material-> set_face_culling_enabled(false);
    auto billboard = std::make_shared<Mesh>(billboard_geometry, billboard_material);
    billboard-> set_position(glm::vec3(0.0f, 2.5f, 0.0f));
    billboard-> set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
    billboard-> set_billboard(true );

    // Lamps

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.2f, 20, 20);
    auto lamp_sphere_geomerty = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geomerty, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geomerty, lamp_material);
    auto lamp3 = std::make_shared<Mesh>(lamp_sphere_geomerty, lamp_material);
    auto lamp4 = std::make_shared<Mesh>(lamp_sphere_geomerty, lamp_material);

    std::vector<std::shared_ptr<Object>> objects{room_ground, billboard};
    auto scene = std::make_shared<Scene>(objects);

    // Point Lights

    auto point_light1 = std::make_shared<PointLight>();
    point_light1-> set_intensity(4000.0f);
    point_light1-> set_constant_attenuation(0.0f);
    point_light1-> set_linear_attenuation(0.2f);
    point_light1-> set_quadratic_attenuation(0.8f);
    point_light1-> set_two_sided(true);
    point_light1-> set_position(glm::vec3(-25.0f, 4.0f, 25.0f));
    point_light1-> add_child(lamp1);
    scene-> get_root()-> add_child(point_light1);
    scene-> get_point_lights().push_back(point_light1);

    auto point_light2 = std::make_shared<PointLight>();
    point_light2-> set_intensity(4000.0f);
    point_light2-> set_constant_attenuation(0.0f);
    point_light2-> set_linear_attenuation(0.2f);
    point_light2-> set_quadratic_attenuation(0.8f);
    point_light2-> set_two_sided(true);
    point_light2-> set_position(glm::vec3(25.0f, 4.0f, 25.0f));
    point_light2-> add_child(lamp2);
    scene-> get_root()-> add_child(point_light2);
    scene-> get_point_lights().push_back(point_light2);

    auto point_light3 = std::make_shared<PointLight>();
    point_light3-> set_intensity(4000.0f);
    point_light3-> set_constant_attenuation(0.0f);
    point_light3-> set_linear_attenuation(0.2f);
    point_light3-> set_quadratic_attenuation(0.8f);
    point_light3-> set_two_sided(true);
    point_light3-> set_position(glm::vec3(25.0f, 4.0f, -25.0f));
    point_light3-> add_child(lamp3);
    scene-> get_root()-> add_child(point_light3);
    scene-> get_point_lights().push_back(point_light3);

    auto point_light4 = std::make_shared<PointLight>();
    point_light4-> set_intensity(4000.0f);
    point_light4-> set_constant_attenuation(0.0f);
    point_light4-> set_linear_attenuation(0.2f);
    point_light4-> set_quadratic_attenuation(0.8f);
    point_light4-> set_two_sided(true);
    point_light4-> set_position(glm::vec3(-25.0f, 4.0f, -25.0f));
    point_light4-> add_child(lamp4);
    scene-> get_root()-> add_child(point_light4);
    scene-> get_point_lights().push_back(point_light4);

    // Camera

    auto camera = scene-> get_camera();
    camera-> set_position(glm::vec3(0.0f, 0.0f, 20.0f));

    // Input

    // TODO: Learm c++ lambdas
    window-> set_on_key_down([&](int key) {
        glm::mat4 model_matrix = camera-> get_model_matrix();

        switch (key) {
            case SDLK_w: camera-> add_to_position(-glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)); break;
            case SDLK_a: camera-> add_to_position(-glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)); break;
            case SDLK_s: camera-> add_to_position(glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)); break;
            case SDLK_d: camera-> add_to_position(glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)); break;
            // TODO: Remove when i have full game-play and debugging is done.
            case SDLK_e: camera-> add_to_y(CAMERA_ROT_SPEED * 2); break;
            case SDLK_q: camera-> add_to_y(-CAMERA_ROT_SPEED * 2); break;
            case SDLK_ESCAPE: exit(0);
            default: break;
        }
    });

    window-> set_on_mouse_move([&](int x, int y, int x_rel, int y_rel) {
        camera-> add_to_rotation_y(static_cast<float>(-x_rel) * MOUSE_SENCITIVITY);
        camera-> add_to_rotation_x(static_cast<float>(-y_rel) * MOUSE_SENCITIVITY);
    });

    // Rendering

    ES2Renderer renderer(scene, window);
    while(1) {
        window-> poll();

        renderer.render();
    }
}
