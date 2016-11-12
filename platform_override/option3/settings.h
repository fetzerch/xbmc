#pragma once

// Generic
#define SETTING_X "generic_setting"
#define SETTING_Y "unoverriden setting"

// Android
#if (PLATFORM == android)
  #undef  SETTING_X
  #define SETTING_X "android_setting"
#endif
