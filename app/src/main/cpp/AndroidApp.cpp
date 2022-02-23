#include "AndroidApp.h"

#include "util/Util.h"
#include "util/Ensure.h"
#include "Log.h"

AndroidApp* AndroidApp::instance {};

AndroidApp::AndroidApp(struct android_app* app): app(app) {
    ensure(!AndroidApp::instance, "Only one AndroidApp can exist at once.");
    AndroidApp::instance = this;

    //app->onAppCmd = [&](struct android_app* app, i32 cmd) {
    //    onAppCommand(app, cmd);
    //};

    //let fn = bind_this(this, &AndroidApp::onInputEvent);
    //app->onAppCmd = bind_this(&AndroidApp::onAppCommand, this);
    app->onAppCmd = AndroidApp::onAppCommand;
    app->onInputEvent = AndroidApp::onInputEvent;
   // app->onInputEvent = std::bind(&AndroidApp::onInputEvent, this, std::placeholders::_1);
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