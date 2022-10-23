#version 330 core
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D faceTexture;

void main() {
    FragColor = texture(faceTexture, texCoord);
}
