#pragma once

#include <any>
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include <cstdint>
#include <optional>
#include <glm/glm.hpp>

/** I like Javascript <3 */
#define let auto

/*
 * Type aliases for signed and unsigned integer types,
 * both exact and fast, and floating point types.
 */

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using isize = intmax_t;

using i8f = int_fast8_t;
using i16f = int_fast16_t;
using i32f = int_fast32_t;
using i64f = int_fast64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usize = size_t;

using u8f = uint_fast8_t;
using u16f = uint_fast16_t;
using u32f = uint_fast32_t;
using u64f = uint_fast64_t;

using f32 = float;
using f64 = double;

/*
 * Constants for the maximum values for each
 * of the integer types, both exact and fast.
 */

constexpr const i8 I8_MAX = INT8_MAX;
constexpr const i16 I16_MAX = INT16_MAX;
constexpr const i32 I32_MAX = INT32_MAX;
constexpr const i64 I64_MAX = INT64_MAX;
constexpr const isize ISIZE_MAX = INT32_MAX;

constexpr const i8f I8F_MAX = INT_FAST8_MAX;
constexpr const i16f I16F_MAX = INT_FAST16_MAX;
constexpr const i32f I32F_MAX = INT_FAST32_MAX;
constexpr const i64f I64F_MAX = INT_FAST64_MAX;

constexpr const u8 U8_MAX = UINT8_MAX;
constexpr const u16 U16_MAX = UINT16_MAX;
constexpr const u32 U32_MAX = UINT32_MAX;
constexpr const u64 U64_MAX = UINT64_MAX;
constexpr const usize USIZE_MAX = SIZE_T_MAX;

constexpr const u8f U8F_MAX = UINT_FAST8_MAX;
constexpr const u16f U16F_MAX = UINT_FAST16_MAX;
constexpr const u32f U32F_MAX = UINT_FAST32_MAX;
constexpr const u64f U64F_MAX = UINT_FAST64_MAX;

/*
 * Fixed-size type aliases for the glm vectors,
 * floating point, integral signed and unsigned.
 */

using vec2 = glm::f32vec2;
using vec3 = glm::f32vec3;
using vec4 = glm::f32vec4;

using glm::i8vec2;
using glm::i8vec3;
using glm::i8vec4;
using glm::i16vec2;
using glm::i16vec3;
using glm::i16vec4;
using ivec2 = glm::i32vec2;
using ivec3 = glm::i32vec3;
using ivec4 = glm::i32vec4;

using glm::u8vec2;
using glm::u8vec3;
using glm::u8vec4;
using glm::u16vec2;
using glm::u16vec3;
using glm::u16vec4;
using uvec2 = glm::u32vec2;
using uvec3 = glm::u32vec3;
using uvec4 = glm::u32vec4;

/*
 * De-namespace common data structures,
 * vector => vec for conciseness.
 */

using std::array;
using std::string;
template <typename T>
using vec = std::vector<T>;

/*
 * Shorthands for smart pointer types.
 */

template <typename T>
using sptr = std::shared_ptr<T>;
template <typename T>
using uptr = std::unique_ptr<T>;
template <typename T>
using wptr = std::weak_ptr<T>;

/*
 * De-namespace smart pointer helpers.
 */

using std::make_shared;
using std::make_unique;

/*
 * De-namespace common containers.
 */

using std::any;
using std::tuple;
using std::variant;
using std::optional;

using std::any_cast;