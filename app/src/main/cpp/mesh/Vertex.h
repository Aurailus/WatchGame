#pragma once

#include "../util/Type.h"

namespace detail {
    template <typename T> struct PrimitiveGLType {};

    template <> struct PrimitiveGLType<i8>  { constexpr static u32 gl_type = GL_BYTE; };
    template <> struct PrimitiveGLType<u8>  { constexpr static u32 gl_type = GL_UNSIGNED_BYTE; };
    template <> struct PrimitiveGLType<i16> { constexpr static u32 gl_type = GL_SHORT; };
    template <> struct PrimitiveGLType<u16> { constexpr static u32 gl_type = GL_UNSIGNED_SHORT; };
    template <> struct PrimitiveGLType<i32> { constexpr static u32 gl_type = GL_INT; };
    template <> struct PrimitiveGLType<u32> { constexpr static u32 gl_type = GL_UNSIGNED_INT; };
    template <> struct PrimitiveGLType<f32> { constexpr static u32 gl_type = GL_FLOAT; };

    enum class NumberMode { Int, Float, FloatNormalized };

    template <typename T, typename _ = void>
    struct Attribute {
        typedef T type;
        typedef T primitive;
        constexpr static NumberMode mode = std::is_integral_v<T> ? NumberMode::Int : NumberMode::Float;
        constexpr static u32 size = sizeof(T);
        constexpr static u32 gl_type = PrimitiveGLType<T>::gl_type;
        constexpr static u32 components = 1;
    };

    template <typename T>
    struct Attribute<T, typename std::enable_if<std::is_integral_v<typename T::length_type>>::type> : Attribute<typename T::value_type> {
        typedef T type;
        constexpr static u32 components = T::length();
    };

    template <typename T, bool N,
            std::enable_if_t<std::is_integral_v<typename Attribute<T>::primitive> ||
            std::is_floating_point_v<typename Attribute<T>::primitive>, bool> = true>
    struct Floating {
        typedef T type;
        constexpr static bool normalize = N;
    };

    template <typename T>
    struct Attribute<T, typename std::enable_if<std::is_same_v<T, Floating<typename T::type, T::normalize>>>::type> : Attribute<typename T::type> {
        constexpr static NumberMode mode = T::normalize ? NumberMode::FloatNormalized : NumberMode::Float;
    };

    template <typename T, u32 I = 0, typename... Args>
    constexpr inline auto getAttributesTuple() {
        if constexpr (I < std::tuple_size_v<T>) return getAttributesTuple<T, I + 1, Args..., Attribute<std::tuple_element_t<I, T>>>();
        else return std::tuple<Args...>{};
    }

    template <typename T>
    struct Type {
        typedef T type;
    };

    template <typename T, bool N>
    struct Type<Floating<T, N>> {
        typedef T type;
    };

    template <typename T, u32 I = 0, typename... Args>
    constexpr inline auto getTypesTuple() {
        if constexpr (I < std::tuple_size_v<T>) return getTypesTuple<T, I + 1, Args..., typename Type<std::tuple_element_t<I, T>>::type>();
        else return std::tuple<Args...>{};
    }

    template<typename T, typename _ = void>
    struct is_vertex : std::false_type {};

    template <typename T>
    struct is_vertex<T, typename std::enable_if<std::tuple_size_v<typename T::attributes_type> != 0>::type> : std::true_type {};

    template<typename T>
    constexpr bool is_vertex_v = is_vertex<T>::value;
}

template <typename T, bool N = false>
using Floating = detail::Floating<T, N>;

template <typename... T>
struct Vertex {
    typedef decltype(detail::getTypesTuple<std::tuple<T...>>()) types_tuple;
    typedef decltype(detail::getAttributesTuple<std::tuple<T...>>()) attributes_tuple;

    template <typename... A>
    Vertex(const A&... data): data(std::make_tuple(data...)) {};

    types_tuple data;
};

/// Position, Normal, Color
typedef Vertex<vec3, vec3, u8vec3> SimpleVertex;