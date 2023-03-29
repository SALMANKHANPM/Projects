// OLED Display Modules
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables for Relay
#define relayPin = 6;

// Variables for Soil Moisture Sensor
#define sensor1Pin A2
#define sensor2Pin A3
int sensor1Analog = 0;
int sensor2Analog = 0;
int moistureData1 = 0;
int moistureData2 = 0;
int avgMoisture = 0;


void setup(){
    // PinModes
    pinMode(A2, INPUT); // Moisture Sesnor 1
    pinMode(A3, INPUT); // Moistue Sensor 2
    pinMode(6, OUTPUT); // Realy 

    // OLED Initialization
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    delay(500);
    display.clearDisplay();
    display.setTextColor(WHITE);

    // Serial Connections for Debug
    Serial.begin(9600);

}

void loop(){
    // OLED Display Properties
    delay(500);
    display.setCursor(0,0);
    display.setTextSize(2);
    display.clearDisplay();
    Serial.println("OLED DISPLAY..");

    // Soil Moisture Properties
    sensor1Analog = analogRead(sensor1Pin);
    sensor2Analog = analogRead(sensor2Pin);

    moistureData1 = ( 100 - ( (sensor1Analog / 4095.00) * 100 ) );
    moistureData2 = ( 100 - ( (sensor2Analog / 4095.00) * 100 ) );

    avgMoisture = (moistureData1 + moistureData2) / 2;

    // Dispaying Soil Moisture Level
    // Display Crop
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,5);
    display.println("Crop : ");
    display.setTextSize(3);
    display.setCursor(1,30);
    display.println("CHILLI");
    display.display();
    delay(2000);

    //  Display Moisture Level
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Moisture");
    display.setCursor(0, 18);
    display.println("Level :"); 
    display.setTextSize(3);
    display.setCursor(0, 38);
    display.print(avgMoisture);
    display.print("%");
    display.display();
    delay(3000);

    // Serial Debug
    Serial.print("Sensor Data 1 : ");
    Serial.println(moistureData1);
    Serial.print("Sensor Data 2 : ");
    Serial.println(moistureData2);
    Serial.print("Moisture Level : ");
    Serial.println(avgMoisture);
    Serial.print("%");

    // Checking Whether to Pump Or Not/    
    if(avgMoisture < 80){
      digitalWrite(6, LOW);
      Serial.println("Pump ON");
      delay(5000);   
    }
    else {
      digitalWrite(6, HIGH);
      Serial.println("Pump OFF");
    }
}



