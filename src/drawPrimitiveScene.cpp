//https://solarianprogrammer.com/2013/05/13/opengl-101-drawing-primitives/

#include "drawPrimitiveScene.hpp"

namespace sasha22 {

    DrawPrimitiveScene::DrawPrimitiveScene() 
            : shd_quad("./src/shaders/quad_vs.glsl", "./src/shaders/quad_fs.glsl") {
        
        float vertices[] = {
            .5f,  .5f, 0.0f, // top right
            .5f, -.5f, 0.0f, // bottom right
           -.5f, -.5f, 0.0f, // bottom left
           -.5f,  .5f, 0.0f  // top left
        };
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        //Creation of OpenGL objects (and its configuration) for drawing a quand on the screen
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void DrawPrimitiveScene::update_draw(bool opt_drawPrimitiveScene) {

        if(opt_drawPrimitiveScene) {

            ImGui::Begin("Primitivas"); 
            {
                if(ImGui::Button("Ponto"))
                    drawPrimitiveSceneOptConf("point");
                if(ImGui::Button("Linha"))
                    drawPrimitiveSceneOptConf("line");
                if(ImGui::Button("Triângulo"))
                    drawPrimitiveSceneOptConf("triangle");
                if(ImGui::Button("Retângulo"))
                    drawPrimitiveSceneOptConf("rect");
                if(ImGui::Button("Círculo"))
                    drawPrimitiveSceneOptConf("circle");
            }
            ImGui::End();

            ImGui::Begin("Propriedades");
            {
                if(opt_drawPrimitiveScene_point) {
                    static float xPointPos = 0.0f;
                    static float yPointPos = 0.0f;
                    ImGui::DragFloat("Coordenada X", &xPointPos);
                    ImGui::DragFloat("Coordenada Y", &yPointPos);
                }
            }
            ImGui::End();

            ImGui::Begin("Confirmação");
            {
                ImGui::Button("Confirmar");
                ImGui::Button("Cancelar");
            }

            ImGui::End();

        }

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
        shd_quad.use();
        shd_quad.setMat4("transform", transform);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }

    // This function takes a string indicating what primitive you want to draw.
    // It sets all the other primitives options to false
    void DrawPrimitiveScene::drawPrimitiveSceneOptConf(std::string optName) {

        opt_drawPrimitiveScene_point = false;
        opt_drawPrimitiveScene_line = false;
        opt_drawPrimitiveScene_triangle = false;
        opt_drawPrimitiveScene_rect = false;
        opt_drawPrimitiveScene_circle = false;

        int res = -1;
        res = optName.compare("point");
        if(res == 0) {
            opt_drawPrimitiveScene_point = true;   
        }
        res = optName.compare("line");
        if(res == 0) {
            opt_drawPrimitiveScene_line = true;   
        }
        res = optName.compare("triangle");
        if(res == 0) {
            opt_drawPrimitiveScene_triangle = true;   
        }
        res = optName.compare("rect");
        if(res == 0) {
            opt_drawPrimitiveScene_rect = true;   
        }
        res = optName.compare("circle");
        if(res == 0) {
            opt_drawPrimitiveScene_circle = true;   
        }
    }

}