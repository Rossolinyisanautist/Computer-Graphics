//
// Created by Isa on 5/28/20.
//
#include "aur.hpp"

#ifndef AUR_ENEMY_H
#define AUR_ENEMY_H


using namespace aur;
class Monster {

public:
    typedef std::tuple<const std::string, unsigned int, unsigned int> enemy_sprite_data_type;

    enum State {
        Alive,
        Dying,
        Dead
    };


    Monster(const glm::vec3& position, float size, float speed, const enemy_sprite_data_type& enemy_sprite_data)
            : _position{ position }, _speed(speed) {
        const auto& [sprite_file, sprite_frame_count, first_dying_state_sprite_frame] = enemy_sprite_data;

        auto [image_data, image_width, image_height, image_channels] = file_utilities::read_image_file(sprite_file);
        _texture = std::make_shared<ES2Texture>(image_data, image_width, image_height, image_channels);
        _texture->set_minification_filter(Texture::FilterType::Nearest);
        _texture->set_magnification_filter(Texture::FilterType::Nearest);
        _texture->set_mode(Texture::Mode::Modulation);
        _texture->set_transformation_enabled(true);
        _set_texture_frames(sprite_frame_count);
        _set_first_dying_texture_frame(first_dying_state_sprite_frame);

        auto [billboard_indices, billboard_vertices] =
            geometry_generators::generate_plane_geometry_data(size, size,5, 5);
        auto billboard_geometry = std::make_shared<ES2Geometry>(billboard_indices, billboard_vertices);
        auto billboard_materials = std::make_shared<ES2ConstantMaterial>();
        billboard_materials->set_texture_1(_texture);
        billboard_materials->set_face_culling_enabled(false);
        billboard_materials->set_blending_enabled(true);
        billboard_materials->set_transparent(true);

        _mesh = std::make_shared<Mesh>(billboard_geometry, billboard_materials);
        _mesh->set_position(position);
        _bounding_volume = Sphere{ _mesh->get_position(), size / 2 };
    }

    [[nodiscard]] const std::shared_ptr<Mesh>& get_mesh() const {
        return _mesh;
    }

    void set_target(const std::shared_ptr<Camera>& target) {
        _target = target;
    }


    [[nodiscard]] bool interesect_with_ray(const Ray& ray) const {
        return ray.intersects_with_sphere(_bounding_volume).first;
    }

    void kill() {
        if (_state == Alive) {
            _state = Dying;
            _set_texture_frame(_first_dying_texture_frame);
        }
    }

    void update(float delta_time) {
        if (_state == Dying) {
            if (_update_request++ % _update_rate != 0) {
                return;
            }

            unsigned int frame = _texture_frame + 1;
            if (frame >= _texture_frames) {
                _state = Dead;
            }
            else {
                _set_texture_frame(frame);
            }
        }
        else if (_state == Alive) {

            if (_update_request++ % _update_rate != 0) // || _target == nullptr
            {
                return;
            }

            _set_texture_frame(((_texture_frame + 1) % _first_dying_texture_frame));
        }

        _mesh->billboard_toward_camera(_target);
//        int i = 0;
    }

private:
    State _state{ Alive };
    glm::vec3 _position;
    float _speed{ 1.0f };
    glm::vec3 _velocity{ 0.0f };
    std::shared_ptr<Mesh> _mesh;
    Sphere _bounding_volume{ glm::vec3{0.0f}, 1.0f };
    std::shared_ptr<Camera> _target{ nullptr };

    int _update_request{ 0 };
    int _update_rate{ 10 };

    std::shared_ptr<ES2Texture> _texture;
    unsigned int _texture_frame{ 0 };
    unsigned int _texture_frames{ 1 };
    unsigned int _first_dying_texture_frame{ 0 };

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
        // MAYBE ERROR
        matrix[3][0] = static_cast<float>(_texture_frame) / static_cast<float>(_texture_frames);
        _texture->set_transformation_matrix(matrix);
    }

    void _set_first_dying_texture_frame(unsigned int first_dying_texture_frame) {
        _first_dying_texture_frame = first_dying_texture_frame;
    }

};


#endif //AUR_ENEMY_H
