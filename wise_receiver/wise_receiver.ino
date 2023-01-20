#include <RH_ASK.h>
#include <RHGenericDriver.h>


const int rf_rx_pin = 8;   
RH_ASK driver(2000, rf_rx_pin);

void setup() {
  driver.init();
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    int sensor1_status = buf[0];
    int sensor2_status = buf[1];
    int tank_sensor_status = buf[2];
    int soil_sensor_status = buf[3];
    int pump_status = buf[4];
    int valve_status = buf[5];
  }
}
