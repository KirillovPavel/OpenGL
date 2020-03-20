#include "camera.hpp"

Camera::Camera(GLfloat key_speed,
               GLfloat mouse_speed,
               glm::vec3 cameraPos,
               glm::vec3 cameraDirect,
               GLfloat yaw,
               GLfloat pitch,
               GLfloat zoom,
               const float front,
               const float back):
    key_speed(key_speed),
    mouse_speed(mouse_speed),
    cameraPos(cameraPos),
    cameraDirect(cameraDirect),
    Up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(yaw),
    pitch(pitch),
    zoom(zoom),
    deltaTime(0.0),
    front(front),
    back(back)
{
    glm::vec3 direct;
    direct.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direct.y = sin(glm::radians(pitch));
    direct.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirect = glm::normalize(direct);
}

glm::mat4 Camera::View(){
    glm::mat4 view(1);
    view = glm::lookAt(cameraPos, cameraPos + cameraDirect, Up);
    return view;
}

void Camera::set_View(GLuint program, const char* name){
    GLint viewLoc = glGetUniformLocation(program, name);
    glm::mat4 view(1);
    view = glm::lookAt(cameraPos, cameraPos + cameraDirect, Up);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::set_Perspective(GLuint program, const char* name, GLfloat ratio){
    glm::mat4 perspective(1);
    perspective = glm::perspective(glm::radians(zoom), ratio, front, back);
    GLint perspectiveLoc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
}

void Camera::set_Model(GLuint program,
               const char* name,
               const glm::vec3 translate,
               const glm::vec3 rotate,
               const GLfloat angle,
               const glm::vec3 scale){
    glm::mat4 model(1);
    model = glm::translate(model, translate);
    model = glm::rotate(model, glm::radians(angle), rotate);
    model = glm::scale(model, scale);
    GLint modelLoc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Camera::mouse_correct(GLfloat lastX, GLfloat lastY, GLfloat xpos, GLfloat ypos){
    GLfloat sensetivity = mouse_speed * deltaTime;
    yaw += (xpos - lastX) * sensetivity;
    pitch -= (ypos - lastY) * sensetivity;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.f)
        pitch = -89.0f;

    glm::vec3 direct;
    direct.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direct.y = sin(glm::radians(pitch));
    direct.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirect = glm::normalize(direct);
}

void Camera::zoom_correct(GLfloat yoffset){
    if(zoom >= 1.0f && zoom <= 90.0f)
        zoom -= yoffset;
    if(zoom < 1.0f)
        zoom = 1.0f;
    if(zoom > 90.0f)
        zoom = 90.0f;
}

void Camera::key_correct(Movements button){
    GLfloat sensetivity = key_speed * deltaTime;
    if(button == W)
        cameraPos -= sensetivity * glm::cross(glm::cross(cameraDirect, Up), Up);
    if(button == S)
        cameraPos += sensetivity * glm::cross(glm::cross(cameraDirect, Up), Up);
    if(button == D)
        cameraPos += sensetivity * glm::normalize(glm::cross(cameraDirect, Up));
    if(button == A)
        cameraPos -= sensetivity * glm::normalize(glm::cross(cameraDirect, Up));
//    if(cameraPos.x > 5.89f)
//        cameraPos.x = 5.89f;
//    if(cameraPos.x < -5.89f)
//        cameraPos.x = -5.89f;
//    if(cameraPos.z > 5.89f)
//        cameraPos.z = 5.89f;
//    if(cameraPos.z < -5.89f)
//        cameraPos.z = -5.89f;
}

void Camera::correct_Time(GLdouble dtime){
    deltaTime = dtime;
}
