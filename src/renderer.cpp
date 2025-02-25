#include "renderer.h"
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Renderer::Renderer() {}

Renderer::~Renderer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteProgram(m_shaderProgram);
    for (unsigned int vao : m_modelVAOs) glDeleteVertexArrays(1, &vao);
    for (unsigned int vbo : m_modelVBOs) glDeleteBuffers(1, &vbo);
    for (unsigned int ebo : m_modelEBOs) glDeleteBuffers(1, &ebo);
}

void Renderer::Initialize(GLFWwindow* window) {
    m_window = window;

    // Initial objects: terrain and cube (AI character)
    AddObject(Object("Terrain", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(10.0f, 1.0f, 10.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    AddObject(Object("AI Character", glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));

    // Set up OpenGL
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Shader program
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        out vec4 vertexColor;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            vertexColor = aColor;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec4 vertexColor;
        out vec4 FragColor;
        void main() {
            FragColor = vertexColor;
        }
    )";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glEnable(GL_DEPTH_TEST);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Renderer::Update(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 cameraUp, bool editMode) {
    m_editMode = editMode;
    m_cameraPosition = cameraPos;
    m_cameraTarget = cameraTarget;
    m_cameraUp = cameraUp;

    m_view = glm::lookAt(m_cameraPosition, m_cameraTarget, m_cameraUp);
    m_projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);

    // Update vertices and indices based on objects
    m_vertices.clear();
    m_indices.clear();

    for (const auto& obj : m_objects) {
        float sizeX = obj.scale.x, sizeY = obj.scale.y, sizeZ = obj.scale.z;
        glm::vec3 pos = obj.position;
        glm::vec4 col = obj.color;

        // Example: Cube vertices (simplified for each object, assuming cube-like shape)
        std::vector<Vertex> cubeVertices = {
            { glm::vec3(-sizeX/2 + pos.x, -sizeY/2 + pos.y, -sizeZ/2 + pos.z), col },
            { glm::vec3(sizeX/2 + pos.x, -sizeY/2 + pos.y, -sizeZ/2 + pos.z), col },
            { glm::vec3(-sizeX/2 + pos.x, sizeY/2 + pos.y, -sizeZ/2 + pos.z), col },
            { glm::vec3(sizeX/2 + pos.x, sizeY/2 + pos.y, -sizeZ/2 + pos.z), col },
            { glm::vec3(-sizeX/2 + pos.x, -sizeY/2 + pos.y, sizeZ/2 + pos.z), col },
            { glm::vec3(sizeX/2 + pos.x, -sizeY/2 + pos.y, sizeZ/2 + pos.z), col },
            { glm::vec3(-sizeX/2 + pos.x, sizeY/2 + pos.y, sizeZ/2 + pos.z), col },
            { glm::vec3(sizeX/2 + pos.x, sizeY/2 + pos.y, sizeZ/2 + pos.z), col }
        };
        std::vector<unsigned int> cubeIndices = {
            0, 1, 2, 2, 1, 3, // Front
            4, 5, 6, 6, 5, 7, // Back
            0, 1, 4, 4, 1, 5, // Bottom
            2, 3, 6, 6, 3, 7, // Top
            0, 2, 4, 4, 2, 6, // Left
            1, 3, 5, 5, 3, 7  // Right
        };

        size_t baseIndex = m_vertices.size();
        m_vertices.insert(m_vertices.end(), cubeVertices.begin(), cubeVertices.end());
        for (unsigned int idx : cubeIndices) {
            m_indices.push_back(static_cast<unsigned int>(idx + baseIndex));
        }
    }

    // Update buffers if vertices/indices changed
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Renderer::Render() {
    glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!m_editMode) {
        glUseProgram(m_shaderProgram);

        // Set matrices
        glm::mat4 model = glm::mat4(1.0f); // Identity matrix
        unsigned int modelLoc = glGetUniformLocation(m_shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(m_shaderProgram, "view");
        unsigned int projectionLoc = glGetUniformLocation(m_shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Render maid model (if loaded)
        for (size_t i = 0; i < m_modelVAOs.size(); ++i) {
            glBindVertexArray(m_modelVAOs[i]);
            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0); // Adjust indices based on model
            glBindVertexArray(0);
        }
    }

    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Editor UI
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Edit")) {
        if (ImGui::MenuItem("Toggle Edit Mode", nullptr, &m_editMode)) {}
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    ImGui::Begin("World Editor");

    // Object List
    if (ImGui::CollapsingHeader("Objects")) {
        for (size_t i = 0; i < m_objects.size(); ++i) {
            if (ImGui::Selectable(m_objects[i].name.c_str(), i == m_selectedObjectIndex)) {
                m_selectedObjectIndex = i;
            }
        }
    }

    // Inspector
    if (ImGui::CollapsingHeader("Inspector")) {
        if (m_selectedObjectIndex < m_objects.size()) {  // Use m_selectedObjectIndex directly
            Object& obj = m_objects[m_selectedObjectIndex];
            char nameBuffer[256];  // Buffer for ImGui::InputText
            strcpy_s(nameBuffer, obj.name.c_str());
            if (ImGui::InputText("Name", nameBuffer, IM_ARRAYSIZE(nameBuffer))) {
                obj.name = nameBuffer;
            }
            ImGui::InputFloat3("Position", &obj.position.x);
            ImGui::InputFloat3("Rotation", &obj.rotation.x);
            ImGui::InputFloat3("Scale", &obj.scale.x);
            ImGui::ColorEdit4("Color", &obj.color.x, ImGuiColorEditFlags_AlphaOpaque);
        }
    }

    // Content Management
    if (ImGui::CollapsingHeader("Content")) {
        static char assetPath[256] = "";
        ImGui::InputText("Asset Path", assetPath, IM_ARRAYSIZE(assetPath));
        if (ImGui::Button("Add Asset")) {
            Object newObject("New Asset", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec4(1.0f));
            AddObject(newObject);
        }
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET")) {
                Object newObject("Dragged Asset", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec4(1.0f));
                AddObject(newObject);
            }
            ImGui::EndDragDropTarget();
        }
    }

    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
}

void Renderer::AddObject(const Object& obj) {
    m_objects.push_back(obj);
    Update(m_cameraPosition, m_cameraTarget, m_cameraUp, m_editMode);
}

const std::vector<Object>& Renderer::GetObjects() const {
    return m_objects;
}

void Renderer::SetEditMode(bool editMode) {
    m_editMode = editMode;
}

Object* Renderer::GetSelectedObject(int index) {
    if (index >= 0 && index < static_cast<int>(m_objects.size())) {
        return &m_objects[index];
    }
    return nullptr;
}

void Renderer::LoadModel(const std::string& path) {
    m_scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) {
        std::cerr << "Error loading model: " << m_importer.GetErrorString() << std::endl;
        return;
    }

    for (unsigned int i = 0; i < m_scene->mNumMeshes; ++i) {
        aiMesh* mesh = m_scene->mMeshes[i];
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
            vertices.push_back({
                glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z),
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // Default color, adjust as needed
            });
        }

        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                indices.push_back(face.mIndices[k]);
            }
        }

        unsigned int vao, vbo, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_modelVAOs.push_back(vao);
        m_modelVBOs.push_back(vbo);
        m_modelEBOs.push_back(ebo);
    }
}