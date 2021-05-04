#include "console.hpp"

#include <cstring>

#include "../font/font.hpp"

Console::Console(PixelWriter& writer, const PixelColor& fg_color,
                 const PixelColor& bg_color)
    : writer(writer),
      fg_color(fg_color),
      bg_color(bg_color),
      buffer{},
      cursor_row{0},
      cursor_column{0} {}

void Console::PutString(const char* s) {
    while (*s) {
        if (*s == '\n') {
            NewLine();
        } else if (cursor_column < kColumns - 1) {
            WriteAscii(this->writer, 8 * cursor_column, 16 * cursor_row, *s,
                       fg_color);
            buffer[cursor_row][cursor_column] = *s;
            ++cursor_column;
        }
        ++s;
    }
}

void Console::NewLine() {
    this->cursor_column = 0;
    if (this->cursor_row < this->kRows - 1) {
        ++cursor_row;
    } else {
        for (int y = 0; y < 16 * kRows; ++y) {
            for (int x = 0; x < 8 * this->kColumns; ++x) {
                this->writer.Write(x, y, bg_color);
            }
        }
        for (int row = 0; row < kRows - 1; ++row) {
            memcpy(this->buffer[row], this->buffer[row + 1],
                   this->kColumns + 1);
            WriteString(this->writer, 0, 16 * row, this->buffer[row],
                        this->fg_color);
        }
        memset(this->buffer[kRows - 1], 0, this->kColumns + 1);
    }
}
