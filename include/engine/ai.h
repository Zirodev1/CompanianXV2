#ifndef AI_H
#define AI_H

#include "../glm/glm.hpp"
#include "physics.h"

class AI {
private:
    Physics& m_physics;
    float m_wanderTimer;
    float m_wanderInterval;
    bool m_isPaused;

public:
    AI(Physics& physics);
    ~AI();

    void Initialize();
    void Update(float deltaTime);
    void SetPaused(bool paused);  // Added to fix undefined method error
};

#endif