#pragma once

#include "shader.h"
#include "scene.hpp"

#include <stb_image.h>

//glm
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <memory>

namespace sasha22 {

    class NavigatingCameraSceneDemo : Scene {

    private:
        Shader shd_simpleTexturedCube;

    public:
        NavigatingCameraSceneDemo();
        ~NavigatingCameraSceneDemo();

        void processInput(GLFWwindow* window, float deltaTime, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp);

        void update_draw(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float fov);

    };

}