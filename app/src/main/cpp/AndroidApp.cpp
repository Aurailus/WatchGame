#include "AndroidApp.h"

#include "util/Util.h"
#include "util/Ensure.h"
#include "Log.h"
#include "mesh/Vertex.h"
#include "mesh/Mesh.h"

AndroidApp* AndroidApp::instance {};

AndroidApp::AndroidApp(struct android_app* app): app(app) {
    ensure(!AndroidApp::instance, "Only one AndroidApp can exist at once.");
    AndroidApp::instance = this;

    app->onAppCmd = AndroidApp::onAppCommand;
    app->onInputEvent = AndroidApp::onInputEvent;

    typedef Vertex<vec4, u16vec2, u8> WeirdVertex;
    WeirdVertex v {vec4(1, 1, 0, 1), u16vec2(0, 1), 1 };

    Mesh<WeirdVertex> m(vec<WeirdVertex> { v }, vec<u32> { 0 });

    Info("%u", sizeof(SimpleVertex));
    Info("hi %f %u", std::get<0>(v.data).x, m.VAO);
}

AndroidApp::~AndroidApp() {
    AndroidApp::instance = nullptr;
}

void AndroidApp::loop() {
    volatile bool destroyRequested = false;
    while (!destroyRequested) {
        i32 events = -1;
        struct android_poll_source* source = nullptr;

        while (ALooper_pollAll(0, nullptr, &events, (void **)&source) >= 0) {
            if (source != nullptr) source->process(app, source);
            if (app->destroyRequested != 0) destroyRequested = true;
        }

        if (!renderer.isPrepared()) continue;

        renderer.beginRender();

        // Render code

        renderer.swapBuffer();
    }
}

void AndroidApp::onAppCommand(struct android_app*, i32 cmd) {
    switch (cmd) {
        default:
            break;
        case APP_CMD_INIT_WINDOW:
            instance->renderer.init(instance->app->window);
            break;
        case APP_CMD_TERM_WINDOW:
            instance->renderer.cleanup();
            break;
    }
}

i32 AndroidApp::onInputEvent(struct android_app*, AInputEvent *inputEvent) {
    if (AInputEvent_getType(inputEvent) == AINPUT_EVENT_TYPE_KEY
        && AKeyEvent_getKeyCode(inputEvent) == AKEYCODE_BACK) {
        ANativeActivity_finish(instance->app->activity);
        return 1;
    }

    if (AInputEvent_getType(inputEvent) == AINPUT_EVENT_TYPE_MOTION) {
        // TODO: Handle touch event...
        return 1;
    }

    return 0;
}