#pragma once

#include <flowmotion/frame.hpp>
#include <flowmotion/frame_processor.hpp>

#include <cstddef>
#include <memory>
#include <vector>

namespace flowmotion {

class Pipeline {
public:
    void add_processor(std::shared_ptr<FrameProcessor> processor);
    void process(const FrameView& frame);

    [[nodiscard]] std::size_t processor_count() const noexcept;

private:
    std::vector<std::shared_ptr<FrameProcessor>> processors_;
};

} // namespace flowmotion
