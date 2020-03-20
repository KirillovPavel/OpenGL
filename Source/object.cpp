#include "object.hpp"

Object::Object(const GLfloat* vertices, unsigned int size_v,
               const GLuint* indexes, unsigned int size_i){
    this->size_v = size_v / sizeof(GLfloat);
    this->size_i = size_i / sizeof(GLuint);
    this->vertices = new GLfloat[size_v];
    this->indexes = new GLuint[size_i];
    for(unsigned int i = 0; i < size_v; ++i)
        this->vertices[i] = vertices[i];
    for(unsigned int i = 0; i < size_i; ++i)
        this->indexes[i] = indexes[i];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_v, this->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_i, this->indexes, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, size_i, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Object::print(){
    std::cout << size_v << ' ' << size_i << std::endl << std::endl;
    for(unsigned int i = 0; i < size_v / 11; i++){
        for(unsigned int j = 0; j < 11; j++)
            std::cout << vertices[11*i + j] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for(unsigned int i = 0; i < size_i / 3; ++i){
        for(unsigned j = 0; j < 3; ++j)
            std::cout << indexes[3*i + j] << ' ';
        std::cout << std::endl;
    }
}

Object::~Object(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete[] vertices;
    delete[] indexes;
}
