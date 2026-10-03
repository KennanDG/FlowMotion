#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <span>

namespace flowmotion {

enum class PixelFormat {
    unknown,
    gray8,
    bgr8,
    rgb8,
    bgra8,
    rgba8
};

struct FrameView {
    std::span<const std::byte> data {};
    std::size_t width {};
    std::size_t height {};
    std::size_t stride_bytes {};
    PixelFormat pixel_format {PixelFormat::unknown};
    std::chrono::nanoseconds timestamp {};

    [[nodiscard]] bool empty() const noexcept
    {
        return data.empty() || width == 0 || height == 0;
    }
};

} // namespace flowmotion
