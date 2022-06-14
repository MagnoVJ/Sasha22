#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <stdio.h>
#include <iostream>

class Point {

private:
    unsigned int VBO, VAO, EBO;
    std::shared_ptr<Shader> shd;

public:
    Point();
    void UpdateAndDraw();

};