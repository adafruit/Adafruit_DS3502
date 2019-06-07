#include <Adafruit_DS3502.h>

Adafruit_DS3502 ds3502 = Adafruit_DS3502();
/* For this example, make the following connections:
    * DS3502 RH to 5V
    * DS3502 RL to GND
    * DS3502 RW to the pin specified by WIPER_VALUE_PIN
*/

#define WIPER_VALUE_PIN A0

void setup() {
  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }

  Serial.println("Adafruit DS3502 Test");

  if (!ds3502.begin()) {
    Serial.println("Couldn't find DS3502 chip");
    while (1);
  }
  Serial.println("Found DS3502 chip");
  /*
  Steps to test `setWiperDefault`:

  1. Run the program once to see what the current default value is
  2. Uncomment the call to `setWiperDefault` below and run it again.
  3. Once the program has run with the `setWiperDefault` call,
      comment out the line below again, then powercycle the DS3502 
      by removing then reattaching VCC
  4. Then run the program again with the line commented out to see the 
      new default wiper value
  */


  // ds3502.setWiperDefault(64);
}

void loop() {
  uint8_t default_value = ds3502.getWiper();

  Serial.print("Default wiper value: ");
  Serial.println(default_value);

  Serial.print("Wiper voltage with wiper set to default: ");
  float wiper_value = analogRead(WIPER_VALUE_PIN);
  wiper_value *= 5.0;
  wiper_value /= 1024;
  Serial.print(wiper_value);
  Serial.println(" V");

  Serial.println();
  delay(1000);

}