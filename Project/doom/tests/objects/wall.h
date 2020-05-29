//
// Created by Isa on 5/28/20.
//

#ifndef AUR_WALL_H
#define AUR_WALL_H

//
// Created by Isa on 5/28/20.
//

#include "aur.hpp"
using namespace aur;

class Wall {
public:
//    typedef std::tuple < const std::string, unsigned int, unsigned int > wall_sprite_data_type;

    Wall(
            std::string texture,
            const glm::vec3 &position,
            float width = 10.0f,
            float height = 10.0f
    ) {

        auto[plane1_indices, plane1_vertices] = geometry_generators::generate_plane_geometry_data(width, height,
                                                                                                  _w_seg_count,
                                                                                                  _h_seg_count);
        _geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
        _material = std::make_shared<ES2PhongMaterial>();

        auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file(texture);
        _texture = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);

        _texture->set_transformation_enabled(true);
        _texture->set_wrap_mode_s(Texture::WrapMode::Repeat);
        _texture->set_wrap_mode_t(Texture::WrapMode::Repeat);


        // DEFAULT TEXTURE TRANSFORMATION METRIX
        glm::mat4 texture_transformation_matrix = {glm::vec4{8.0, 0.0, 0.0, 0.0}, glm::vec4{0.0, 4.0, 0.0, 0.0},
                                                    glm::vec4{0.0, 0.0, 1.0, 0.0}, glm::vec4{0.0, 0.0, 0.0, 1.0}};

        _texture->set_transformation_matrix(texture_transformation_matrix);

        _material->set_texture_1(_texture);

        _material->set_specular_exponent(20.0f);

        _mesh = std::make_shared<Mesh>(_geometry, _material);
        _mesh->set_position(position);

    }




    [[nodiscard]] const std::shared_ptr<Mesh>& get_mesh() const
    {
        return _mesh;
    }

    void set_rotation(const glm::vec3 &rotation)
    {
        _mesh->set_rotation(rotation);
    }

    void set_transformation_matrix(const glm::mat4 &texture_transformation_matrix)
    {
        _texture->set_transformation_matrix(texture_transformation_matrix);
        _material->set_texture_1(_texture);
        _material->set_specular_exponent(20.0f);
    }
    [[nodiscard]] const std::shared_ptr<ES2PhongMaterial>& get_material() const {
        return _material;
    }

    void set_specular_exponent(float value) {
        _material->set_specular_exponent(value);
    }

    void set_specular_color(glm::vec3 value) {
        _material->set_specular_color(value);
    }

    void set_diffuse_color(glm::vec4 value) {
        _material->set_diffuse_color(value);
    }

//    ground->get_material()->set_specular_color(glm::vec3{0.0f});
//    ground->get_material()->set_diffuse_color(glm::vec4{0.25f});


private:
//    float _width = 20, _height = 20;
    int _w_seg_count = 1, _h_seg_count = 1;
    std::shared_ptr<Mesh> _mesh;
    std::shared_ptr<ES2PhongMaterial> _material;
    std::shared_ptr<ES2Geometry> _geometry;
    std::shared_ptr<ES2Texture> _texture;
};

#endif //AUR_WALL_H
