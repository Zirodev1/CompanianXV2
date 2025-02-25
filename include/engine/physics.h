#ifndef PHYSICS_H
#define PHYSICS_H

#include "../glm/glm.hpp"
#include "object.h"

class Physics {
private:
    glm::vec3 m_position;
    glm::vec3 m_velocity;
    float m_gravity;
    Object* m_object; // Link to the AI object

public:
    Physics();
    ~Physics();

    void Initialize(Object* obj = nullptr);
    void Update(float deltaTime);
    glm::vec3 GetPosition() const;  // Added to fix undefined method error
    void SetPosition(glm::vec3 pos);
    void SetObject(Object* obj);
};

#endif