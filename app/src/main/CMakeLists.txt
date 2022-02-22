cmake_minimum_required(VERSION 3.18.1)
project(Roguelike)

add_library(appglue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
include_directories(${ANDROID_NDK}/sources/android/native_app_glue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SRC)

#set(SRC ${SRC} cpp/Log.h)
set(SRC ${SRC} cpp/GraphicsDevice.cpp)
set(SRC ${SRC} cpp/AndroidApp.cpp)
set(SRC ${SRC} cpp/main.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC})
target_link_libraries(${PROJECT_NAME} android appglue log EGL GLESv2)