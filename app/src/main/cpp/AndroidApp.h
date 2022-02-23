#pragma once

#include <jni.h>
#include <memory>
#include <android/input.h>
#include "GraphicsDevice.h"

class AndroidApp {
public:
    explicit AndroidApp(struct android_app* app);
    ~AndroidApp();

    void loop();

private:
    static void onAppCommand(struct android_app*, i32 cmd);
    static i32 onInputEvent(struct android_app*, AInputEvent* inputEvent);

    struct android_app* app;
    GraphicsDevice renderer {};

    static AndroidApp* instance;
};