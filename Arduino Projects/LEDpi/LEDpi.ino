#include <FastLED.h>

// Define analog output pins
#define REDPIN   9
#define GREENPIN 10
#define BLUEPIN  6

// Variable to read incoming serial data into
int incomingByte;

void setup() {

  // Initialize serial communication
  Serial.begin(9600);

  // Setup analog output pins
  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);

}

void loop() {

  // See if there's incoming serial data
  if (Serial.available() > 0) {
    // Read the oldest byte in the serial buffer
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), start analogRainbowLoop:
    if (incomingByte == 'H') {
      analogRainbowLoop();
    }
    // if it's an L (ASCII 76) turn off LEDs:
    if (incomingByte == 'L') {
      analogOff();
    }
  }

}

// --------------- Utilities --------------------------------

// showAnalogRGB: this is like FastLED.show(), but outputs on 
// analog PWM output pins instead of sending data to an intelligent,
// pixel-addressable LED strip.
// 
// This function takes the incoming RGB values and outputs the values
// on three analog PWM output pins to the r, g, and b values respectively.
void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g );
  analogWrite(BLUEPIN,  rgb.b );
}

// ^^^^^^^^^^^^^^ Utilities ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// --------------- Analog Functions ----------------------------

void analogRainbowLoop() 
{
  static uint8_t hue;
  hue = hue + 1;
  // Use FastLED automatic HSV->RGB conversion
  showAnalogRGB( CHSV( hue, 255, 255) );
  
  delay(20);
}

void analogOff()
{
  analogWrite(REDPIN,   0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN,  0);
}

// ^^^^^^^^^^^^^^^^^ Analog Functions ^^^^^^^^^^^^^^^^^^^^^^^^^^^
