//
// Created by Isa on 5/28/20.
//
#include "aur.hpp"
#ifndef AUR_GUN_H
#define AUR_GUN_H

using namespace aur;

class Weapon {
public:
    typedef std::tuple < const std::string, unsigned int, unsigned int > gun_sprite_data_type;

    enum State {
        Neutral,
        Shooting,
    };

    Weapon(const glm::vec3& position, float size, const gun_sprite_data_type& gun_sprite_data)
            :_position{ position }
    {
        const auto& [sprite_file, sprite_frame_count, first_shoot_sprite_frame] = gun_sprite_data;

        auto [image_data, image_width, image_height, image_channels] = file_utilities::read_image_file(sprite_file);
        _texture = std::make_shared<ES2Texture>(image_data, image_width, image_height, image_channels);
        _texture->set_minification_filter(Texture::FilterType::Nearest);
        _texture->set_magnification_filter(Texture::FilterType::Nearest);
        _texture->set_mode(Texture::Mode::Modulation);
        _texture->set_transformation_enabled(true);
        _set_texture_frames(sprite_frame_count);
        _set_first_shoot_frame(first_shoot_sprite_frame);

        auto [overlay_indices, overlay_vertices] = geometry_generators::generate_plane_geometry_data(size, size, 1, 1);
        auto overlay_geometry = std::make_shared<ES2Geometry>(overlay_indices, overlay_vertices);
        auto overlay_material = std::make_shared<ES2ConstantMaterial>();
        overlay_material->set_texture_1(_texture);
        overlay_material->set_blending_enabled(true);
        overlay_material->set_overlay(true);

        _mesh = std::make_shared<Mesh>(overlay_geometry, overlay_material);
        _mesh->set_position(position);

    }

    [[nodiscard]] const std::shared_ptr<Mesh>& get_mesh() const
    {
        return _mesh;
    }

    void shoot_animation() {
        if (_state == Neutral) {
            _state = Shooting;
            _set_texture_frame(_first_shoot_texture_frame);
        }
    }

    void update()
    {
        if (_state == Shooting) {
            if (_update_request++ % _update_rate != 0) {
                return;
            }

            unsigned int frame = _texture_frame + 1;
            if (frame >= _texture_frames) {
                _state = Neutral;
                _set_texture_frame(0);
            }
            else {
                _set_texture_frame(frame);
            }
        }

    }

private:
    State _state{ Neutral };

    glm::vec3 _position;

    glm::vec3 _velocity{ 0.0f };

    std::shared_ptr<Mesh> _mesh;

    std::shared_ptr<Camera> _target{ nullptr };

    int _update_request{ 0 };
    int _update_rate{ 4 };

    std::shared_ptr<ES2Texture> _texture;
    unsigned int _texture_frame{ 0 };
    unsigned int _texture_frames{ 1 };
    unsigned int _first_shoot_texture_frame{ 0 };

    void _set_texture_frame(unsigned int texture_frame) {
        _texture_frame = texture_frame;
        glm::mat4 matrix = _texture->get_transformation_matrix();
        matrix[3][0] = static_cast<float>(_texture_frame) / static_cast<float>(_texture_frames);
        _texture->set_transformation_matrix(matrix);
    }


    void _set_texture_frames(unsigned int texture_frames) {
        _texture_frames = texture_frames;
        glm::mat4 matrix = _texture->get_transformation_matrix();
        matrix[0][0] = 1.0f / static_cast<float>(_texture_frames);
        matrix[3][0] = static_cast<float>(_texture_frame) / static_cast<float>(_texture_frames);
        _texture->set_transformation_matrix(matrix);
    }

    void _set_first_shoot_frame(unsigned int first_shoot_texture_frame) {
        _first_shoot_texture_frame = first_shoot_texture_frame;
    }
};



#endif //AUR_GUN_H
