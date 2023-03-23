#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/* Define the names for ESP32 pin for HC-SR04*/
#define trigger_pin 10
#define Echo_pin 9

#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

/* two variables to store duraion and distance value */
long duration;
int distance;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
/* configure D9 and D11 as digital input and output respectively */
void setup() {
pinMode(trigger_pin, OUTPUT); // configure the trigger_pin(D9) as an Output
pinMode(Echo_pin, INPUT); // configure the Echo_pin(D11) as an Input
Serial.begin(9600); // Enable the serial with 9600 baud rate
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
  delay(500);
display.clearDisplay();
display.setTextColor(WHITE);
}

void loop() {

delay(500);
display.setCursor(0,0);
display.setTextSize(1);
display.clearDisplay();  

digitalWrite(trigger_pin, LOW); //set trigger signal low for 2us
delayMicroseconds(2);

/*send 10 microsecond pulse to trigger pin of HC-SR04 */
digitalWrite(trigger_pin, HIGH);  // make trigger pin active high
delayMicroseconds(10);            // wait for 10 microseconds
digitalWrite(trigger_pin, LOW);   // make trigger pin active low

/*Measure the Echo output signal duration or pulss width */
duration = pulseIn(Echo_pin, HIGH); // save time duration value in "duration variable
distance = duration * 0.034/2;
Serial.print("Distance: ");
Serial.println(distance);


  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Distance: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(distance);
  display.setTextSize(2);
  display.print("cm");

  Serial.println();
  display.display();
  delay(200);
}