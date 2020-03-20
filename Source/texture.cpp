#include "texture.hpp"

Texture::Texture(const char* path, GLint mode){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    image = SOIL_load_image(path, &im_width, &im_height, nullptr, mode);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_width, im_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::set(GLenum parameter, GLint mode){
    glTexParameteri(GL_TEXTURE_2D, parameter, mode);
}

void Texture::bind(GLuint program, const char* name, GLuint i){
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(program, name), i);
}

Texture::~Texture(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

Material::Material(const char* diffuse,
                   const char* specular,
                   GLfloat shininess):
    diffuse(diffuse),
    specular(specular),
    shininess(shininess)
{}

void Material::bind(GLuint program, std::string name){
    diffuse.bind(program, (name + ".diffuse").data(), 1);
    specular.bind(program, (name + ".specular").data(), 2);
    GLint varLoc = glGetUniformLocation(program, (name + ".shininess").data());
    glUniform1f(varLoc, shininess);
}
