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

const int kMouseCursorWidth = 15;
const int kMouseCursorHeight = 24;
const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
    "@              ", "@@             ", "@.@            ", "@..@           ",
    "@...@          ", "@....@         ", "@.....@        ", "@......@       ",
    "@.......@      ", "@........@     ", "@.........@    ", "@..........@   ",
    "@...........@  ", "@............@ ", "@......@@@@@@@@", "@......@       ",
    "@....@@.@      ", "@...@ @.@      ", "@..@   @.@     ", "@.@    @.@     ",
    "@@      @.@    ", "@       @.@    ", "         @.@   ", "         @@@   ",
};

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

    const int kFrameWidth = frame_buffer_config.horizontal_resolution;
    const int kFrameHeight = frame_buffer_config.vertical_resolution;
    const PixelColor kDesktopBGColor{45, 118, 237};
    const PixelColor kDesktopFGColor{255, 255, 255};

    FillRectangle(*pixel_writer, {0, 0}, {kFrameWidth, kFrameHeight - 50},
                  kDesktopBGColor);
    FillRectangle(*pixel_writer, {0, kFrameHeight - 50}, {kFrameWidth, 50},
                  {1, 8, 17});
    FillRectangle(*pixel_writer, {0, kFrameHeight - 50}, {kFrameWidth / 5, 50},
                  {80, 80, 80});
    DrawRectangle(*pixel_writer, {10, kFrameHeight - 40}, {30, 30},
                  {160, 160, 160});

    console =
        new (console_buf) Console{*pixel_writer, {255, 255, 255}, {0, 0, 0}};
    printk("Welcome to Mikan OS!\n");

    for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
        for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
            if (mouse_cursor_shape[dy][dx] == '@') {
                pixel_writer->Write(200 + dx, 100 + dy, {0, 0, 0});
            } else if (mouse_cursor_shape[dy][dx] == '.') {
                pixel_writer->Write(200 + dx, 100 + dy, {255, 255, 255});
            }
        }
    }

    while (1) __asm__("hlt");
}
