#include "light.hpp"

PointLight::PointLight(glm::vec3 position,
                       glm::vec3 ambient,
                       glm::vec3 diffuse,
                       glm::vec3 specular,
                       GLfloat a, GLfloat b):
    a(a),
    b(b)
{
    for(int i = 0; i < 3; ++i){
        this->position[i] = position[i];
        this->ambient[i] = ambient[i];
        this->diffuse[i] = diffuse[i];
        this->specular[i] = specular[i];
    }
}

void PointLight::bind(GLuint program, std::string name, int iter){
    std::string realName(name);
    if(iter >= 0){
        realName += "[" + std::to_string(iter) + "]";
    }
    realName += ".";
    GLint varLoc = glGetUniformLocation(program, (realName + "position").data());
    glUniform3fv(varLoc, 1, position);
    varLoc = glGetUniformLocation(program, (realName + "ambient").data());
    glUniform3fv(varLoc, 1, ambient);
    varLoc = glGetUniformLocation(program, (realName + "diffuse").data());
    glUniform3fv(varLoc, 1, diffuse);
    varLoc = glGetUniformLocation(program, (realName + "specular").data());
    glUniform3fv(varLoc, 1, specular);
    varLoc = glGetUniformLocation(program, (realName + "a").data());
    glUniform1f(varLoc, a);
    varLoc = glGetUniformLocation(program, (realName + "b").data());
    glUniform1f(varLoc, b);
}

DirectLight::DirectLight(glm::vec3 direct,
                         glm::vec3 ambient,
                         glm::vec3 diffuse,
                         glm::vec3 specular)
{
    for(int i = 0; i < 3; ++i){
        this->direct[i] = direct[i];
        this->ambient[i] = ambient[i];
        this->diffuse[i] = diffuse[i];
        this->specular[i] = specular[i];
    }
}

void DirectLight::bind(GLuint program, std::string name, int iter){
    std::string realName(name);
    if(iter >= 0){
        realName += "[" + std::to_string(iter) + "]";
    }
    realName += ".";
    GLint varLoc = glGetUniformLocation(program, (realName + "direct").data());
    glUniform3fv(varLoc, 1, direct);
    varLoc = glGetUniformLocation(program, (realName + "ambient").data());
    glUniform3fv(varLoc, 1, ambient);
    varLoc = glGetUniformLocation(program, (realName + "diffuse").data());
    glUniform3fv(varLoc, 1, diffuse);
    varLoc = glGetUniformLocation(program, (realName + "specular").data());
    glUniform3fv(varLoc, 1, specular);
}

SpotLight::SpotLight(glm::vec3 position,
                     glm::vec3 direct,
                     glm::vec3 ambient,
                     glm::vec3 diffuse,
                     glm::vec3 specular,
                     GLfloat a, GLfloat b,
                     GLfloat inR, GLfloat exR):
    a(a),
    b(b),
    inR(glm::cos(glm::radians(inR))),
    exR(glm::cos(glm::radians(exR)))
{
    for(int i = 0; i < 3; ++i){
        this->position[i] = position[i];
        this->direct[i] = direct[i];
        this->ambient[i] = ambient[i];
        this->diffuse[i] = diffuse[i];
        this->specular[i] = specular[i];
    }
}

void SpotLight::bind(GLuint program, std::string name, int iter){
    std::string realName(name);
    if(iter >= 0){
        realName += "[" + std::to_string(iter) + "]";
    }
    realName += ".";
    GLint varLoc = glGetUniformLocation(program, (realName + "position").data());
    glUniform3fv(varLoc, 1, position);
    varLoc = glGetUniformLocation(program, (realName + "direct").data());
    glUniform3fv(varLoc, 1, direct);
    varLoc = glGetUniformLocation(program, (realName + "ambient").data());
    glUniform3fv(varLoc, 1, ambient);
    varLoc = glGetUniformLocation(program, (realName + "diffuse").data());
    glUniform3fv(varLoc, 1, diffuse);
    varLoc = glGetUniformLocation(program, (realName + "specular").data());
    glUniform3fv(varLoc, 1, specular);
    varLoc = glGetUniformLocation(program, (realName + "a").data());
    glUniform1f(varLoc, a);
    varLoc = glGetUniformLocation(program, (realName + "b").data());
    glUniform1f(varLoc, b);
    varLoc = glGetUniformLocation(program, (realName + "inR").data());
    glUniform1f(varLoc, inR);
    varLoc = glGetUniformLocation(program, (realName + "exR").data());
    glUniform1f(varLoc, exR);
}

void SpotLight::set_Pos(glm::vec3 Pos){
    for(int i = 0; i < 3; ++i)
        this->position[i] = Pos[i];
}

void SpotLight::set_Dir(glm::vec3 Dir){
    for(int i = 0; i < 3; ++i)
        this->direct[i] = Dir[i];
}
