find_package(Python 3.10 REQUIRED COMPONENTS Interpreter Development.Module)

find_package(pybind11 CONFIG QUIET)

if(NOT pybind11_FOUND)
    include(FetchContent)

    message(STATUS "pybind11 not found locally; fetching pybind11")

    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v3.0.1
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(pybind11)
endif()

pybind11_add_module(_flowmotion
    module.cpp
)

target_link_libraries(
    _flowmotion
    PRIVATE
        FlowMotion::flowmotion
)

target_compile_features(_flowmotion PRIVATE cxx_std_20)
