#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window{
public:
    unsigned int width, height;
    GLFWwindow* window ;
    Window(const unsigned int width = 1360,
           const unsigned int height = 768);
    ~Window();
};

#endif // WINDOW_HPP
