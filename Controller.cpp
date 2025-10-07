#include "Controller.h"
#include <ObjImporter.h>

Controller::Controller(Model& m,View& v) {
    model = m;
    view = v;
    time = 0.0f;
    createModels();
}

Controller::~Controller()
{

}

void Controller::run()
{
    view.init(model);

    while (!view.shouldWindowClose()) {
        //increment time
        time +=0.01f;
        model.animateStep(time);
        view.display(model);
    }
    view.closeWindow();
    exit(EXIT_SUCCESS);
}

void Controller::createModels() {
    util::PolygonMesh<VertexAttrib> mesh;
    glm::mat4 transform;
    util::Material mat;

    ifstream in;

    // trackball - should be stationary and only rotates
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, false);
    // change color to black to blend in with background
    mat.setAmbient(0, 0,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(0, 0, 0);
    mat.setSpecular(0, 0, 0);

    transform = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 150.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0), glm::vec3(700.0f, 700.0f, 700.0f));

    model.addMesh("trackball",mesh,mat,transform);
    in.close();
    

    // floor
    in.open("models/box.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, false);
    mat.setAmbient(0, 0,
                   1);  // only this one is used currently to determine color
    mat.setDiffuse(0, 0, 1);
    mat.setSpecular(0, 0, 1);

    transform = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, -1.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0), glm::vec3(500.0f, 2.0f, 500.0f));

    model.addMesh("floor",mesh,mat,transform);
    in.close();

    // back wall
    in.open("models/box.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(1, 0,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(1, 0, 0);
    mat.setSpecular(1, 0, 0);
    transform =
        glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 150.0f, -250.0f)) *
        glm::scale(glm::mat4(1.0), glm::vec3(500.0f, 300.0f, 2.0f));
    model.addMesh("back wall",mesh,mat,transform);
    in.close();

    // front wall
    in.open("models/box.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(0, 1,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(0, 1, 0);
    mat.setSpecular(0, 1, 0);
    transform =
        glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 150.0f, 250.0f)) *
        glm::scale(glm::mat4(1.0), glm::vec3(500.0f, 300.0f, 2.0f));

    model.addMesh("front wall",mesh,mat,transform);
    in.close();

    // left wall
    in.open("models/box.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(1, 0.5f,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(1, 0.5f, 0);
    mat.setSpecular(1, 0.5f, 0);
    transform =
        glm::translate(glm::mat4(1.0), glm::vec3(-250.0f, 150.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0), glm::vec3(2.0f, 300.0f, 500.0f));
    model.addMesh("left wall",mesh,mat,transform);
    in.close();

    // right wall
    in.open("models/box.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(1, 0,
                   0.5f);  // only this one is used currently to determine color
    mat.setDiffuse(1, 0, 0.5f);
    mat.setSpecular(1, 0, 0.5f);
    transform =
        glm::translate(glm::mat4(1.0), glm::vec3(250.0f, 150.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0), glm::vec3(2.0f, 300.0f, 500.0f));
    model.addMesh("right wall",mesh,mat,transform);
    in.close();

    // sun - should be stationary
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, false);
    mat.setAmbient(1, 1,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(1, 1, 0);
    mat.setSpecular(1, 1, 0);
    transform = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 150.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0), glm::vec3(50.0f, 50.0f, 50.0f));
    
    model.addMesh("sun",mesh,mat,transform);
    in.close();

    // red planet
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    glm::vec4 maxB = mesh.getMaximumBounds();
    mat.setAmbient(1, 0,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(1, 0, 0);
    mat.setSpecular(1, 0, 0);
    transform = glm::scale(glm::mat4(1.0), glm::vec3(20.0f, 20.0f, 20.0f));
    model.addMesh("red planet",mesh,mat,transform);
    in.close();

    // orange planet
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, false);
    mat.setAmbient(1, 0.5,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(1, 0.5, 0);
    mat.setSpecular(1, 0.5, 0);
    transform = glm::scale(glm::mat4(1.0), glm::vec3(20.0f, 20.0f, 20.0f));
    model.addMesh("orange planet",mesh,mat,transform);
    in.close();

    // blue planet
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, false);
    mat.setAmbient(0, 0,
                   1);  // only this one is used currently to determine color
    mat.setDiffuse(0, 0, 1);
    mat.setSpecular(0, 0, 1);
    transform = glm::scale(glm::mat4(1.0), glm::vec3(20.0f, 20.0f, 20.0f));
    model.addMesh("blue planet",mesh,mat,transform);
    in.close();

    // blue planet satellite
    in.open("models/cylinder.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, false);
    mat.setAmbient(0, 0.8,
                   1);  // only this one is used currently to determine color
    mat.setDiffuse(0, 0.8, 1);
    mat.setSpecular(0, 0.8, 1);
    transform = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1,0,0)) *
                glm::scale(glm::mat4(1.0), glm::vec3(5.0f, 15.0f, 5.0f));
    model.addMesh("blue planet satellite",mesh,mat,transform);
    in.close();

    // purple planet
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(0.5, 0,
                   1);  // only this one is used currently to determine color
    mat.setDiffuse(0.5, 0, 1);
    mat.setSpecular(0.5, 0, 1);
    transform = glm::scale(glm::mat4(1.0), glm::vec3(20.0f, 20.0f, 20.0f));
    model.addMesh("purple planet",mesh,mat,transform);
    in.close();

    // purple planet satellite 1
    in.open("models/cylinder.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(1, 0,
                   1);  // only this one is used currently to determine color
    mat.setDiffuse(1, 0, 1);
    mat.setSpecular(1, 0, 1);
    transform = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1,0,0)) *
                glm::scale(glm::mat4(1.0), glm::vec3(5.0f, 15.0f, 5.0f));
    model.addMesh("purple planet satellite 1",mesh,mat,transform);
    in.close();

    // purple planet satellite 2
    in.open("models/cylinder.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(0.5, 0.4,
                   1);  // only this one is used currently to determine color
    mat.setDiffuse(0.5, 0.4, 1);
    mat.setSpecular(0.5, 0.4, 1);
    transform = glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(1,0,0)) *
                glm::scale(glm::mat4(1.0), glm::vec3(5.0f, 7.0f, 5.0f));
    model.addMesh("purple planet satellite 2",mesh,mat,transform);
    in.close();
}