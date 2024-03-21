// Generated by imageconverter. Please, do not edit!

#ifndef TOUCHGFX_BITMAPDATABASE_HPP
#define TOUCHGFX_BITMAPDATABASE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>

const uint16_t BITMAP_BACKGROUND_ID = 0;
const uint16_t BITMAP_BUTTON_DOWN_DISABLED_ID = 1;
const uint16_t BITMAP_BUTTON_DOWN_PRESSED_ID = 2;
const uint16_t BITMAP_BUTTON_DOWN_RELEASED_ID = 3;
const uint16_t BITMAP_BUTTON_UP_DISABLED_ID = 4;
const uint16_t BITMAP_BUTTON_UP_PRESSED_ID = 5;
const uint16_t BITMAP_BUTTON_UP_RELEASED_ID = 6;
const uint16_t BITMAP_COUNTER_BOX_ID = 7;

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance();
uint16_t getInstanceSize();
} // namespace BitmapDatabase

#endif // TOUCHGFX_BITMAPDATABASE_HPP
