#pragma once

#include <flowmotion/frame.hpp>

namespace flowmotion {

class FrameProcessor {
public:
    virtual ~FrameProcessor() = default;

    FrameProcessor() = default;
    FrameProcessor(const FrameProcessor&) = default;
    FrameProcessor& operator=(const FrameProcessor&) = default;
    FrameProcessor(FrameProcessor&&) noexcept = default;
    FrameProcessor& operator=(FrameProcessor&&) noexcept = default;

    virtual void process(const FrameView& frame) = 0;
};

} // namespace flowmotion
