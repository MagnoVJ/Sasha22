#pragma once

#include "scene.hpp"
#include "sasha22.hpp"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <utility>

namespace sasha22 {

    class DrawPrimitiveScene : public Scene {

    private:
        // Opts for Draw Primitives (These opts will be moved to drawPrimitiveScene.cpp in the future)
        // For each button in "Primitivas" section, exists an opt
        bool opt_drawPrimitiveScene_point = false;
        bool opt_drawPrimitiveScene_line = false;
        bool opt_drawPrimitiveScene_triangle = false;
        bool opt_drawPrimitiveScene_rect = false;
        bool opt_drawPrimitiveScene_circle = false;

        void drawPrimitiveSceneOptConf(std::string optName);

        //void cleanUp_opt_drawPrimitiveScene_point_variables();

        Shader shd_quad;

        std::map<std::string, float*> mapOfFloatValues;

    public:
        DrawPrimitiveScene();
        void update_draw() override;

    };
}