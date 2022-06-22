#pragma once

#include "shader.h"

#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <memory>

namespace sasha22 {

    const unsigned int SCR_WIDTH = 1366;
    const unsigned int SCR_HEIGHT = 768;

    class Scene {

    protected:
        unsigned int VBO, VAO, EBO;
        unsigned int texture1, texture2;

    };

}