#include <cstdlib>
#include "GraphicsDevice.h"

#include "Log.h"
#include "util/Ensure.h"

void GraphicsDevice::init(ANativeWindow* newWindow) {
    Info("initialized gfx");
    window = newWindow;

    const i32 displayAttribList[] = { EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE };
    const i32 contextAttribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    ensure(window, "Failed to initialize window.");

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    i32 configNumber = -1;
    i32 configAttrib = -1;
    EGLConfig config = nullptr;
    eglChooseConfig(display, displayAttribList, &config, 1, &configNumber);
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &configAttrib);

    ANativeWindow_setBuffersGeometry(window, 0, 0, configAttrib);

    surface = eglCreateWindowSurface(display, config, window, nullptr);
    context = eglCreateContext(display, config, nullptr, contextAttribList);

    eglMakeCurrent(display, surface, surface, context);

    eglQuerySurface(display, surface, EGL_WIDTH, &windowSize.x);
    eglQuerySurface(display, surface, EGL_HEIGHT, &windowSize.y);
}

void GraphicsDevice::cleanup() {
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);

    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
    display = EGL_NO_DISPLAY;
}

void GraphicsDevice::beginRender() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0.7, 1, 1);
}

void GraphicsDevice::swapBuffer() {
    eglSwapBuffers(display, surface);
}
