#pragma once

#include "../util/Type.h"

class Shader {
public:
    enum class Type { Vertex, Fragment };

    struct Source {
        Type type;
        const char* data;
    };

    template <usize L>
    Shader(const array<Source, L>& sources) {
        i32 result = 0;

        shaderID = glCreateProgram();
        if (!shaderID) ensure(false, "Failed to create shader program: "
            + std::to_string(glGetError()));

        for (const Source& source : sources) addSource(source.type, source.data);

        glLinkProgram(shaderID);
        glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
        if (!result) {
            GLchar eLog[1024] = {};
            glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
            ensure(false, string("Failed to link shader program:\n ") + string(eLog));
        }

        glValidateProgram(shaderID);
        glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
        if (!result) {
            GLchar eLog[1024] = {};
            glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
            ensure(false, string("Failed to validate shader program:\n ") + string(eLog));
        }
    }

private:
    void addSource(Type type, const char* data) {
        u32 shader = glCreateShader(type == Type::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

        i32 dataLen = strlen(data);
        glShaderSource(shader, 1, &data, &dataLen);
        glCompileShader(shader);

        i32 result = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (!result) {
            GLchar eLog[1024] = { 0 };
            glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
            ensure(false, string("Failed to compile shader:\n ") + string(eLog));
        }

        glAttachShader(shader, shader);
    }

    u32f shaderID;
};