#pragma once

#include "shader.h"

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <memory>

class Camera {

private:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;
    std::shared_ptr<Shader> ourShader;

public:
    Camera();
    ~Camera();

    void processInput(GLFWwindow* window, float deltaTime, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp);

    void update_draw(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float fov);

};