#include <flowmotion/flowmotion.hpp>

#include <cassert>
#include <memory>
#include <stdexcept>

namespace {

class CountingProcessor final : public flowmotion::FrameProcessor {
public:
    void process(const flowmotion::FrameView&) override
    {
        ++count_;
    }

    [[nodiscard]] int count() const noexcept
    {
        return count_;
    }

private:
    int count_ {};
};

} // namespace

int main()
{
    flowmotion::Pipeline pipeline;

    assert(pipeline.processor_count() == 0);

    auto processor = std::make_shared<CountingProcessor>();
    pipeline.add_processor(processor);

    assert(pipeline.processor_count() == 1);

    const flowmotion::FrameView frame {};
    pipeline.process(frame);

    assert(processor->count() == 1);

    bool threw = false;
    try {
        pipeline.add_processor(nullptr);
    } catch (const std::invalid_argument&) {
        threw = true;
    }

    assert(threw);

    return 0;
}
