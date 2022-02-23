#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "../util/Type.h"

template<typename V>
class Mesh {
public:
    Mesh() = default;
    template<typename VA, typename IA>
    Mesh(const VA& vertices, const IA& indices) {
        create(vertices, indices);
    }

    template<typename VA, typename IA, std::enable_if_t<std::is_same_v<typename IA::value_type, u32> && std::is_same_v<typename VA::value_type, V>, bool> = true>
    void create(const VA& vertices, const IA& indices) {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32),
                     (void*)(&indices.front()), GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(typename VA::value_type),
                     (void*)(&vertices.front()), GL_STATIC_DRAW);

        createVertexAttrib<>();
    }

    template <u16f I = 0, usize O = 0>
    inline void createVertexAttrib() {
        typedef std::tuple_element_t<I, typename V::attributes_tuple> attr;

        glEnableVertexAttribArray(I);

        //Info("Adding Attribute #%i of type %i with %i components, each taking %i bytes at an offset of %i.",
        //     I, attr::gl_type, attr::components, sizeof(typename attr::primitive), O);

        if constexpr (std::is_integral_v<typename attr::primitive>) {
            glVertexAttribIPointer(I, attr::components, attr::gl_type, sizeof(V), (void *) O);
        }
        else {
            glVertexAttribPointer(I, attr::components, attr::gl_type, false, sizeof(V), (void *) O);
        }

        if constexpr (I + 1 < std::tuple_size<typename V::attributes_tuple>())
            createVertexAttrib<I + 1, O + sizeof(typename attr::type)>();
    }

    u32 VAO, VBO, IBO;
};

typedef Mesh<SimpleVertex> SimpleMesh;