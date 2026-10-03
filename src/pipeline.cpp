#include <flowmotion/pipeline.hpp>

#include <stdexcept>
#include <utility>

namespace flowmotion {

void Pipeline::add_processor(std::shared_ptr<FrameProcessor> processor)
{
    if (!processor) {
        throw std::invalid_argument("processor must not be null");
    }

    processors_.push_back(std::move(processor));
}

void Pipeline::process(const FrameView& frame)
{
    for (const auto& processor : processors_) {
        processor->process(frame);
    }
}

std::size_t Pipeline::processor_count() const noexcept
{
    return processors_.size();
}

} // namespace flowmotion
