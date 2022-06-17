#pragma once

#include "shader.h"
#include "scene.hpp"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <stdio.h>
#include <iostream>

namespace sasha22 {

    class DrawPrimitiveScene : Scene {

    public:
        DrawPrimitiveScene();
        void update_draw();

    };
}