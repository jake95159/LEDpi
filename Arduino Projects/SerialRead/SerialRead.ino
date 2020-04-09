#include <FastLED.h>

// Define analog output pins
#define REDPIN   9
#define GREENPIN 10
#define BLUEPIN  6

// Serial comms
String command;

void setup() {

  // Initialize serial comms
  Serial.begin(9600);


  // Setup analog output pins
  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);

}

void loop() {
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '\n')
    {
      parseCommand(command);
      command = "";
    }
    else
    {
      command += c;
    }
  }
}

void parseCommand(String com)
{
  String part1;
  String part2;

  part1 = com.substring(0, com.indexOf(" "));
  part2 = com.substring(com.indexOf(" ") + 1);

  if (part1.equalsIgnoreCase("pinOn"))
  {
    int pin = part2.toInt();
    digitalWrite(pin, HIGH);
  }
  else if (part1.equalsIgnoreCase("pinOff"))
  {
    int pin = part2.toInt();
    digitalWrite(pin, LOW);
  }
  else
  {
    Serial.println("Command not recognized");
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

void analogSolid()
{
  static uint8_t hue;
}


void analogRainbow() 
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
