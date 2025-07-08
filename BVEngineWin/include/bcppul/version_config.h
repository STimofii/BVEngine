// include/bcppul/version_config.h.in
#pragma once

#define BCPPUL_VERSION_MAJOR 0
#define BCPPUL_VERSION_MINOR 1
#define BCPPUL_VERSION_PATCH 8

#define BCPPUL_VERSION_STRING "0.1.8"

#define BCPPUL_VERSION_CHECK(major, minor, patch) \
    (BCPPUL_VERSION_MAJOR > (major) || \
     (BCPPUL_VERSION_MAJOR == (major) && BCPPUL_VERSION_MINOR > (minor)) || \
     (BCPPUL_VERSION_MAJOR == (major) && BCPPUL_VERSION_MINOR == (minor) && BCPPUL_VERSION_PATCH >= (patch)))
