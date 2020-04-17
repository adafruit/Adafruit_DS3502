/*!
 *  @file Adafruit_DS3502.cpp
 *
 *  @mainpage Adafruit DS3502 I2C Potentiometer
 *
 *  @section intro_sec Introduction
 *
 * 	I2C Driver for the Maxim DS3502 I2C Potentiometer
 *
 * 	This is a library for the Adafruit DS3502 breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section dependencies Dependencies
 *
 *  This library depends on the Adafruit BusIO library
 *
 *  @section author Author
 *
 *  Bryan Siepert for Adafruit Industries
 *
 * 	@section license License
 *
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include "Arduino.h"
#include <Wire.h>

#include "Adafruit_DS3502.h"

/*!
 *    @brief  Instantiates a new DS3502 class
 */
Adafruit_DS3502::Adafruit_DS3502(void) {}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  i2c_address
 *            The I2C address to be used.
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
bool Adafruit_DS3502::begin(uint8_t i2c_address, TwoWire *wire) {
  i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  mode_selector = new Adafruit_BusIO_Register(i2c_dev, DS3502_MODE, 1);
  mode_selector->write(0x80);
  return true;
}

/**************************************************************************/
/*!
    @brief Gets the current value of the wiper register.
    @return The 7-bit wiper value.
*/
/**************************************************************************/

uint8_t Adafruit_DS3502::getWiper(void) {
  Adafruit_BusIO_Register wiper =
      Adafruit_BusIO_Register(i2c_dev, DS3502_WIPER, 1);
  return wiper.read();
}
/**************************************************************************/
/*!
    @brief Sets the potentiometer wiper to a new value.
    @param  new_wiper_value
            The new wiper value to set. Must be from 0-127
*/
/**************************************************************************/
void Adafruit_DS3502::setWiper(uint8_t new_wiper_value) {
  if ((new_wiper_value > 127) || (new_wiper_value < 0)) {
    return;
  }
  Adafruit_BusIO_Register wiper =
      Adafruit_BusIO_Register(i2c_dev, DS3502_WIPER, 1);
  wiper.write(new_wiper_value);
}

/**************************************************************************/
/*!
    @brief Sets the Wiper and IVR (Initial Value Register) to the given value.
    @param  new_wiper_default
            The new wiper default to be set the wiper and default wiper value
   to. The wiper register will be set to the given value when written and when
   the device is powered on. Must be from 0-127
*/
/**************************************************************************/
void Adafruit_DS3502::setWiperDefault(uint8_t new_wiper_default) {
  if ((new_wiper_default > 127) || (new_wiper_default < 0)) {
    return;
  }

  Adafruit_BusIO_Register wiper =
      Adafruit_BusIO_Register(i2c_dev, DS3502_WIPER, 1);

  mode_selector->write(0x00);     // set mode to write default on wiper write
  wiper.write(new_wiper_default); // write the new wiper value which carries
                                  // over to the IVR
  delay(100); // delay to allow EEPROM write to IVR to finish
  mode_selector->write(0x80);
}
