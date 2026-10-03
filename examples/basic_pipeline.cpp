#include <flowmotion/flowmotion.hpp>

#include <cstddef>
#include <iostream>
#include <memory>

namespace {

class FrameCounter final : public flowmotion::FrameProcessor {
public:
    void process(const flowmotion::FrameView&) override
    {
        ++frames_processed_;
    }

    [[nodiscard]] std::size_t frames_processed() const noexcept
    {
        return frames_processed_;
    }

private:
    std::size_t frames_processed_ {};
};

} // namespace

int main()
{
    flowmotion::Pipeline pipeline;
    auto counter = std::make_shared<FrameCounter>();

    pipeline.add_processor(counter);

    const flowmotion::FrameView frame {};
    pipeline.process(frame);

    std::cout << "FlowMotion " << FLOWMOTION_VERSION_STRING << '\n';
    std::cout << "Processors: " << pipeline.processor_count() << '\n';
    std::cout << "Frames observed: " << counter->frames_processed() << '\n';

    return 0;
}
