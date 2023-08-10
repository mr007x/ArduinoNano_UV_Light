#include <Wire.h>
#include "Adafruit_VEML6070.h"
#include <BH1750FVI.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_VEML6070 uv = Adafruit_VEML6070();

BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(9600);
  Serial.println("VEML6070 Test");
  uv.begin(VEML6070_1_T);  // pass in the integration time constant

  LightSensor.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.display();
  delay(2000);

  //display.clearDisplay();
}

void loop()
{
  display.clearDisplay();

  Serial.print("UV light level: "); Serial.println(uv.readUV());

  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.println(lux);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.print(F("UV: "));
  display.println(uv.readUV());
  display.display();

  if(uv.readUV()>=0 && uv.readUV()<689 )
  {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.print(F("Low Risk"));
    display.display();
  } else 

   if(uv.readUV()>=690 && uv.readUV()<1379)
  {
      display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.print(F("Moderate Risk"));
    display.display();
  } else 

   if(uv.readUV()>=1380 && uv.readUV()<1839)
  {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.print(F("High Risk"));
    display.display();
  } else


  if(uv.readUV()>=1839 && uv.readUV()<2529)
  {
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 20);
      display.print(F("Very High Risk"));
      display.display();
  }

  if(uv.readUV()>=2530 && uv.readUV()<2760)
  {
    display.setTextSize(2);
    display.setCursor(30,20);
    display.print("Extreme high");
  }

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 50);
  display.print(F("LUX: "));
  display.println(lux);
  display.display();

  delay(2000);
}
