
#pragma once
#ifndef WORLD_ENGINE_H
#define WORLD_ENGINE_H

#include "renderer.h"
#include "physics.h"
#include "ai.h"

class Window;

class WorldEngine {
private:
glm::vec3 m_cameraPosition;
glm::vec3 m_cameraTarget;
glm::vec3 m_cameraUp;
glm::mat4 m_view;
glm::mat4 m_projection;

Renderer m_renderer;
Physics m_physics;
AI m_ai;
bool m_editMode = false;

public:
WorldEngine();
~WorldEngine();

bool Run(Window& window);
void Initialize(Window& window);
void ToggleEditMode();
bool IsEditMode() const;
void Update(float deltaTime);

};

#endif