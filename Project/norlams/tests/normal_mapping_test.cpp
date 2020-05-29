//
// Created by Isa on 5/27/20.
//

#include "aur.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
static const float CAMERA_SPEED{0.5f};
static const float CAMERA_ROT_SPEED{0.05f};
static const float PLANE_ROT_SPEED{0.01f};

const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

int main(int argc, char** argv) {
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("Noramls", 0, 0);

    auto[plane1_indices, plane1_vertices] = geometry_generators::generate_sphere_geometry_data(10, 40, 40);
    auto plane1_geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
//    plane1_geometry->set_type(Geometry::TriangleFan);
    plane1_geometry->calc_tangents_and_binormals();
    auto plane1_material = std::make_shared<ES2PhongMaterial>();
    auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/bricks.png");
    auto[image1_normals_data, image1_normals_width, image1_normals_height, image1_normals_channels] = file_utilities::read_image_file("data/images/bricks_normals.png");
    auto texture1 = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    auto texture1_normals = std::make_shared<ES2Texture>(image1_normals_data, image1_normals_width, image1_normals_height, image1_normals_channels);

    plane1_material->set_texture_1(texture1);
    plane1_material->set_normal_1(texture1_normals);
    plane1_material->set_specular_exponent(50.0f);
    auto sphere = std::make_shared<Mesh>(plane1_geometry, plane1_material);
    sphere->set_z(0);
    sphere->set_y(-10);
    sphere->set_rotation_x(-M_PI / 2);

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.2f, 20, 20);
    auto lamp_sphere_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    lamp_material->set_emission_color(glm::vec4(1.0f));
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);


    std::shared_ptr<Object> obj1 = std::make_shared<Object>("", glm::vec3(0.0f, -10.0f, 0.0f));
    std::shared_ptr<Object> obj2 = std::make_shared<Object>("", glm::vec3(0.0f, -20.0f, 0.0f));
    std::shared_ptr<Object> obj3 = std::make_shared<Object>("", glm::vec3(0.0f, 0.0f, 0.0f));
    obj3->add_child(sphere);

    std::vector<std::shared_ptr<Object>> objects{ obj1, obj2, obj3};
    auto scene = std::make_shared<Scene>(objects);

    auto point_light1 = std::make_shared<PointLight>();
    auto point_light2 = std::make_shared<PointLight>();
    point_light1->set_intensity(0.45f);
    point_light1->set_z(10.0f);
    point_light1->set_y(2.0f);
    point_light1->set_two_sided(true);
    obj1->add_child(point_light1);
    point_light1->add_child(lamp1);

    point_light2->set_intensity(0.45f);
    point_light1->set_z(10.0f);
    point_light2->set_y(0.0f);
    point_light2->set_x(10.0f);
    point_light2->set_two_sided(true);
    obj2->add_child(point_light2);
    point_light2->add_child(lamp2);


//    scene->get_root()->add_child(point_light1);
//    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light1);
    scene->get_point_lights().push_back(point_light2);


    auto camera = scene->get_camera();
    camera->set_x(0.0f);
    camera->set_y(-9.0f);
    camera->set_z(24.0f);
//    camera->add_to_rotation_y(-.5f);

    window->set_on_key_down([&](int key) {
        switch (key) {
            case SDLK_s: camera->add_to_rotation_x(-CAMERA_ROT_SPEED); break;
            case SDLK_a: camera->add_to_rotation_y(CAMERA_ROT_SPEED); break;
            case SDLK_w: camera->add_to_rotation_x(CAMERA_ROT_SPEED); break;
            case SDLK_d: camera->add_to_rotation_y(-CAMERA_ROT_SPEED); break;
            case SDLK_e: camera->add_to_y(CAMERA_ROT_SPEED); break;
            case SDLK_q: camera->add_to_y(-CAMERA_ROT_SPEED); break;
            case SDLK_UP: camera->add_to_position(-glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_DOWN: camera->add_to_position(glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_ESCAPE: exit(0);
            default: break;
        }
    });

    float camera_x_shift = 0.15f;
    float camera_y_rot_shift = 0.005f;
    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

//        camera->set_x(camera_x);
        camera->add_to_x(camera_x_shift);
        camera->add_to_rotation_y(camera_y_rot_shift);
        obj1->add_to_rotation_y(-0.02f);
        obj2->add_to_rotation_y(-0.04f);
        obj3->add_to_rotation_y(0.005f);

        if(camera->get_x() < -15) {
            camera->set_x(-15);
            camera_x_shift *= -1;
        }
        if(camera->get_x() > 15) {
            camera->set_x(15);
            camera_x_shift *= -1;
        }

        if(camera->get_rotation_y() > 0.5) {
            camera->set_rotation_y(0.5);
            camera_y_rot_shift = -camera_y_rot_shift;
        }
        if(camera->get_rotation_y() < -0.5) {
            camera->set_rotation_y(-0.5);
            camera_y_rot_shift = -camera_y_rot_shift;
        }

        renderer.render();


    }
}


#pragma clang diagnostic pop