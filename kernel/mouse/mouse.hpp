#pragma once

#include <graphics/graphics.hpp>
#include <util/vector2d.hpp>

class MouseCursor {
   public:
    MouseCursor(PixelWriter* writer, PixelColor erase_color,
                Vector2D<int> initial_position);
    void MoveRelative(Vector2D<int> displacement);

   private:
    PixelWriter* pixel_writer = nullptr;
    PixelColor erase_color;
    Vector2D<int> position;
};

