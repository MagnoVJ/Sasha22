#include "spinningCubeSceneDemo.hpp"

namespace sasha22 {

    SpinningCubeSceneDemo::SpinningCubeSceneDemo() 
            : shd_simpleTexturedCube("./src/shaders/simpleTexturedCube_vs.glsl", "./src/shaders/simpleTexturedCube_fs.glsl") {

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[180];
        int i = 0;

        // Reading file
        std::ifstream cubeFile;
        std::string cubeFileString;

        cubeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {

            cubeFile.open("./cube.sgf");
            std::stringstream cubeStringStream;
            cubeStringStream << cubeFile.rdbuf();
            cubeFile.close();
            cubeFileString = cubeStringStream.str();

            for(auto it = cubeFileString.cbegin(); it != cubeFileString.cend(); ++it) {

                if(*it == '{') {

                    while(*it != '}') {
                        ++it;
                        std::stringstream ss;
                        while(*it != ',' && *it != ' ' && *it != '\n' && *it != '}') {
                            ss << *it;
                            ++it;
                        }
                        std::string s = ss.str();
                        if(s != "") {
                            vertices[i] = std::stof(s);
                            i++;
                        }

                    }   
                }
            }

        } catch(std::ifstream::failure& e) {
            std::cout << "ERROR::COULDN'T READ CUBE GEOMETRY FILE" << std::endl;
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // load and create a texture 
        // -------------------------
        // texture 1
        // ---------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1); 
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load("./assets/images/wall.jpg", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        // texture 2
        // ---------
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("./assets/images/awesomeface.png", &width, &height, &nrChannels, 0);
        if (data) {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        shd_simpleTexturedCube.use(); // don't forget to activate/use the shader before setting uniforms!
        // either set it manually like so:
        glUniform1i(glGetUniformLocation(shd_simpleTexturedCube.ID, "texture1"), 0);
        // or set it via the texture class
        shd_simpleTexturedCube.setInt("texture2", 1);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // glBindVertexArray(0);

    }

    SpinningCubeSceneDemo::~SpinningCubeSceneDemo() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }


    void SpinningCubeSceneDemo::update_draw() {

        ImGui::Begin("Bem-Vindo!");
        {
            ImGui::Text("             Seja Bem-Vindo ao Sasha22!\n\nSasha22 é uma ferramenta para trabalhar com as mais\ndiversas aplicações gráficas 2D ou 3D.");
        }
        ImGui::End();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        shd_simpleTexturedCube.use();

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(shd_simpleTexturedCube.ID, "model");
        unsigned int viewLoc  = glGetUniformLocation(shd_simpleTexturedCube.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        shd_simpleTexturedCube.setMat4("projection", projection);

        // render box
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
}