#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GL/glew.h>
#include <iostream>

class Object{
public:
    GLuint VBO, EBO, VAO;
    GLfloat* vertices;
    GLuint* indexes;
    int n_vec;
    unsigned int size_v;
    unsigned int size_i;

    Object(const GLfloat* vertices, unsigned int size_v,
           const GLuint* indexes, unsigned int size_i);
    void draw();
    void print();
    ~Object();
};

#endif // OBJECT_HPP
