find_package(PkgConfig QUIET)

if (PKG_CONFIG_FOUND)
    pkg_check_modules(PC_RapidJSON QUIET RapidJSON)
endif (PKG_CONFIG_FOUND)

find_path(RapidJSON_INCLUDE_DIR rapidjson/rapidjson.h HINTS "${PC_RapidJSON_INCLUDEDIR}" "/usr/include" "/usr/local/include" "${PROJECT_SOURCE_DIR}/libraries/rapidjson/include")

if (RapidJSON_INCLUDE_DIR)
    set(RapidJSON_FOUND TRUE)
    message(STATUS "RapidJSON found at: ${RapidJSON_INCLUDE_DIR}")
else()
    set(RapidJSON_FOUND FALSE)
    message(FATAL_ERROR "Missing RapidJSON dependency")
endif()
