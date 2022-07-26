#pragma once

#include "scene.hpp"

namespace sasha22 {
    
    class SpinningCubeSceneDemo : public Scene {

    private:
        Shader shd_simpleTexturedCube;

        unsigned int VBO_SpinningCube, VAO_SpinningCube;
        unsigned int txt1_SpinningCube, txt2_SpinningCube;

    public:
        SpinningCubeSceneDemo();
        ~SpinningCubeSceneDemo();

        void update_draw() override;

    };

}