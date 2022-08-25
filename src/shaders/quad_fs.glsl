#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    //FragColor = texture(texture1, TexCoord);
    vec2 st = gl_FragCoord.xy/vec2(1920, 1080);
    vec3 canvas = vec3(1.0);
    float circle = 0.0;

    circle = distance(st, vec2(0.5));

    canvas = canvas * circle;

    gl_FragColor = vec4(canvas, 1.0);
}