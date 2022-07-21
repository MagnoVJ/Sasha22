//https://solarianprogrammer.com/2013/05/13/opengl-101-drawing-primitives/
/*
    For tomorrow 06/24/2022: Implement Drawing point. You'll have to instantiate the temporary variables/values in the heap (pointers)
    // you'll work with flags, you will verify everytime if these flags are true/false and clean these temporary variables/values based on the flags
    // exemple opt_drawPrimitive_point if its changing from true to false, clean these variables
*/

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

    void DrawPrimitiveScene::update_draw() {

        ImGui::Begin("Primitivas", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking); {
            if(ImGui::Button("Ponto") && !Sasha22::locked) {

                drawPrimitiveSceneOptConf("point");
                
                //mapOfScenes.insert(std::pair<std::string, std::shared_ptr<sasha22::Scene>>("PTR_SC_IDX", ptr_Scene));
                mapOfFloatValues.insert(std::pair<std::string, float*>("CDA_X", new float(0)));
                mapOfFloatValues.insert(std::pair<std::string, float*>("CDA_Y", new float(0)));
                
                Sasha22::locked = true;

            }
            if(ImGui::Button("Linha") && !Sasha22::locked)
                drawPrimitiveSceneOptConf("line");
            if(ImGui::Button("Triângulo") && !Sasha22::locked)
                drawPrimitiveSceneOptConf("triangle");
            if(ImGui::Button("Retângulo") && !Sasha22::locked)
                drawPrimitiveSceneOptConf("rect");
            if(ImGui::Button("Círculo") && !Sasha22::locked)
                drawPrimitiveSceneOptConf("circle");
        } ImGui::End();

        ImGui::Begin("Propriedades" , nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking); {
            if(opt_drawPrimitiveScene_point) {
                // You're going to create a map of pointers (to float). You're going to instantiate a pointer and insert it to the map when
                // opt_drawPrimitiveScene is == true, then this part of the code will be executed. In this part you'll pass to ImGui::DragFloat
                // the reference (in the map of pointers) through index, of the value you instantiated earlier. When you're done (when you press confirm
                // or cancel, and unlock the interface) you'll delete the pointer and remove it from the map.
                // static float xPointPos = 0.0f;
                // static float yPointPos = 0.0f;
                ImGui::DragFloat("Coordenada X", mapOfFloatValues["CDA_X"]);
                ImGui::DragFloat("Coordenada Y", mapOfFloatValues["CDA_Y"]);
            }
        } ImGui::End();

        // In the confirmation section, delete all the pointers and clear the map mapOfFloatValues
        ImGui::Begin("Confirmação" , nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking); {
            
            if(ImGui::Button("Confirmar") || ImGui::Button("Cancelar")) {

                for(std::map<std::string, float*>::iterator it = mapOfFloatValues.begin(); it != mapOfFloatValues.end(); ++it) {
                    delete(it->second);
                }

                mapOfFloatValues.clear();

                opt_drawPrimitiveScene_point = false;
                sasha22::Sasha22::locked = false;

            }
            
        } ImGui::End();        

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

        if(!optName.compare("point")) {
            opt_drawPrimitiveScene_point = true;
        }
        if(!optName.compare("line")) {
            opt_drawPrimitiveScene_line = true;   
        }
        if(!optName.compare("triangle")) {
            opt_drawPrimitiveScene_triangle = true;   
        }
        if(!optName.compare("rect")) {
            opt_drawPrimitiveScene_rect = true;   
        }
        if(!optName.compare("circle")) {
            opt_drawPrimitiveScene_circle = true;   
        }
    }

}