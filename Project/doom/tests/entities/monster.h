//
// Created by Isa on 5/28/20.
//
#include "aur.hpp"

#ifndef AUR_ENEMY_H
#define AUR_ENEMY_H


using namespace aur;

class Monster {
public:
    typedef std::tuple < const std::string, unsigned int, unsigned int > enemy_sprite_data_type;

    enum State {
        Alive,
        Dying,
        Dead
    };

    Monster(const glm::vec3 &position, float size, float speed, const enemy_sprite_data_type& enemy_sprite_data)
            :_position{ position }, _speed(speed)
    {
        const auto& [sprite_file, sprite_frame_count, first_dying_state_sprite_frame] = enemy_sprite_data;

        auto [image_data, image_width, image_height, image_channels] = file_utilities::read_image_file(sprite_file);
        _texture = std::make_shared<ES2Texture>(image_data, image_width, image_height, image_channels);
        _texture->set_minification_filter(Texture::FilterType::Nearest);
        _texture->set_magnification_filter(Texture::FilterType::Nearest);
        _texture->set_mode(Texture::Mode::Modulation);
        _texture->set_transformation_enabled(true);
        _set_texture_frames(sprite_frame_count);
        _set_first_dying_texture_frame(first_dying_state_sprite_frame);

        auto [billboard_indices, billboard_vertices] = geometry_generators::generate_plane_geometry_data(size, size, 1, 1);
        auto billboard_geometry = std::make_shared<ES2Geometry>(billboard_indices, billboard_vertices);
        auto billboard_material = std::make_shared<ES2ConstantMaterial>();
        billboard_material->set_texture_2(_texture);
        billboard_material->set_face_culling_enabled(false);
        billboard_material->set_blending_enabled(true);
        billboard_material->set_transparent(true);

        _mesh = std::make_shared<Mesh>(billboard_geometry, billboard_material);
        _mesh->set_position(position);
        _bounding_volume = Sphere{ _mesh->get_position(), size / 2 };
    }

    [[nodiscard]] const std::shared_ptr<Mesh>& get_mesh() const
    {
        return _mesh;
    }

    void set_target(const std::shared_ptr<Camera>& target)
    {
        _target = target;
    }


    [[nodiscard]] bool intersects_with_ray(const Ray& ray) const
    {
        return ray.intersects_with_sphere(_bounding_volume).first;
    }

    void update(float delta_time)
    {
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
            if (_update_request++ % _update_rate != 0 || _target == nullptr) {
                return;
            }

            _set_texture_frame((_texture_frame + 1) % _first_dying_texture_frame);

            glm::vec3 target = _target->get_world_position();
            glm::vec3 position = _position;
            target.y = position.y;
            _velocity = glm::normalize(target - position) * _speed * delta_time;
            _position += _velocity * delta_time;
//            _bounding_volume.set_center(_position);
            _mesh->set_position(_position);

        }

        _mesh->billboard_toward_camera(_target);

    }

    [[nodiscard]] glm::vec3 get_position() const{
        return _position;
    }

    [[nodiscard]] std::shared_ptr<Camera> get_target_position() const {
        return _target;
    }


    void die() {
        if (_state == Alive) {
            _state = Dying;
            _set_texture_frame(_first_dying_texture_frame);
        }
    }

private:
    State _state{Alive};

    glm::vec3 _position;

    float _speed{ 1.0f };
    glm::vec3 _velocity{ 0.0f };

    std::shared_ptr<Mesh> _mesh;
    Sphere _bounding_volume{ glm::vec3{0.0f}, 1.0f };

    std::shared_ptr<Camera> _target{ nullptr };

    int _update_request{ 0 };
    int _update_rate{ 8 };

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
        matrix[3][0] = static_cast<float>(_texture_frame) / static_cast<float>(_texture_frames);
        _texture->set_transformation_matrix(matrix);
    }

    void _set_first_dying_texture_frame(unsigned int first_dying_texture_frame) {
        _first_dying_texture_frame = first_dying_texture_frame;
    }
};

#endif //AUR_ENEMY_H
