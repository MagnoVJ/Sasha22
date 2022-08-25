//https://solarianprogrammer.com/2013/05/13/opengl-101-drawing-primitives/
/*
    For tomorrow 06/24/2022: Implement Drawing point. You'll have to instantiate the temporary variables/values in the heap (pointers)
    // you'll work with flags, you will verify everytime if these flags are true/false and clean these temporary variables/values based on the flags
    // exemple opt_drawPrimitive_point if its changing from true to false, clean these variables
*/

#include "drawPrimitiveScene.hpp"

namespace sasha22 {

    DrawPrimitiveScene::DrawPrimitiveScene() : shd_quad("./src/shaders/quad_vs.glsl", "./src/shaders/quad_fs.glsl") {
        
        float vertices[] = {
            // positions          // colors           // texture coords
            1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
           -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
           -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        glGenVertexArrays(1, &VAO_Quad);
        glGenBuffers(1, &VBO_Quad);
        glGenBuffers(1, &EBO_Quad);
        glBindVertexArray(VAO_Quad);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Quad);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Quad);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glGenTextures(1, &TXT_Quad);
        glBindTexture(GL_TEXTURE_2D, TXT_Quad); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char* data = stbi_load("./assets/images/GhoststarFINISHED.png", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    
    }

    void DrawPrimitiveScene::update_draw() {

        ImGui::Begin("Primitivas", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking); {
            if(ImGui::Button("Ponto") && !Sasha22::locked) {

                drawPrimitiveSceneOptConf("point");
                
                // mapOfScenes.insert(std::pair<std::string, std::shared_ptr<sasha22::Scene>>("PTR_SC_IDX", ptr_Scene));
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
            
            if(opt_drawPrimitiveScene_point) {

                if(ImGui::Button("Confirmar")) {

                    float normX = 0;
                    float normY = 0;

                    // if(mapOfFloatValues["CDA_X"] != nullptr) {
                    //     auto value = mapOfFloatValues.find("CDA_X");
                    //     normX = *(value->second);
                    // }

                    //if(mapOfFloatValues["CDA_X"] != nullptr)
                    normX = 2 * (*(mapOfFloatValues["CDA_X"]) - 0) / (1549 - 0) - 1;
                    normY = 2 * (*(mapOfFloatValues["CDA_Y"]) - 0) / (990 - 0) - 1;

                    ShaProp prop;
                    prop.posX = normX;
                    prop.posY = normY;

                    vectorProp.push_back(prop);

                    for(std::map<std::string, float*>::iterator it = mapOfFloatValues.begin(); it != mapOfFloatValues.end(); ++it) {
                        delete(it->second);
                    }
                    mapOfFloatValues.clear();
                    opt_drawPrimitiveScene_point = false;
                    sasha22::Sasha22::locked = false;

                }
                if(ImGui::Button("Cancelar")) {
                    for(std::map<std::string, float*>::iterator it = mapOfFloatValues.begin(); it != mapOfFloatValues.end(); ++it) {
                        delete(it->second);
                    }
                    mapOfFloatValues.clear();
                    opt_drawPrimitiveScene_point = false;
                    sasha22::Sasha22::locked = false;
                }

            }
            
            
        } ImGui::End();

        for(auto iVec = vectorProp.begin(); iVec < vectorProp.end(); iVec++) {

            glBindTexture(GL_TEXTURE_2D, TXT_Quad);
            glm::mat4 transform = glm::mat4(1.0f);
            // How to convert screen resolution to -> glm::vec3(0.0f, 0.0f, 0.0f) 
            transform = glm::translate(transform, glm::vec3(iVec->posX, iVec->posY, 0.0f));
            // The aspect ratio of the viewport is = 1.7777 and the aspect ratio of the view window is 1.564. Let's settle with 1.6
            // 1,1 is 1980/1549, 990/1080 = 1.6
            /*
                0.5 --- 1.6
                x  --- 1
                1.6x = 0.5
                x = 0.3125
                
                The ratio between width and height needs to be 0.3125
            */
            transform = glm::scale(transform, glm::vec3(0.3125f, 0.5f, 1.0f));
            shd_quad.use();
            shd_quad.setMat4("transform", transform);
            glBindVertexArray(VAO_Quad);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }

    }

    // This function takes a string indicating what primitive you want to draw.
    // It sets all the other primitive options to false
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