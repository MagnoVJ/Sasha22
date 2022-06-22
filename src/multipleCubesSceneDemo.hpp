#pragma once

#include "scene.hpp"

namespace sasha22 {

    class MultipleCuebesSceneDemo : Scene {
    
    private:
        Shader shd_simpleTexturedCube;

    public:
        MultipleCuebesSceneDemo();
        ~MultipleCuebesSceneDemo();

        void update_draw();

    };

}