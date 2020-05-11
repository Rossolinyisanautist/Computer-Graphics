#include "aur.hpp"

static const float CAMERA_SPEED { 0.01f };
static const float CAMERA_ROT_SPEED { 0.01f };

static const float SUN_ROT_SPEED { 0.01f };
static const float EARTH_ROT_SPEED { 0.02f };

static const int CIRCLE_FRAGMENT_COUNT { 100 };
static const float CIRCLE_RADIUS { 0.5f };

static const glm::vec4 FORWARD { 0.0f, 0.0f, 1.0f, 0.0f };

int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 500, 500);

   
    std::vector<Vertex> circleVertices;
    for (int i = 0; i < CIRCLE_FRAGMENT_COUNT; ++i) {
        float angle = (float) i / (float) CIRCLE_FRAGMENT_COUNT * 2.0f * M_PI;
        float x = cosf(angle) * CIRCLE_RADIUS;
        float y = sinf(angle) * CIRCLE_RADIUS;
        circleVertices.push_back(Vertex{{x, y, 0.0f}});
    }
    
    auto circleGeometry = std::make_shared<ES2Geometry>(circleVertices);
    circleGeometry->set_type(GL_TRIANGLE_FAN);
    
    auto sunMaterial = std::make_shared<ES2ConstantMaterial>();
    sunMaterial->set_emission_color(glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f } );
    auto earthMaterial = std::make_shared<ES2ConstantMaterial>();
    earthMaterial->set_emission_color(glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });
    auto moonMaterial = std::make_shared<ES2ConstantMaterial>();
    moonMaterial->set_emission_color(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
    
    auto sun = std::make_shared<Mesh>(circleGeometry, sunMaterial, glm::vec3{0.0f, 0.0f, 0.0f} );
    sun->set_scale(glm::vec3 { 2.0f} );
    auto earth = std::make_shared<Mesh>(circleGeometry, earthMaterial, glm::vec3{1.0f, 0.0f, 0.0f} );
    earth->set_scale(glm::vec3 { 0.5f} );
    auto moon = std::make_shared<Mesh>(circleGeometry, moonMaterial, glm::vec3{1.0f, 0.0f, 0.0f} );
    moon->set_scale(glm::vec3 { 0.2f} );
    
    sun->add_child(earth);
    earth->add_child(moon);
    
    std::vector<std::shared_ptr<Object>> objects { sun };
    auto scene = std::make_shared<Scene>(objects);

    auto &camera = scene->get_camera();
    camera.set_z(5.0f);

    ES2Renderer renderer(scene, window);

    for (;;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto end;
            } else {
                switch (event.key.keysym.sym) {
                    case SDLK_w: {
                        camera.set_rotation_x(camera.get_rotation_x() - CAMERA_ROT_SPEED);
                        break;
                    }
                    case SDLK_a: {
                        camera.set_rotation_y(camera.get_rotation_y() + CAMERA_ROT_SPEED);
                        break;
                    }
                    case SDLK_s: {
                        camera.set_rotation_x(camera.get_rotation_x() + CAMERA_ROT_SPEED);
                        break;
                    }
                    case SDLK_d: {
                        camera.set_rotation_y(camera.get_rotation_y() - CAMERA_ROT_SPEED);
                        break;
                    }
                    case SDLK_e: {
                        camera.set_y(camera.get_y() + CAMERA_ROT_SPEED);
                        break;
                    }
                    case SDLK_q: {
                        camera.set_y(camera.get_y() - CAMERA_ROT_SPEED);
                        break;
                    }
                    case SDLK_UP: {
                        camera.set_position(camera.get_position() - glm::vec3(camera.get_model_matrix() * FORWARD * CAMERA_SPEED));
                        break;
                    }
                    case SDLK_DOWN: {
                        camera.set_position(camera.get_position() + glm::vec3(camera.get_model_matrix() * FORWARD * CAMERA_SPEED));
                        break;
                    }
                }
            }
        }

        sun->set_rotation_z(sun->get_rotation_z() + SUN_ROT_SPEED);
//        sun->set_rotation_y(sun->get_rotation_y() + SUN_ROT_SPEED);
        earth->set_rotation_z(earth->get_rotation_z() + EARTH_ROT_SPEED);
        
        renderer.render();
    }

end:
    return 0;
}
