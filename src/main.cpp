#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "../.pio/libdeps/esp12e/U8g2/src/clib/u8x8.h"
#include "../.pio/libdeps/esp12e/U8g2/src/clib/u8g2.h"
#include "../.pio/libdeps/esp12e/U8g2/src/U8g2lib.h"

#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
unsigned long delayTime;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void u8g2_prepare()
{
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

void drawBme280() {
    float temperatur = bme.readTemperature();
    float luftdruck =  (bme.readPressure() / 100);
    float luftfeuchtigkeit = bme.readHumidity();
    u8g2.drawStr(0,0, "Temperatur: ");
    u8g2.drawStr(70,0, String(temperatur).c_str());
    u8g2.drawStr(102,0,"C");
    u8g2.drawStr(0,15,"Luftdruck: ");
    u8g2.drawStr(62,15, String(luftdruck).c_str());
    u8g2.drawStr(106,15,"hPa");
    u8g2.drawStr(0,30,"Höhe m:");
    u8g2.drawStr(60,30, String(luftfeuchtigkeit).c_str());

}

void setup(void) {
    Serial.begin(9600);
    while (!Serial);
    Serial.println(F("BME280 Test"));
    unsigned status;
    status = bme.begin();
    if (!status)
    {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x");
        Serial.println(bme.sensorID(), 16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(1000);
    }
    Serial.println("-- Default Test --");
    delayTime = 1000;
    Serial.println();
    u8g2.begin();
    u8g2_prepare();
}

void loop(void) {
    u8g2.clearBuffer();
    drawBme280();    
    u8g2.sendBuffer();
}