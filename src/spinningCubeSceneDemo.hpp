#pragma once

#include "scene.hpp"

namespace sasha22 {
    
    class SpinningCubeSceneDemo : Scene {

    private:
        Shader shd_simpleTexturedCube;

    public:
        SpinningCubeSceneDemo();
        ~SpinningCubeSceneDemo();

        void update_draw();

    };

}