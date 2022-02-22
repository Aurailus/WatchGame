#include <iostream>

#include "AndroidApp.h"

void android_main(struct android_app* app) {
    AndroidApp::initialize(app);
    AndroidApp::instance()->mainLoop();
}