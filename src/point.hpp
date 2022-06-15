#include "shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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