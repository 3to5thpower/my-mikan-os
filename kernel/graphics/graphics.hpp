#pragma once

#include <frame_buffer_config.hpp>
#include <util/vector2d.hpp>

struct PixelColor {
    uint8_t r, g, b;
};

class PixelWriter {
   public:
    PixelWriter(const FrameBufferConfig& config) : config{config} {}
    virtual ~PixelWriter() = default;
    virtual void Write(int x, int y, const PixelColor& c);

   protected:
    uint8_t* PixelAt(int x, int y) {
        return config.frame_buffer + 4 * (config.pixels_per_scan_line * y + x);
    }

   private:
    const FrameBufferConfig& config{};
};

class RGBResv8BitPerColorPixelWriter : public PixelWriter {
   public:
    using PixelWriter::PixelWriter;
    virtual void Write(int x, int y, const PixelColor& c) override;
};
class BGRResv8BitPerColorPixelWriter : public PixelWriter {
   public:
    using PixelWriter::PixelWriter;
    virtual void Write(int x, int y, const PixelColor& c) override;
};

void FillRectangle(PixelWriter&, const Vector2D<int>& pos,
                   const Vector2D<int>& size, const PixelColor&);

void DrawRectangle(PixelWriter&, const Vector2D<int>& pos,
                   const Vector2D<int>& size, const PixelColor&);
