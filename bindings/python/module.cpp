#include <flowmotion/version.hpp>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_flowmotion, module)
{
    module.doc() = "Python bindings for FlowMotion";
    module.attr("__version__") = FLOWMOTION_VERSION_STRING;

    module.def(
        "version",
        []() {
            return FLOWMOTION_VERSION_STRING;
        },
        "Return the FlowMotion version."
    );
}
