#include "lcd_i2c.h"

lcd_i2c::lcd_i2c(uint8_t address, uint8_t cols, uint8_t rows, uint8_t SDA, uint8_t SCL) : _lcd(address, cols, rows), _SDA(SDA), _SCL(SCL) {}

void lcd_i2c::begin()
{
    _lcd.begin(16, 2);
    _lcd.backlight();
    Wire.begin(_SDA, _SCL);
}

void lcd_i2c::setFirstln(const char *text)
{
    _lcd.setCursor(0, 0);
    _lcd.print(text);
}

void lcd_i2c::setSecondln(const char *text)
{
    _lcd.setCursor(0, 1);
    _lcd.print(text);
}

void lcd_i2c::clear()
{
    _lcd.clear();
}