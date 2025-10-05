#include "View.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexAttrib.h"


View::View() {

}

View::~View(){

}

void View::init(Model& model) 
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_dimensions = glm::ivec2(800,800);

    window = glfwCreateWindow(window_dimensions.x,window_dimensions.y, "CameraViews", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwGetFramebufferSize(window, &window_dimensions[0], &window_dimensions[1]);

    glfwSetWindowUserPointer(window, this);

    //using C++ functions as callbacks to a C-style library
    glfwSetKeyCallback(window, 
    [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        static_cast<View*>(glfwGetWindowUserPointer(window))->onkey(window,key,scancode,action,mods);
    });

    glfwSetWindowSizeCallback(window, 
    [](GLFWwindow* window, int width,int height)
    {
        static_cast<View*>(glfwGetWindowUserPointer(window))->reshape(window,width,height);
    });

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // create the shader program
    program.createProgram(string("shaders/default.vert"),
                          string("shaders/default.frag"));
    // assuming it got created, get all the shader variables that it uses
    // so we can initialize them at some point
    // enable the shader program
    program.enable();
    shaderLocations = program.getAllShaderVariables();

    
    //now we create an object that will be used to render this mesh in opengl
    /*
     * now we create an ObjectInstance for it.
     * The ObjectInstance encapsulates a lot of the OpenGL-specific code
     * to draw this object
     */

    /* so in the mesh, we have some attributes for each vertex. In the shader
     * we have variables for each vertex attribute. We have to provide a mapping
     * between attribute name in the mesh and corresponding shader variable
     name.
     *
     * This will allow us to use PolygonMesh with any shader program, without
     * assuming that the attribute names in the mesh and the names of
     * shader variables will be the same.

       We create such a shader variable -> vertex attribute mapping now
     */
    map<string, string> shaderVarsToVertexAttribs;

    // currently there are only two per-vertex attribute: position and color
    shaderVarsToVertexAttribs["vPosition"] = "position";

    vector<string> meshNames = model.getMeshNames();

    for (string name:meshNames) {
        util::ObjectInstance *obj =  new util::ObjectInstance("triangles");
        obj->initPolygonMesh<VertexAttrib>(
            program,                    // the shader program
            shaderLocations,            // the shader locations
            shaderVarsToVertexAttribs,  // the shader variable -> attrib map
            model.getMesh(name));                      // the actual mesh object
        objects[name] = obj;
    }

    
	

    //prepare the projection matrix for orthographic projection
	glViewport(0, 0, window_dimensions.x, window_dimensions.y);
    projection = glm::perspective((float)glm::radians(60.0f),
            (float) window_dimensions.x/window_dimensions.y,
            0.1f,
            10000.0f);
            

   // projection = glm::ortho(-400.0f,400.0f,-400.0f,400.0f,0.1f,10000.0f);
    angleOfRotation = 0;
    cameraMode = GLOBAL;

    frames = 0;
    time = glfwGetTime();
    
}



void View::display(Model& model)
{
    program.enable();
    //set the background color to be black
    glClearColor(0,0,0, 1);
    //clear the background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //outline mode
    

     glUniformMatrix4fv(shaderLocations.getLocation("projection"), 1,
                              false, glm::value_ptr(projection));
    
    while (!modelview.empty()) {
        modelview.pop();
    }
    modelview.push(glm::mat4(1.0));

    if (cameraMode == GLOBAL)
    {
        glm::vec4 camera = glm::vec4(0.0f, 600.0f, 600.0f, 1.0f);
        // transform the camera
        // camera = cameraRotation * camera;
        modelview.top() = modelview.top() *
                          glm::lookAt(glm::vec3(camera.x, camera.y, camera.z),
                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                      glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else
    {
        

        modelview.top() = modelview.top() *
            glm::lookAt(glm::vec3(0.0f,0.0f,-10.0f),glm::vec3(0.0f,0.0f,500.0f),glm::vec3(0.0f,1.0f,0.0f))
            * glm::inverse(model.getAnimationTransform("red planet"));

            
    }

    for (string name:model.getMeshNames()) {
        modelview.push(modelview.top());  // save the current modelview
        glm::mat4 transform =
            model.getAnimationTransform(name) * model.getTransform(name);
        modelview.top() = modelview.top() * transform;

        // The total transformation is whatever was passed to it, with its own
        // transformation
        glUniformMatrix4fv(shaderLocations.getLocation("modelview"), 1,
                              false, glm::value_ptr(modelview.top()));
        // set the color for all vertices to be drawn for this object
        glUniform4fv(shaderLocations.getLocation("vColor"), 1,
                        glm::value_ptr(model.getMaterial(name).getAmbient()));
        objects[name]->draw();
        modelview.pop();
    }

    glFlush();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //revert back to fill mode

    
    program.disable();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    frames++;
    double currenttime = glfwGetTime();
    if ((currenttime-time)>1.0) {
        printf("Framerate: %2.0f\r",frames/(currenttime-time));
        frames = 0;
        time = currenttime;
    }
    

}

bool View::shouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void View::onkey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // If the user presses escape, the program should exit
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        closeWindow();
        exit(EXIT_SUCCESS);
    }
    if (key=='F') {
        cameraMode = FPS;
    }
    else if (key=='G') {
        cameraMode = GLOBAL;
    }
}

void View::reshape(GLFWwindow* window, int width, int height) 
{
    window_dimensions = glm::ivec2(width,height);
    glViewport(0, 0, width, height);
    projection = glm::perspective((float)glm::radians(60.0f),
            (float) width/height,
            0.1f,
            10000.0f);
            

   // projection = glm::ortho(-400.0f,400.0f,-400.0f,400.0f,0.1f,10000.0f);
}

void View::dispose(GLFWwindow* window)
{
    closeWindow();
}

void View::closeWindow() {
    for (map<string,util::ObjectInstance *>::iterator it=objects.begin();it!=objects.end();it++) {
        it->second->cleanup();
        delete it->second;
    }
    objects.clear();
    glfwDestroyWindow(window);

    glfwTerminate();
}

void View::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



