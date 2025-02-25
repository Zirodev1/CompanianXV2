#include "world_engine.h"
#include "window.h"  // Include Window here instead of in the header

WorldEngine::WorldEngine() 
    : m_cameraPosition(glm::vec3(0.0f, 10.0f, -20.0f)),
      m_cameraTarget(glm::vec3(0.0f)),
      m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
      m_ai(m_physics) {
}

WorldEngine::~WorldEngine() {}

bool WorldEngine::Run(Window& window) {
    while (window.ProcessMessages()) {
        float deltaTime = 1.0f / 60.0f; // Simplified for now (use actual time later)

        if (!m_editMode) {
            m_physics.Update(deltaTime);
            m_ai.Update(deltaTime);
            glm::vec3 aiPos = m_physics.GetPosition();
            m_cameraPosition = glm::vec3(aiPos.x, aiPos.y + 10.0f, aiPos.z - 20.0f); // Follow AI
        }

        m_renderer.Update(m_cameraPosition, m_cameraTarget, m_cameraUp, m_editMode);
        m_renderer.Render();
    }
    return false;  // Return false when the loop exits (window closed)
}

void WorldEngine::Initialize(Window& window) {
    m_renderer.Initialize(window.getNativeHandle());
    m_physics.Initialize(const_cast<Object*>(&m_renderer.GetObjects()[1])); // Updated to pass Object* directly
    m_ai.Initialize();
}

void WorldEngine::ToggleEditMode() {
    m_editMode = !m_editMode;
    m_renderer.SetEditMode(m_editMode);
    m_ai.SetPaused(m_editMode);
    if (m_editMode) {
        // Optionally reset or pause physics/AI state
    } else {
        // Resume physics/AI
    }
}

bool WorldEngine::IsEditMode() const {
    return m_editMode;
}

void WorldEngine::Update(float deltaTime) {
  // Implementation code
  // You're already calling this in Run(), so move that code here
  // or create a proper implementation
  if (!m_editMode) {
      m_physics.Update(deltaTime);
      m_ai.Update(deltaTime);
      glm::vec3 aiPos = m_physics.GetPosition();
      m_cameraPosition = glm::vec3(aiPos.x, aiPos.y + 10.0f, aiPos.z - 20.0f);
  }
}