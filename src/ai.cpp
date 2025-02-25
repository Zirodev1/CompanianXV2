#include "ai.h"
#include <cstdlib>
#include <ctime>

AI::AI(Physics& physics) 
    : m_physics(physics), 
      m_wanderTimer(0.0f), 
      m_wanderInterval(2.0f),
      m_isPaused(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

AI::~AI() {}

void AI::Initialize() {}

void AI::Update(float deltaTime) {
    if (m_isPaused) return;

    m_wanderTimer += deltaTime;
    if (m_wanderTimer >= m_wanderInterval) {
        // Random wandering
        glm::vec3 velocity = glm::vec3(
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f, // Random x (-1 to 1)
            0.0f, // No vertical movement
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f  // Random z (-1 to 1)
        );
        velocity = glm::normalize(velocity); // Normalize for consistent speed
        velocity *= 2.0f; // Set speed
        m_physics.SetPosition(m_physics.GetPosition()); // Reset position for simplicity
        m_physics.Update(deltaTime); // Apply physics
        m_wanderTimer = 0.0f;
        m_wanderInterval = static_cast<float>(std::rand()) / RAND_MAX * 3.0f + 1.0f; // Random interval (1-4 seconds)
    } else {
        m_physics.Update(deltaTime); // Continue current movement
    }
}

void AI::SetPaused(bool paused) {  // Implemented to fix undefined method error
    m_isPaused = paused;
}