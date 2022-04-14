#pragma once

#include "../../../../../../../AppData/Local/Android/Sdk/ndk/21.4.7075529/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/log.h"

#define TAG "Roguelike/AURI"

#define Info(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define Debug(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define Warn(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define Error(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)