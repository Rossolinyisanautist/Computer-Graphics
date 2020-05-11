//
//  triangle_test.cpp
//  triangle_test
//
//  Created by Isa on 3/8/20.
//

#include "aur.hpp"


int main()
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);
    
    std::vector<glm::vec4> colors = std::vector<glm::vec4>{
        {0.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 1.0f, 1.0f}
    };
    
    auto geometryData = geometry_generators::generate_triangle_geometry_data(1, colors);
    
    auto triangle_geometry = std::make_shared<ES2Geometry>(geometryData.first, geometryData.second);
    triangle_geometry->set_type(Geometry::Type::TriangleFan);
    
    auto triangle_material = std::make_shared<ES2ConstantMaterial>();
    
    auto triangle_mesh = std::make_shared<Mesh>(triangle_geometry, triangle_material, glm::vec3(0.0f, 0.0f, 0.0f));
    triangle_mesh->set_scale(glm::vec3{ 3.0f });
    
    std::vector<std::shared_ptr<Object>> objects = { triangle_mesh };
//    objects.push_back(triangle_mesh);
    auto scene = std::make_shared<Scene>(objects);
    
    auto& camera = scene->get_camera();
    camera->set_z(10.0f);
    
    ES2Renderer renderer = ES2Renderer(scene, window);
    
    while (true) {
        window->poll();
        
//        triangle_mesh->set_rotation_z(triangle_mesh->get_rotation_z() + 10.0f);
        triangle_mesh->set_rotation_z(triangle_mesh->get_rotation_z() + .15f);
        
        renderer.render();
    }
    
}
