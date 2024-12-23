// 4.22.1 0x11fa8c98
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_background[]; // BITMAP_BACKGROUND_ID = 0, Size: 480x272 pixels
extern const unsigned char image_button_down_disabled[]; // BITMAP_BUTTON_DOWN_DISABLED_ID = 1, Size: 130x56 pixels
extern const unsigned char image_button_down_pressed[]; // BITMAP_BUTTON_DOWN_PRESSED_ID = 2, Size: 130x56 pixels
extern const unsigned char image_button_down_released[]; // BITMAP_BUTTON_DOWN_RELEASED_ID = 3, Size: 130x56 pixels
extern const unsigned char image_button_up_disabled[]; // BITMAP_BUTTON_UP_DISABLED_ID = 4, Size: 130x56 pixels
extern const unsigned char image_button_up_pressed[]; // BITMAP_BUTTON_UP_PRESSED_ID = 5, Size: 130x56 pixels
extern const unsigned char image_button_up_released[]; // BITMAP_BUTTON_UP_RELEASED_ID = 6, Size: 130x56 pixels
extern const unsigned char image_counter_box[]; // BITMAP_COUNTER_BOX_ID = 7, Size: 152x154 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_background, 0, 480, 272, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 272, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_button_down_disabled, 0, 130, 56, 3, 0, 124, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 55, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_button_down_pressed, 0, 130, 56, 3, 0, 124, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 55, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_button_down_released, 0, 130, 56, 3, 0, 124, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 55, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_button_up_disabled, 0, 130, 56, 3, 0, 124, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 55, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_button_up_pressed, 0, 130, 56, 3, 0, 124, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 55, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_button_up_released, 0, 130, 56, 3, 0, 124, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 55, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_counter_box, 0, 152, 154, 0, 0, 152, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 154, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
