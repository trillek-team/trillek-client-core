#include "resources/material.hpp"
#include "resources/shader.hpp"

namespace trillek {
namespace graphics {

Material::Material() { }
Material::~Material() { }

void Material::SetShader(std::shared_ptr<Shader> s) {
    this->shader = s;
}

size_t Material::AddTexture(std::shared_ptr<Texture> t) {
    for (size_t i = 0; i < this->textures.size(); ++i) {
        if (this->textures[i].first == t) {
            return i;
        }
    }

    // TODO: Generate the texture ID and copy the pixel data
    GLuint tex_id = 0;

    // The texture wasn't found in the list so add it.
    this->textures.push_back(std::make_pair(t, tex_id));

    return this->textures.size();
}

size_t Material::GetTextureIndex(std::shared_ptr<Texture> t) {
    for (size_t i = 0; i < this->textures.size(); ++i) {
        if (this->textures[i].first == t) {
            return i;
        }
    }

    return AddTexture(t);
}

void Material::ActivateTexture(const size_t index, const GLuint target) {
    if (index < this->textures.size()) {
        GLuint tex_id = this->textures[index].second;
        glActiveTexture(GL_TEXTURE0 + target);
        glBindTexture(GL_TEXTURE_2D, tex_id);
    }
}

} // End of graphics
} // End of trillek
