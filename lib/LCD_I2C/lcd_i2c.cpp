#include "lcd_i2c.h"

lcd_i2c::lcd_i2c(uint8_t address, uint8_t cols, uint8_t rows) : _lcd(address, cols, rows) {}

void lcd_i2c::begin()
{
    _lcd.begin(16, 2);
    _lcd.backlight();
    setFirstln("LCD Initialized");
    delay(1000);
    setSecondln("Ready to go...");
    delay(500);
    clear();
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