#include "sasha22.hpp"

#include <stb_image.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdio.h> 
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float yaw       = -90.0f;
float pitch     = 0.0f;
float lastX     = 800.0f / 2.0;
float lastY     = 600.0 / 2.0;
float fov       = 45.0f;

glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

// Application Specific opt
bool opt_spinningCubeSceneDemo = false;
bool opt_multipleCubesSceneDemo = false;
bool opt_navigatingCameraSceneDemo = false;
bool opt_drawPrimitiveScene = true;

// Opts for Draw Primitives (These opts will be moved to drawPrimitiveScene.cpp in the future)
// For each button in "Primitivas" section, exists an opt
bool opt_drawPrimitiveScene_point = false;
bool opt_drawPrimitiveScene_line = false;
bool opt_drawPrimitiveScene_triangle = false;
bool opt_drawPrimitiveScene_rect = false;
bool opt_drawPrimitiveScene_circle = false;

// This function takes a string indicating what primitive you want to draw.
// It sets all the other primitives options to false
// (These function will be moved to drawPrimitiveScene.cpp in the future)
void drawPrimitiveSceneOptConf(std::string optName) {

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

int main() { 
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sasha22", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    glfwMaximizeWindow(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dar ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Our states
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Here you create an instance of the class that represents the functionality(menu) you're using/wants to include
    sasha22::SpinningCubeSceneDemo spinningCubeSceneDemo;
    sasha22::MultipleCuebesSceneDemo multipleCubesSceneDemo;
    sasha22::NavigatingCameraSceneDemo navigatingCameraSceneDemo;
    sasha22::DrawPrimitiveScene drawPrimitiveScene;

    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
  
    // Generate texture
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1366, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1366, 768);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  

    cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);
        
        if(opt_navigatingCameraSceneDemo)
            navigatingCameraSceneDemo.processInput(window, deltaTime, cameraPos, cameraFront, cameraUp);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // -----RENDER GUI -------
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // Because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {

            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {

            if(ImGui::BeginMenu("Menu")) {

                bool lastState = opt_drawPrimitiveScene;
                ImGui::MenuItem("Desenhar", NULL, &opt_drawPrimitiveScene);
                if(lastState != opt_drawPrimitiveScene) {
                    opt_spinningCubeSceneDemo = false;
                    opt_multipleCubesSceneDemo = false;
                    opt_navigatingCameraSceneDemo = false;
                }

                lastState = opt_spinningCubeSceneDemo;
                ImGui::MenuItem("Cubo Girando (Demonstração)", NULL, &opt_spinningCubeSceneDemo);
                if(lastState != opt_spinningCubeSceneDemo) {
                    opt_multipleCubesSceneDemo = false;
                    opt_navigatingCameraSceneDemo = false;
                    opt_drawPrimitiveScene = false;
                }

                lastState = opt_multipleCubesSceneDemo;
                ImGui::MenuItem("Vários Cubos (Demonstração)", NULL, &opt_multipleCubesSceneDemo);
                if(lastState != opt_multipleCubesSceneDemo) {
                    opt_spinningCubeSceneDemo = false;
                    opt_navigatingCameraSceneDemo = false;
                    opt_drawPrimitiveScene = false;
                }

                lastState = opt_navigatingCameraSceneDemo;
                ImGui::MenuItem("Navegar Entre os Cubos (Demonstração)", NULL, &opt_navigatingCameraSceneDemo);
                if(lastState != opt_navigatingCameraSceneDemo) {
                    opt_spinningCubeSceneDemo = false;
                    opt_multipleCubesSceneDemo = false;
                    opt_drawPrimitiveScene = false;
                }

                ImGui::EndMenu();
                
            }

            if (ImGui::BeginMenu("Configurações")) {

                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                // ImGui::MenuItem("Tela Cheia", NULL, &opt_fullscreen);
                // ImGui::MenuItem("Padding", NULL, &opt_padding);
                // ImGui::Separator();
                // if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                // if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                // if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                // if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                // if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                // ImGui::Separator();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
            
        }

        //static float value = 0.0f;
        //ImGui::DragFloat("Value", &value);

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

            ImGui::Begin("Confirmar");
            {
                ImGui::Button("Aceitar");
                ImGui::Button("Cancelar");
            }

            ImGui::End();

        }

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // render
        // ------
        //int display_w, display_h;
        //glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // Drawing the viewport of specific functionality
        if(opt_spinningCubeSceneDemo)
            spinningCubeSceneDemo.update_draw();
        else if(opt_multipleCubesSceneDemo)
            multipleCubesSceneDemo.update_draw();
        else if(opt_navigatingCameraSceneDemo)
            navigatingCameraSceneDemo.update_draw(cameraPos, cameraFront, cameraUp, fov);
        else if(opt_drawPrimitiveScene)
            drawPrimitiveScene.update_draw();

         // Now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // Clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Begin("Janela de Exibição");

        // Get the size of the child (i.e. the whole draw size of the windows).
        ImVec2 wsize = ImGui::GetWindowSize();
        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        ImGui::Image((ImTextureID)textureColorbuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();

        // ------ End of docking --------
        ImGui::End(); 
        
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        // For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup Imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

    if(opt_navigatingCameraSceneDemo) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if(firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

    }
    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if(opt_navigatingCameraSceneDemo) {
        fov -= (float)yoffset;
        if(fov < 1.0f)
            fov = 1.0f;
        if(fov > 45.0f)
            fov = 45.0f;
    }
}