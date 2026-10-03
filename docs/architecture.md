# FlowMotion Architecture

## Initial layers

```text
Application / Python API
          |
          v
+------------------------+
|   FlowMotion Pipeline  |
+------------------------+
          |
          v
+------------------------+
|   FrameProcessor API   |
+------------------------+
          |
          +--------------------+
          |                    |
          v                    v
 Optical Flow          Future processors
 Motion Analyzer       Tracking / filters /
                       stabilization / VO

Backend integrations:
- OpenCV capture / image conversion
- CPU optical flow
- Future GPU backends
```

The core API deliberately avoids exposing `cv::Mat` as its foundational frame type.
That keeps OpenCV as an implementation/backend dependency rather than making it
part of every consumer's public API contract.

OpenCV adapters and the first optical-flow module should be added as separate
modules once the base pipeline is stable.
