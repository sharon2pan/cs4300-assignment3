#include "Model.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Model::Model()
{
}

const util::PolygonMesh<VertexAttrib>& Model::getMesh(const string& name) {
    return meshes[name];
}

const util::Material& Model::getMaterial(const string& name) {
    return materials[name];
}

const glm::mat4 Model::getTransform(const string& name) {
    return glm::mat4(transformations[name]);
}

const glm::mat4 Model::getAnimationTransform(const string& name) {
    return glm::mat4(animation_transformations[name]);
}

void Model::addMesh(const string& name,util::PolygonMesh<VertexAttrib>& mesh,util::Material& mat,glm::mat4& transformation) {
    meshes[name] = mesh;
    materials[name] = mat;
    transformations[name] = transformation;
    animation_transformations[name] = glm::mat4(1.0f);
}

vector<string> Model::getMeshNames() {
    vector<string> names;

    for (auto const& mapentry:meshes) {
        names.push_back(mapentry.first);
    }
    return names;
}

void Model::animateStep(float time) {
    // red planet
    animation_transformations["red planet"] =
        glm::rotate(glm::mat4(1.0), glm::radians(-150.0f * time),
                    glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::translate(glm::mat4(1.0), glm::vec3(75.0f, 50.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0), glm::radians(150.0f * time),
                    glm::vec3(0.0f, 0.0f, 1.0f));

    // orange planet
    animation_transformations["orange planet"] =
        glm::rotate(glm::mat4(1.0), glm::radians(-50.0f * time),
                    glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::translate(glm::mat4(1.0), glm::vec3(-110.0f, 50.0f, -200.0f)) *
        glm::rotate(glm::mat4(1.0), glm::radians(-time * 50.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));

    // blue planet
    animation_transformations["blue planet"] =
        glm::rotate(glm::mat4(1.0), glm::radians(-75.0f * time),
                    glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::translate(glm::mat4(1.0), glm::vec3(100.0f, 0.0f, 200.0f)) *
        glm::rotate(glm::mat4(1.0), glm::radians(time * 75.0f),
                    glm::vec3(1.0f, 1.0f, 0.0f));

    // purple planet
    animation_transformations["purple planet"] =
        glm::rotate(glm::mat4(1.0), glm::radians(-50.0f * time),
                    glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::translate(glm::mat4(1.0), glm::vec3(-100.0f, 0.0f, 200.0f)) *
        glm::rotate(glm::mat4(1.0), glm::radians(time * 50.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));
}

Model::~Model()
{

}

