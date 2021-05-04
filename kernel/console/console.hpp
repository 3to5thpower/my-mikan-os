#pragma once

#include "../graphics/graphics.hpp"

class Console {
   public:
    static const int kRows = 25;
    static const int kColumns = 80;

    Console(PixelWriter& writer, const PixelColor& fg_color,
            const PixelColor& bg_color);
    void PutString(const char* s);

   private:
    void NewLine();
    PixelWriter& writer;
    const PixelColor& fg_color;
    const PixelColor& bg_color;
    char buffer[kRows][kColumns + 1];
    int cursor_row;
    int cursor_column;
};
