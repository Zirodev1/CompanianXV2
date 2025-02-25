#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "../glm/glm.hpp"

struct Object {
    std::string name;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec4 color;

    Object(const std::string& n = "New Object", glm::vec3 pos = glm::vec3(0.0f), 
           glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), 
           glm::vec4 col = glm::vec4(1.0f));
};

#endif