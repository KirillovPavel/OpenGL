#define GLEW_STATIC

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

//#include <iostream>
//#include <unistd.h>

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "window.hpp"
#include "object.hpp"
#include "light.hpp"

static Camera camera;
static PointLight pointLight[2];
static DirectLight directLight[1];
static SpotLight spotLight[1];
static GLfloat lastX = 400.0f;
static GLfloat lastY = 300.0f;
static bool firstMouse = true;

static bool keys[1024]{0};
static bool shift = 0;
static int lightNum = 0;
static bool fonarik = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movements();

int main()
{
    //WINDOW;

    Window window;
    
    //CALLBACKS

    glfwSetKeyCallback(window.window, key_callback);
    glfwSetCursorPosCallback(window.window, mouse_callback);
    glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window.window, scroll_callback);

    //SHADER
    
    Shader ObjectProgram("Shaders/v_object", "Shaders/f_object");

    //TEXTURE

    Material material;
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    Texture floor_down("Data/floor_down.png");
    Texture wall("Data/wall.png");
    Texture floor_up("Data/floor_up.png");
    Texture sunset("Data/sunset.png");

    glEnable(GL_DEPTH_TEST);

    //VERTEXES

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 	0.0f, 0.0f,  0.0f, 0.0f, 1.0f, //down-left
        0.5f, -0.5f, 0.0f,		1.0f, 0.0f,  0.0f, 0.0f, 1.0f, //down-right
        0.5f, 0.5f, 0.0f,		1.0f, 1.0f,  0.0f, 0.0f, 1.0f, //up-right
        -0.5f, 0.5f, 0.0f,		0.0f, 1.0f,  0.0f, 0.0f, 1.0f, //up-left
    };
    GLuint ind[] = {
        0, 1, 2,
        0, 2, 3,
    };
    glm::vec3 WallPositions[] = {
        glm::vec3(0.0f, -3.0f, 0.0f),
        glm::vec3(0.0f, 3.0f, 0.0f),
        glm::vec3(6.0f, 0.0f, 0.0f),
        glm::vec3(-6.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -6.0f),
        glm::vec3(0.0f, 0.0f, 40.0f)
    };

    //OBJECTS

    Object Wall_obj(vertices, sizeof (vertices), ind, sizeof (ind));

    //GAME LOOP

    GLdouble lastTime = glfwGetTime();

    while(!glfwWindowShouldClose(window.window)) {
        GLdouble currentTime = glfwGetTime();
        camera.correct_Time(currentTime - lastTime);
        lastTime = currentTime;

        glfwPollEvents();
        do_movements();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ObjectProgram.use();
        for(int i = 0; i < 2; ++i)
            pointLight[i].bind(ObjectProgram.program, "pointLight", i);
        directLight[0].bind(ObjectProgram.program, "directLight", 0);
        if(fonarik){
            spotLight[0].set_Dir(-camera.cameraDirect);
            spotLight[0].set_Pos(camera.cameraPos);
            spotLight[0].bind(ObjectProgram.program, "spotLight", 0);
        }

        material.bind(ObjectProgram.program, "material");
        GLint lightLoc = glGetUniformLocation(ObjectProgram.program, "cameraPos");
        glUniform3f(lightLoc, camera.cameraPos[0], camera.cameraPos[1], camera.cameraPos[2]);

        camera.set_View(ObjectProgram.program, "view");
        camera.set_Perspective(ObjectProgram.program, "perspective", 1.0f * window.width / window.height);

        //BALY
        ObjectProgram.use();
        camera.set_Model(ObjectProgram.program, "model",
                         WallPositions[0], glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(12.0f, 12.0f, 1.0f));
        floor_down.bind(ObjectProgram.program, "ourTexture", 0);
        Wall_obj.draw();

        camera.set_Model(ObjectProgram.program, "model",
                         WallPositions[1], glm::vec3(1.0f, 0.0f, 0.0f), 90.0f, glm::vec3(12.0f, 12.0f, 1.0f));
        floor_up.bind(ObjectProgram.program, "ourTexture", 0);
        Wall_obj.draw();

        //walls
        camera.set_Model(ObjectProgram.program, "model",
                         WallPositions[2], glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, glm::vec3(12.0f, 6.0f, 1.0f));
        wall.bind(ObjectProgram.program, "ourTexture", 0);
        Wall_obj.draw();

        camera.set_Model(ObjectProgram.program, "model",
                         WallPositions[3], glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, glm::vec3(12.0f, 6.0f, 1.0f));
        wall.bind(ObjectProgram.program, "ourTexture", 0);
        Wall_obj.draw();

        camera.set_Model(ObjectProgram.program, "model",
                         WallPositions[4], glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, glm::vec3(12.0f, 6.0f, 1.0f));
        wall.bind(ObjectProgram.program, "ourTexture", 0);
        Wall_obj.draw();

        camera.set_Model(ObjectProgram.program, "model",
                         WallPositions[5], glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, glm::vec3(100.0f, 80.0f, 1.0f));
        sunset.bind(ObjectProgram.program, "ourTexture", 0);
        Wall_obj.draw();

        glfwSwapBuffers(window.window);
    }
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(action == GLFW_PRESS)
        keys[key] = true;
    else
        if(action == GLFW_RELEASE)
            keys[key] = false;
    if(mode == GLFW_MOD_SHIFT)
        shift = 1;
    else
        shift = 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    camera.mouse_correct(lastX, lastY, xpos, ypos);
    lastX = xpos;
    lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.zoom_correct(yoffset);
}

void do_movements(){
    float sensetivity = 0.01f;
    if(shift){
        sensetivity = 0.05f;
        camera.key_speed = 5.0f;
    } else {
        camera.key_speed = 2.0f;
    }
    if(keys[GLFW_KEY_F])
        fonarik = 1 - fonarik;
    if(keys[GLFW_KEY_0])
        lightNum = 0;
    if(keys[GLFW_KEY_1])
        lightNum = 1;
    if(keys[GLFW_KEY_UP])
        pointLight[lightNum].position[2] -= sensetivity;
    if(keys[GLFW_KEY_DOWN])
        pointLight[lightNum].position[2] += sensetivity;
    if(keys[GLFW_KEY_RIGHT])
        pointLight[lightNum].position[0] += sensetivity;
    if(keys[GLFW_KEY_LEFT])
        pointLight[lightNum].position[0] -= sensetivity;
    if(keys[GLFW_KEY_W])
        camera.key_correct(W);
    if(keys[GLFW_KEY_S])
        camera.key_correct(S);
    if(keys[GLFW_KEY_D])
        camera.key_correct(D);
    if(keys[GLFW_KEY_A])
        camera.key_correct(A);
}
