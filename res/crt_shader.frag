#version 330 core

in vec2 fragTexCoord;       // Fragment input attribute: texture coordinate
in vec4 fragColor;          // Fragment input attribute: color
out vec4 finalColor;        // Fragment output: color

uniform sampler2D texture0;
uniform float time;
uniform vec2 size;

void main() {
    vec2 suv = fragTexCoord;

    finalColor = vec4(1.5 * sin(suv.y * size.y / 3 + time * 15));
    finalColor = 1.0 - floor(abs(finalColor));
    finalColor *= 1.1 * vec4(sin(1.0 - suv.y), 0, cos(1.0 - suv.y * 2), 1);
    finalColor *= texture(texture0, suv);
}