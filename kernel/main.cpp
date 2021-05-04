#include <cstddef>
#include <cstdint>

#include "frame_buffer_config.hpp"
#include "graphics/include/font.hpp"
#include "graphics/include/graphics.hpp"

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

void* operator new(size_t size, void* buf) {
    (void)size;
    return buf;
}
void operator delete(void* obj) noexcept { (void)obj; }

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
    switch (frame_buffer_config.pixel_format) {
        case kPixelRGBResv8BitPerColor:
            pixel_writer = new (pixel_writer_buf)
                RGBResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
        case kPixelBGRResv8BitPerColor:
            pixel_writer = new (pixel_writer_buf)
                BGRResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
    }

    for (auto x = 0; x < (int)frame_buffer_config.horizontal_resolution; ++x) {
        for (auto y = 0; y < (int)frame_buffer_config.vertical_resolution;
             ++y) {
            pixel_writer->Write(x, y, {255, 255, 255});
        }
    }
    for (int x = 0; x < 200; ++x) {
        for (int y = 0; y < 200; ++y) {
            pixel_writer->Write(100 + x, 100 + y, {0, 255, 0});
        }
    }
    WriteAscii(*pixel_writer, 50, 50, 'A', {0, 0, 0});
    WriteAscii(*pixel_writer, 58, 50, 'A', {0, 0, 0});

    while (1) __asm__("hlt");
}
