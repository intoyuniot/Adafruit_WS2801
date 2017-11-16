/*****************************************************************************
该例程展示如何驱动Adafruit WS2801 RGB LED灯.
例如:
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683
硬件连接:
1. MOSI  - 数据引脚
2. SCK    - 时钟引脚
3. 连接电源和地  5V供电
控制采取SPI通讯方式，每个LED灯传送24位数据(R,G,B各8位)
*****************************************************************************/
#include <Adafruit_WS2801.h>

const uint8_t dataPin  = D0;    //  数据引脚
const uint8_t clockPin = D1;    //  时钟引脚

//设置LED 行数和列数
Adafruit_WS2801 strip = Adafruit_WS2801((uint16_t)7, (uint16_t)7, dataPin, clockPin);

// R,G,B组合成一个24位颜色值
uint32_t Color(byte r, byte g, byte b)
{
    uint32_t c;
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}

//滚轮效果
uint32_t Wheel(byte WheelPos)
{
    if (WheelPos < 85)
    {
        return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

void drawX(uint8_t w, uint8_t h, uint8_t wait)
{
    uint16_t x, y;
    for (x=0; x<w; x++)
    {
        strip.setPixelColor(x, x, 255, 0, 0);
        strip.show();
        delay(wait);
    }
    for (y=0; y<h; y++)
    {
        strip.setPixelColor(w-1-y, y, 0, 0, 255);
        strip.show();
        delay(wait);
    }
}

void bounce(uint8_t w, uint8_t h, uint8_t wait)
{
    int16_t x = 1;
    int16_t y = 2;
    int8_t xdir = +1;
    int8_t ydir = -1;
    int j;
    for (j=0; j < 256; j++)
    {
        x = x + xdir;
        y = y + ydir;
        if (x < 0)
        {
            x = -x;
            xdir = - xdir;
        }
        if (y < 0)
        {
            y = -y;
            ydir = - ydir;
        }
        if (x == w)
        {
            x = w-2;
            xdir = - xdir;
        }
        if (y == h)
        {
            y = h-2;
            ydir = - ydir;
        }
        strip.setPixelColor(x, y, Wheel(j));
        strip.show();
        delay(wait);
        strip.setPixelColor(x, y, 0, 0, 0);
    }
}

void setup()
{
    strip.begin();
    //显示
    strip.show();
}

void loop()
{
    drawX(7, 7, 100);
    bounce(7, 6, 50);
}
