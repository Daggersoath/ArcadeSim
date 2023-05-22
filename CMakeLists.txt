cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -pthread -static-libgcc -static-libstdc++")
project(ArcadeSim CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_PLATFORM_ARCHITECTURE)
    set(CMAKE_PLATFORM_ARCHITECTURE "x64")
endif()
message("${CMAKE_PLATFORM_ARCHITECTURE} architecture in use")

if(NOT ("${CMAKE_PLATFORM_ARCHITECTURE}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_PLATFORM_ARCHITECTURE} arch is not supported!")
endif()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


find_package(Threads)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PLATFORM_ARCHITECTURE}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PLATFORM_ARCHITECTURE}/${CMAKE_BUILD_TYPE})

################################################################################
# Sub-projects
################################################################################
add_subdirectory(SFML)
add_subdirectory(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PLATFORM_ARCHITECTURE}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PLATFORM_ARCHITECTURE}/${CMAKE_BUILD_TYPE})

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG}/rt )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG}/bin )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )