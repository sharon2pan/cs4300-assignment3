#ifndef __MODEL_H__
#define __MODEL_H__

#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include <map>
using namespace std;

#include "Material.h"

class Model 
{
public:
    Model();
    ~Model();
    const util::PolygonMesh<VertexAttrib>& getMesh(const string& name);
    const util::Material& getMaterial(const string& name);
    const glm::mat4 getTransform(const string& name);
    const glm::mat4 getAnimationTransform(const string& name);
    vector<string> getMeshNames();
    void addMesh(const string& name,util::PolygonMesh<VertexAttrib>& mesh,util::Material& mat,glm::mat4& transformation);
    void animateStep(float time);
private:
    map<string,util::PolygonMesh<VertexAttrib> > meshes;
    map<string,util::Material> materials;
    map<string,glm::mat4> transformations;
    map<string,glm::mat4> animation_transformations;
};
#endif