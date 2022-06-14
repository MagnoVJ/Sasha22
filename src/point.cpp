#include "point.hpp"

Point::Point() {

    shd = std::make_shared<Shader>("./src/shaders/point_vs.glsl", "./src/shaders/point_fs.glsl");
    
    float vertices[] = {
        .5f, .5f, 0.0f, // top right
        .5f, -.5f, 0.0f, // bottom right
        -.5f, -.5f, 0.0f, // bottom left
        -.5f, .5f, 0.0f // top left
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

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

void Point::UpdateAndDraw() {

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));

    shd->use();

    shd->setMat4("transform", transform);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}