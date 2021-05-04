#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "console/console.hpp"
#include "font/font.hpp"
#include "frame_buffer_config.hpp"
#include "graphics/graphics.hpp"

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;
char console_buf[sizeof(Console)];
Console* console;

void* operator new(size_t size, void* buf) {
    (void)size;
    return buf;
}
void operator delete(void* obj) noexcept { (void)obj; }

int printk(const char* fmt, ...) {
    va_list ap;
    int result;
    char s[1024];

    va_start(ap, fmt);
    result = vsprintf(s, fmt, ap);
    va_end(ap);

    console->PutString(s);
    return result;
}

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
    console =
        new (console_buf) Console{*pixel_writer, {255, 255, 255}, {0, 0, 0}};

    for (int i = 0; i < 27; ++i) {
        printk("Line %d:\n", i);
    }

    while (1) __asm__("hlt");
}
