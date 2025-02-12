#ifndef LCD_I2C_H
#define LCD_I2C_H
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class lcd_i2c
{
public:
    lcd_i2c(uint8_t address, uint8_t cols, uint8_t rows, uint8_t SDA, uint8_t SCL);
    void begin();
    void setFirstln(const char *text);
    void setSecondln(const char *text);
    void clear();

private:
    LiquidCrystal_I2C _lcd;
    uint8_t _SDA, _SCL;
};

#endif