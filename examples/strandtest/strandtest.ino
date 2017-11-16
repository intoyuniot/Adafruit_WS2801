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

// 设置像素点的个数 一行25个
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);

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

//彩虹效果
void rainbow(uint8_t wait)
{
    int i, j;

    for (j=0; j < 256; j++)
    {     // 256种颜色轮流变换
        for (i=0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel( (i + j) % 255));
        }
        strip.show();   // write all the pixels out
        delay(wait);
    }
}

//彩虹效果
void rainbowCycle(uint8_t wait)
{
    int i, j;

    for (j=0; j < 256 * 5; j++)
    {
        for (i=0; i < strip.numPixels(); i++)
        {
            // tricky math! we use each pixel as a fraction of the full 96-color wheel
            // (thats the i / strip.numPixels() part)
            // Then add in j which makes the colors go around per pixel
            // the % 96 is to make the wheel cycle around
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) % 256) );
        }
        strip.show();
        delay(wait);
    }
}

//效果
void colorWipe(uint32_t c, uint8_t wait)
{
    int i;

    for (i=0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}

void setup()
{
    strip.begin();
    // 显示
    strip.show();
}

void loop()
{
    colorWipe(Color(255, 0, 0), 50);
    colorWipe(Color(0, 255, 0), 50);
    colorWipe(Color(0, 0, 255), 50);
    rainbow(20);
    rainbowCycle(20);
}
