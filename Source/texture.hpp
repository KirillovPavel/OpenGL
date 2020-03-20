#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <string>

class Texture{
public:
    GLuint texture;
    int im_width, im_height;
    unsigned char* image;
    Texture(const char* path, GLint mode = SOIL_LOAD_RGB);
    void bind(GLuint program, const char* name, unsigned int i);
    void set(GLenum parameter, GLint mode);

    ~Texture();
};

struct Material{
    Texture diffuse;
    Texture specular;
    GLfloat shininess;
    Material(const char* diffuse = "/home/pohuy/Docs/Graph/Data/diffuse.png",
             const char* specular = "/home/pohuy/Docs/Graph/Data/diffuse.png",
             GLfloat shininess = 16.f);
    void bind(GLuint program, std::string name);
};

#endif // TEXTURE_HPP


//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
