#include "mouse.hpp"

namespace {

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

void DrawMouseCursor(PixelWriter* writer, Vector2D<int> pos) {
    for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
        for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
            if (mouse_cursor_shape[dy][dx] == '@') {
                writer->Write(pos.x + dx, pos.y + dy, {0, 0, 0});
            } else if (mouse_cursor_shape[dy][dx] == '.') {
                writer->Write(pos.x + dx, pos.y + dy, {255, 255, 255});
            }
        }
    }
}

void EraseMouseCursor(PixelWriter* writer, Vector2D<int> pos,
                      PixelColor erase_color) {
    for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
        for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
            if (mouse_cursor_shape[dy][dx] != ' ') {
                writer->Write(pos.x + dx, pos.y + dy, erase_color);
            }
        }
    }
}
}  // namespace

MouseCursor::MouseCursor(PixelWriter* writer, PixelColor erase_color,
                         Vector2D<int> initial_position)
    : pixel_writer(writer),
      erase_color(erase_color),
      position(initial_position) {
    DrawMouseCursor(pixel_writer, position);
}

void MouseCursor::MoveRelative(Vector2D<int> displacement) {
    EraseMouseCursor(pixel_writer, position, erase_color);
    position += displacement;
    DrawMouseCursor(pixel_writer, position);
}