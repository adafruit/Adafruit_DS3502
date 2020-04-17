/*!
 *  @file Adafruit_DS3502.h
 *
 * 	I2C Driver for DS3502 I2C Potentiometer
 *
 * 	This is a library for the Adafruit DS3502 breakout:
 * 	http://www.adafruit.com/products
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_DS3502_H
#define _ADAFRUIT_DS3502_H

#include "Arduino.h"
#include <Wire.h>

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

#define DS3502_I2CADDR_DEFAULT 0x28 ///< DS3502 default I2C address

#define DS3502_WIPER 0x00 ///< Wiper value register
#define DS3502_MODE 0x02  ///< Mode selection register

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the DS3502 I2C Potentiometer
 */
class Adafruit_DS3502 {
public:
  Adafruit_DS3502();
  bool begin(uint8_t i2c_addr = DS3502_I2CADDR_DEFAULT, TwoWire *wire = &Wire);
  uint8_t getWiper(void);
  void setWiper(uint8_t new_wiper_value);
  void setWiperDefault(uint8_t new_wiper_default);

  Adafruit_BusIO_Register
      *mode_selector; ///< BusIO Register for selecting the write mode

private:
  Adafruit_I2CDevice *i2c_dev;
};

#endif
