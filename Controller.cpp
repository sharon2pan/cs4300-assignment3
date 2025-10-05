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

    // sun
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, false);
    mat.setAmbient(1, 1,
                   0);  // only this one is used currently to determine color
    mat.setDiffuse(1, 1, 0);
    mat.setSpecular(1, 1, 0);
    transform = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 30.0f, 0.0f)) *
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

    // purple planet
    in.open("models/sphere.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in, true);
    mat.setAmbient(0.5, 0,
                   1);  // only this one is used currently to determine color
    mat.setDiffuse(0.5, 0, 1);
    mat.setSpecular(0.5, 0, 1);
    // the translation correction in y is because the base of the nepture model
    // is not exactly horizontal
    transform = glm::scale(glm::mat4(1.0), glm::vec3(20.0f, 20.0f, 20.0f));
    model.addMesh("purple planet",mesh,mat,transform);
    in.close();
}