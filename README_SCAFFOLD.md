# FlowMotion scaffold

This directory contains the initial native project scaffold.

## Configure

### Development build

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

### Release build

```bash
cmake --preset release
cmake --build --preset release
ctest --preset release
```

If Ninja is not installed, configure without presets:

```bash
cmake -S . -B build -DFLOWMOTION_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Python bindings

Python bindings are intentionally optional at this stage:

```bash
cmake --preset python
cmake --build --preset python
```

If `pybind11` is installed through your package manager or Python environment,
CMake will use it. Otherwise the Python build configuration can fetch pybind11.

## Next module

The recommended next implementation milestone is:

```text
modules/opencv/
    frame_adapter.*
    video_source.*

modules/motion/
    optical_flow_analyzer.*
```

Keep OpenCV-specific types at the backend boundary rather than embedding
`cv::Mat` throughout the public core API.
