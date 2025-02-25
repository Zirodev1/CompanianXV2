#include "object.h"

Object::Object(const std::string& n, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, glm::vec4 col)
    : name(n), position(pos), rotation(rot), scale(scl), color(col) {}