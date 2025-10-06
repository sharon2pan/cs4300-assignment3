#ifndef __VIEW_H__
#define __VIEW_H__

#include <glad/glad.h>
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <cstdio>
#include <ShaderProgram.h>
#include <ObjectInstance.h>
#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include "Material.h"
#include "Model.h"
#include <stack>
#include <map>
using namespace std;



class View
{
    typedef enum {GLOBAL,FPS} TypeOfCamera;
    
public:
    View();
    ~View();
    void init(Model& model);
    void display(Model& model);
    bool shouldWindowClose();
    void closeWindow();

private:   
    void reshape(GLFWwindow* window, int width, int height);
    void dispose(GLFWwindow* window);

    void onkey(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onmouse(GLFWwindow* window, int button, int action, int mods);
    void error_callback(int error, const char* description);

    GLFWwindow* window;
    util::ShaderProgram program;
    util::ShaderLocationsVault shaderLocations;
    map<string,util::ObjectInstance *> objects;
    glm::mat4 projection;
    stack<glm::mat4> modelview;
    int frames;
    double time;
    glm::ivec2 window_dimensions;
    int angleOfRotation;
    TypeOfCamera cameraMode;

    
};

#endif