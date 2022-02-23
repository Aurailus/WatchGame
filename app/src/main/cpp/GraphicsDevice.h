#pragma once

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android_native_app_glue.h>

#include "util/Type.h"

class GraphicsDevice {
public:
    void init(ANativeWindow* newWindow);
    void cleanup();

    inline bool isPrepared() { return window; }

    void beginRender();
    void swapBuffer();

private:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    ivec2 windowSize {};
    ANativeWindow *window;
};