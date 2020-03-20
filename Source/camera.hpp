#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Movements{
    W,
    S,
    A,
    D
};

class Camera{
public:
    GLfloat key_speed;
    GLfloat mouse_speed;

    glm::vec3 cameraPos;
    glm::vec3 cameraDirect;
    glm::vec3 Up;
    
    GLfloat yaw;
    GLfloat pitch;
    GLfloat zoom;

    GLdouble deltaTime;

    const float front;
    const float back;

    Camera(GLfloat key_speed = 2.0f,
           GLfloat mouse_speed = 5.0f,
           glm::vec3 cameraPos = glm::vec3(0.0f, -1.0f, 13.0f),
           glm::vec3 cameraDirect = glm::vec3(0.0f, 0.0f, -1.0f),
           GLfloat yaw = -90.0f,
           GLfloat pitch = 0.0f,
           GLfloat zoom = 45.0f,
           const float front = 0.01f,
           const float back = 1000.0f);

    glm::mat4 View();
    void set_View(GLuint program, const char* name);
    void set_Perspective(GLuint program, const char* name, GLfloat ratio);
    void set_Model(GLuint program,
                   const char* name,
                   const glm::vec3 translate,
                   const glm::vec3 rotate,
                   const GLfloat angle,
                   const glm::vec3 scale);
    void mouse_correct(GLfloat lastX, GLfloat lastY, GLfloat xpos, GLfloat ypos);
    void zoom_correct(GLfloat yoffset);
    void key_correct(Movements button);
    void correct_Time(GLdouble dtime);
};

#endif // CAMERA_HPP
