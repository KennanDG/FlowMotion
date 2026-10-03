cmake_minimum_required(VERSION 3.24)

project(
    FlowMotion
    VERSION 0.1.0
    DESCRIPTION "High-performance real-time video processing and motion analysis."
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)

option(FLOWMOTION_BUILD_EXAMPLES "Build FlowMotion examples" ON)
option(FLOWMOTION_BUILD_TESTS "Build FlowMotion tests" ON)
option(FLOWMOTION_BUILD_PYTHON "Build FlowMotion Python bindings" OFF)
option(FLOWMOTION_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Generated version header
# ---------------------------------------------------------------------------

configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/version.hpp.in"
    "${PROJECT_BINARY_DIR}/generated/flowmotion/version.hpp"
    @ONLY
)

# ---------------------------------------------------------------------------
# Core library
# ---------------------------------------------------------------------------

add_library(flowmotion
    src/pipeline.cpp
)

add_library(FlowMotion::flowmotion ALIAS flowmotion)

target_compile_features(flowmotion PUBLIC cxx_std_20)

target_include_directories(
    flowmotion
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(
    flowmotion
    PROPERTIES
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)

include("${PROJECT_SOURCE_DIR}/cmake/CompilerWarnings.cmake")
flowmotion_set_project_warnings(
    flowmotion
    ${FLOWMOTION_WARNINGS_AS_ERRORS}
)

# ---------------------------------------------------------------------------
# Subprojects
# ---------------------------------------------------------------------------

if(FLOWMOTION_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(FLOWMOTION_BUILD_TESTS AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(FLOWMOTION_BUILD_PYTHON)
    add_subdirectory(bindings/python)
endif()

# ---------------------------------------------------------------------------
# Installation
# ---------------------------------------------------------------------------

install(
    TARGETS flowmotion
    EXPORT FlowMotionTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    FILES "${PROJECT_BINARY_DIR}/generated/flowmotion/version.hpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/flowmotion"
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/FlowMotionConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/FlowMotionConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/FlowMotion"
)

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/FlowMotionConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${PROJECT_BINARY_DIR}/FlowMotionConfig.cmake"
        "${PROJECT_BINARY_DIR}/FlowMotionConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/FlowMotion"
)

install(
    EXPORT FlowMotionTargets
    FILE FlowMotionTargets.cmake
    NAMESPACE FlowMotion::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/FlowMotion"
)
