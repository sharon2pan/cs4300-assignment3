#include <vector>
#include <string>
#include <glm/glm.hpp>


class Planet {
public:
    std::string name;
    glm::vec3 color;
    float orbitRadius;
    float orbitSpeed;
    float rotationAngle;
    glm::mat4 orientation;

    std::vector<Moon*> satellites;

    void update(float deltaTime);
    void draw(glm::mat4 parentTransform);
};
