# Real-Time Video Processing API Roadmap

## Project Goal

Build an open-source **real-time video processing library** with:

- A **C++20 core**
- First-class **C++ and Python APIs**
- Python bindings through **pybind11**
- A modular processing pipeline
- A built-in **Optical Flow Motion Analyzer**
- Performance benchmarks and example applications

**Recommended architecture:** keep all performance-critical processing in C++ and expose a thin, user-friendly Python wrapper.

---

## Target Architecture

```text
C++ API ───────────────┐
                       │
Python API → pybind11 ─┼→ C++ Core
                       │
                       ├→ Video Sources
                       ├→ Pipeline / Frame Processors
                       ├→ Threading / Queues
                       └→ Optical Flow Motion Analyzer
```

Python should be a consumer of the C++ engine, not part of the internal processing pipeline.

---

## 10–12 Week Roadmap

### Weeks 1–2 — Core Foundation

- Set up CMake, C++20, OpenCV, tests, and CI
- Create core abstractions:
  - `Frame`
  - `VideoSource`
  - `FrameProcessor`
  - `Pipeline`
- Support MP4/video-file input
- Implement simple processors such as grayscale and resize

**Milestone:** video → pipeline → processor → display

### Weeks 3–4 — Real-Time Pipeline

- Add worker threads and bounded frame queues
- Implement configurable overflow behavior:
  - Block
  - Drop newest
  - Drop oldest
- Add runtime statistics:
  - Input FPS
  - Processing FPS
  - Average latency
  - Dropped frames
  - Total processed frames

**Milestone:** stable multi-threaded real-time video processing

### Weeks 5–6 — Optical Flow Motion Analyzer

- Implement dense optical flow using OpenCV
- Calculate:
  - Motion magnitude
  - Motion direction
  - Mean/max motion
  - Dominant direction
- Detect significant motion regions
- Add visualization overlays

Example result:

```cpp
struct MotionResult {
    cv::Mat flow;
    float mean_magnitude;
    float max_magnitude;
    cv::Point2f dominant_direction;
    std::vector<MotionRegion> regions;
};
```

**Milestone:** useful motion-analysis API, not just optical-flow visualization

### Weeks 7–8 — Python API

- Add `pybind11` bindings
- Expose major C++ types and functions
- Support NumPy frame input/output where practical
- Create a clean Python package
- Keep native extension details hidden from users

Example:

```python
import flowstream as fs

analyzer = fs.OpticalFlowAnalyzer()

for frame in fs.VideoStream("traffic.mp4"):
    motion = analyzer.analyze(frame)
    print(motion.mean_magnitude)
```

**Milestone:** same C++ engine usable naturally from Python

### Weeks 9–10 — Performance & Testing

Benchmark:

- Decode only
- Decode + preprocessing
- Decode + optical flow
- Single-threaded vs multi-threaded
- C++ API vs Python API
- 720p vs 1080p

Track:

- FPS
- Mean latency
- Dropped frames
- CPU usage

Also add:

- Unit tests
- Integration tests
- Webcam demo
- Video-file demo
- Motion-analysis example

**Milestone:** documented evidence of performance

### Weeks 11–12 — Release v0.1

- Improve README
- Add architecture documentation
- Add API examples for C++ and Python
- Add demo GIF/video
- Package Python release
- Create GitHub release
- Fix remaining stability issues

**Milestone:** polished, installable, portfolio-ready `v0.1`

---

## Recommended v0.1 Scope

Include:

- Video-file input
- Webcam input
- Modular frame-processing pipeline
- Multi-threaded queues
- Pipeline statistics
- Optical flow
- Motion magnitude/direction analysis
- Motion-region detection
- C++ API
- Python bindings
- Tests
- Benchmarks
- Example applications

Postpone:

- CUDA/GPU acceleration
- RTSP/network streaming
- Object detection
- Multi-object tracking
- ROS integration
- Plugin systems
- Distributed processing

---

## Suggested Project Structure

```text
project/
├── CMakeLists.txt
├── include/
│   └── flowstream/
├── src/
├── bindings/
│   └── python/
├── python/
│   └── flowstream/
├── tests/
├── benchmarks/
├── examples/
└── docs/
```

---

## Core Design Principle

Build the framework around reusable processors:

```text
FrameProcessor
├── Resize
├── Grayscale
├── GaussianBlur
├── OpticalFlow
└── MotionAnalyzer
```

Future modules can then add:

- Object detection
- Multi-object tracking
- Video stabilization
- Segmentation
- GPU acceleration

---

## Final Recommendation

Use:

- **C++20** for the engine
- **OpenCV** for video/CV primitives
- **CMake** for builds
- **pybind11** for Python bindings
- **scikit-build-core** for Python packaging

Position the project as:

> A high-performance real-time video processing library written in C++, with first-class C++ and Python APIs and built-in optical-flow motion analysis.

The goal for `v0.1` should be **video pipeline + threading + optical flow + motion analysis + Python bindings + benchmarks**.
