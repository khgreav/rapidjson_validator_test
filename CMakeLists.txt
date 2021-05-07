cmake_minimum_required(VERSION 3.0)

project(testschemas)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DRAPIDJSON_HAS_STDSTRING")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE STRING "Modules for CMake" FORCE)

add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost REQUIRED COMPONENTS filesystem log log_setup program_options)
find_package(RapidJSON REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${RapidJSON_INCLUDE_DIR})

add_subdirectory(src)
