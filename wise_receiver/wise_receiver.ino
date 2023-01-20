#include <RH_ASK.h>
#include <RHGenericDriver.h>

// Pin definitions
const int rf_rx_pin = 8;    // Pin for RF receiver

RH_ASK driver(2000, rf_rx_pin);

void setup() {
  driver.init();
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    // Get the sensor 1 status
    int sensor1_status = buf[0];
    // Get the sensor 2 status
    int sensor2_status = buf[1];
    // Get the tank sensor status
    int tank_sensor_status = buf[2];
    // Get the soil sensor status
    int soil_sensor_status = buf[3];
    // Get the pump status
    int pump_status = buf[4];
    // Get the valve status
    int valve_status = buf[5];
    // use the received data here
  }
}