#ifndef RENDERER_H
#define RENDERER_H


#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "object.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
};

struct Constants {
    glm::mat4 world;
    glm::mat4 view;
    glm::mat4 projection;
};

class Renderer {
private:
    GLFWwindow* m_window;
    glm::vec3 m_cameraPosition;
    glm::vec3 m_cameraTarget;
    glm::vec3 m_cameraUp;
    glm::mat4 m_view;
    glm::mat4 m_projection;

    unsigned int m_vao, m_vbo, m_ebo;
    unsigned int m_shaderProgram;

    std::vector<Object> m_objects;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    bool m_editMode = false;
    size_t m_selectedObjectIndex = 0;  // Added to track selected object in editor UI
    Assimp::Importer m_importer;
    const aiScene* m_scene;
    std::vector<unsigned int> m_modelVAOs, m_modelVBOs, m_modelEBOs;

public:
    Renderer();
    ~Renderer();

    void Initialize(GLFWwindow* window);
    void Update(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 cameraUp, bool editMode);
    void Render();
    void AddObject(const Object& obj);
    const std::vector<Object>& GetObjects() const;
    void SetEditMode(bool editMode);
    Object* GetSelectedObject(int index);
    void LoadModel(const std::string& path);
};

#endif