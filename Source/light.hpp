#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

struct PointLight{
    GLfloat position[3];
    GLfloat ambient[3];
    GLfloat diffuse[3];
    GLfloat specular[3];
    GLfloat a;
    GLfloat b;
    PointLight(glm::vec3 position = glm::vec3(3.0f, 0.0f, -3.0f),
               glm::vec3 ambient = glm::vec3(0.5f, 0.5f, 0.5f),
               glm::vec3 diffuse = glm::vec3(5.0f, 5.0f, 5.0f),
               glm::vec3 specular = glm::vec3(3.0f, 3.0f, 3.0f),
               GLfloat a = 0.032f, GLfloat b = 1.5f);
    void bind(GLuint program, std::string name, int iter);
};

struct DirectLight{
    GLfloat direct[3];
    GLfloat ambient[3];
    GLfloat diffuse[3];
    GLfloat specular[3];
    DirectLight(glm::vec3 direct = glm::vec3(-1.0f, -1.0f, 1.0f),
                glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3 diffuse = glm::vec3(1.0f),
                glm::vec3 specular = glm::vec3(2.0f));
    void bind(GLuint program, std::string name, int iter);
};

struct SpotLight{
    GLfloat position[3];
    GLfloat direct[3];
    GLfloat ambient[3];
    GLfloat diffuse[3];
    GLfloat specular[3];
    GLfloat a;
    GLfloat b;
    GLfloat inR;
    GLfloat exR;
    SpotLight(glm::vec3 position = glm::vec3(3.0f, 0.0f, -3.0f),
              glm::vec3 direct = glm::vec3(0.0f, -1.0f, 0.0f),
              glm::vec3 ambient = glm::vec3(0.5f, 0.5f, 0.5f),
              glm::vec3 diffuse = glm::vec3(15.0f),
              glm::vec3 specular = glm::vec3(3.0f, 3.0f, 3.0f),
              GLfloat a = 0.032f, GLfloat b = 1.5f,
              GLfloat inR = 0.5f, GLfloat exR = 20.5f);
    void bind(GLuint program, std::string name, int iter);
    void set_Pos(glm::vec3 Pos);
    void set_Dir(glm::vec3 Dir);
};

#endif // LIGHT_HPP
