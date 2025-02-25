#include "physics.h"

Physics::Physics() 
    : m_position(glm::vec3(0.0f, 1.0f, 0.0f)), 
      m_velocity(glm::vec3(0.0f)),
      m_gravity(-9.81f),
      m_object(nullptr) {}

Physics::~Physics() {}

void Physics::Initialize(Object* obj) {
    m_object = obj;
    if (m_object) {
        m_position = m_object->position;
    }
}

void Physics::Update(float deltaTime) {
    if (m_object) {
        // Simple gravity and ground collision
        m_velocity.y += m_gravity * deltaTime;
        glm::vec3 positionChange = m_velocity * deltaTime;
        m_position += positionChange;

        // Prevent falling through ground
        if (m_position.y < 0.0f) {
            m_position.y = 0.0f;
            m_velocity.y = 0.0f;
        }

        m_object->position = m_position; // Update object position
    }
}

glm::vec3 Physics::GetPosition() const {  // Implemented to fix undefined method error
    return m_position;
}

void Physics::SetPosition(glm::vec3 pos) {
    m_position = pos;
    if (m_object) {
        m_object->position = m_position;
    }
}

void Physics::SetObject(Object* obj) {
    m_object = obj;
    if (m_object) {
        m_position = m_object->position;
    }
}