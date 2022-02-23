#include <iostream>

#include "AndroidApp.h"

void android_main(struct android_app* app) {
    app_dummy(); // This is actually required, ignore the deprecation warning.
    AndroidApp(app).loop();
}