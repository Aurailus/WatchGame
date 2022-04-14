#pragma once

const char* VertexSource = R"glsl(#version 300 es

in vec3 aPos;
in vec3 aNormal;
in uvec3 aColor;

out vec3 pos;
out vec3 normal;
out vec3 color;

void main() {
    pos = aPos;
    normal = aNormal;
    color = vec3(aColor);
}
)glsl";