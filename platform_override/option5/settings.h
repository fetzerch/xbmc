#pragma once

#define SETTING_X "generic_setting"
#define SETTING_Y "unoverriden setting"

// Starting with GCC 5, we could use __has_include.
// But as the override header is generated, we just make sure it exists via the build system.
#include "settings_override.h"
