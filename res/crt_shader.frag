#version 330 core

in vec2 fragTexCoord;       // Fragment input attribute: texture coordinate
in vec4 fragColor;          // Fragment input attribute: color
out vec4 finalColor;        // Fragment output: color

uniform sampler2D texture0;
uniform float u_time;
uniform vec2 u_size;

void main() {
    vec2 suv = fragTexCoord;

    vec4 colorOutput;
    colorOutput = vec4(1.5 * sin(suv.y * u_size.y / 3 + u_time * 15));
    colorOutput = 1.0 - floor(abs(colorOutput));
    colorOutput *= 1.1 * vec4(sin(1.0 - suv.y), 0, cos(1.0 - suv.y * 2), 1);
    colorOutput *= texture(texture0, suv);

    // Convert the color output to grayscale
    float grayscale = dot(colorOutput.rgb, vec3(0.299, 0.587, 0.114));

    // Set a small threshold for black. If the grayscale value is below this, it will be transparent.
    float alpha = (grayscale > 0.05) ? 1.0 : 0.0;

    finalColor = vec4(vec3(grayscale), alpha);
}
