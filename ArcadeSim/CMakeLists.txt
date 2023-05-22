project(ArcadeSim CXX)

include_directories("../SFML/include" "../spdlog/include")

include_directories(".")

################################################################################
# Source groups
################################################################################

set(PONG_FILES
        Pong/Pong.cpp)

set(ALL_FILES
        "main.cpp"
        Globals.cpp
        ${PONG_FILES})

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

#set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE ArcadeSim)

################################################################################
# Compile definitions
################################################################################
add_definitions(-D_DEBUG)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        "_CONSOLE;"
        "SFML_STATIC;"
        "NOMINMAX;"
        "UNICODE;"
        "_UNICODE"
        )

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_PLATFORM_ARCHITECTURE}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Debug>: ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY} >
                $<$<CONFIG:Release>: /Oi; ${DEFAULT_CXX_RUNTIME_LIBRARY}; /Gy >
                /permissive-;
                /sdl;
                /W4;
                /WX;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                /wd26812;
                ${DEFAULT_CXX_EXCEPTION_HANDLING}
                )
        target_link_options(${PROJECT_NAME} PRIVATE
                $<$<CONFIG:Debug>: /INCREMENTAL >
                $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
                >
                /DEBUG;
                /SUBSYSTEM:CONSOLE
                )
    endif()
else()
    IF (!WIN32)
        message("Adding X11 to link options")
        target_link_options(${PROJECT_NAME} PRIVATE -lX11)
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME} "sfml-system" "sfml-window" "sfml-graphics")

set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "sfml-system"
        "sfml-window"
        "sfml-graphics"
        )

message("Additional dependencies: ${ADDITIONAL_LIBRARY_DEPENDENCIES}")

IF (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
ELSE()
    target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}" X11)
ENDIF()