//
// Created by Isa on 5/28/20.
//
#include "aur.hpp"
#ifndef AUR_LAMP_H
#define AUR_LAMP_H

using namespace aur;
class Lamp {

public:
    Lamp(
            float radius,
            float intensity,
            float constant_attenuation,
            float linear_attenuation,
            float quadratic_attenuation,
            bool two_sided,
            glm::vec3 position = {0.0f, 0.0f, 0.0f}
    ) {
        auto[body_indices, body_vertices] = geometry_generators::generate_sphere_geometry_data(radius, _w_seg_count, _h_seg_count);
        auto body_sphere_geometry = std::make_shared<ES2Geometry>(body_indices, body_vertices);
        auto body_material = std::make_shared<ES2ConstantMaterial>();

        _body_mesh = std::make_shared<Mesh>(body_sphere_geometry, body_material);

        _point_light = std::make_shared<PointLight>();

        _point_light->set_intensity(intensity);
        _point_light->set_constant_attenuation(constant_attenuation);
        _point_light->set_linear_attenuation(linear_attenuation);
        _point_light->set_quadratic_attenuation(quadratic_attenuation);
        _point_light->set_two_sided(two_sided);
        _point_light->set_position(position);

        _point_light->add_child(_body_mesh);
    }

    void add_child(const std::shared_ptr<Object> child) {
        _point_light->add_child(child);
    }

    void make_child_of(const std::shared_ptr<Scene> scene) {
        scene->get_root()->add_child(_point_light);
        scene->get_point_lights().push_back(_point_light);
    }

    [[nodiscard]] std::shared_ptr<Mesh> get_body_mesh() const {
        return _body_mesh;
    }

    void set_position(const glm::vec3 &position) {
        _point_light->set_position(position);
    }
    [[nodiscard]] std::shared_ptr<PointLight> get_point_light() const {
        return _point_light;
    }

private:
    int _w_seg_count = 20.0f, _h_seg_count = 20.0f;
    std::shared_ptr<PointLight> _point_light;
    std::shared_ptr<Mesh> _body_mesh;
};


#endif //AUR_LAMP_H
