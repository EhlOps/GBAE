#include <clock.h>

#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>
#endif

float display_frequency() {
    float refresh_rate = 0.0f;
    #ifdef __APPLE__
    CGDirectDisplayID id = CGMainDisplayID();
    CGDisplayModeRef displayMode = CGDisplayCopyDisplayMode(id);
    if (displayMode) {
        refresh_rate = (float)CGDisplayModeGetRefreshRate(displayMode);
        CFRelease(displayMode);
    }
    #endif
    return refresh_rate;
}