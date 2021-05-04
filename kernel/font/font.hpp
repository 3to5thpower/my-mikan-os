#pragma once

#include <cstdint>

#include "../graphics/graphics.hpp"

void WriteAscii(PixelWriter& writer, int x, int y, char c,
                const PixelColor& color);