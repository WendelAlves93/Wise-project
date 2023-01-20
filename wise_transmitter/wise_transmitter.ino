#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>       
#include <RH_ASK.h>                      
#include <RHGenericDriver.h>             
#include <DHT.h>                         
#define DHTPIN A10                       
#define DHTTYPE DHT11                    
DHT dht(DHTPIN, DHTTYPE);                
#define I2C_ADDRESS 0x27                 
LiquidCrystal_PCF8574 lcd(I2C_ADDRESS);  
#define rf_tx_pin 4                      
RH_ASK driver(2000, rf_tx_pin);          
#define tank_sensor_pin 5                
#define sensorCheia 6                    
#define sensorVazia 7                    
#define pump_pin 8                       
#define BUZZER 9                         
#define valve_pin1 10                    
#define valve_pin2 11                    
#define valve_pin3 12                    
#define valve_pin4 13                    
#define soilSensor1 A0                 
#define soilSensor2 A1                  
#define soilSensor3 A2                  
#define soilSensor4 A3                   


int caixa_Cheia_status; 
int caixa_Vazia_status;  
int tank_sensor_status;  
float humidity;
float temperature;
int soilHumidity1;
int soilHumidity2;
int soilHumidity3;
int soilHumidity4;

void setup() {
  pinMode(soilSensor1, INPUT);  
  pinMode(soilSensor2, INPUT);  
  pinMode(soilSensor3, INPUT);  
  pinMode(soilSensor4, INPUT);  
  
  pinMode(sensorCheia, INPUT);      
  pinMode(sensorVazia, INPUT);     
  pinMode(tank_sensor_pin, INPUT);  
 
  pinMode(pump_pin, OUTPUT);  
  pinMode(BUZZER, OUTPUT);
  pinMode(valve_pin1, OUTPUT);
  pinMode(valve_pin2, OUTPUT);
  pinMode(valve_pin3, OUTPUT);
  pinMode(valve_pin4, OUTPUT);
  lcd.begin(40, 4); 
  lcd.clear();       
  dht.begin();       
}

void loop() {
  controlPump();
  controlDHT();
  controlSoil();
  controlValve(1);
  displayValues(caixa_Vazia_status, caixa_Cheia_status, tank_sensor_status, soilHumidity1, digitalRead(pump_pin), digitalRead(valve_pin1));
  sendDataRF(digitalRead(sensorVazia), digitalRead(sensorCheia), digitalRead(tank_sensor_pin), digitalRead(soilSensor1), digitalRead(pump_pin), digitalRead(valve_pin1));
  delay(2000);
}

void controlPump() {
  
  caixa_Vazia_status = digitalRead(sensorVazia);
  caixa_Cheia_status = digitalRead(sensorCheia);
  tank_sensor_status = digitalRead(tank_sensor_pin);

  
  if ((caixa_Vazia_status == LOW && caixa_Cheia_status == LOW && tank_sensor_status == HIGH) || (caixa_Vazia_status == HIGH && caixa_Cheia_status == LOW && tank_sensor_status == HIGH)) {
    digitalWrite(pump_pin, HIGH);
    digitalWrite(BUZZER, LOW);
  }
  
  else if (caixa_Vazia_status == HIGH && caixa_Cheia_status == HIGH) {
    
    digitalWrite(pump_pin, LOW);
    digitalWrite(BUZZER, LOW);
  } else if (tank_sensor_status == LOW) {
    digitalWrite(pump_pin, LOW);
    digitalWrite(BUZZER, LOW);
  } else if (caixa_Vazia_status == LOW && caixa_Cheia_status == HIGH) {
    digitalWrite(pump_pin, LOW);
    digitalWrite(BUZZER, HIGH);
  }
}
void controlDHT() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}
void controlSoil() {
  soilHumidity1 = analogRead(soilSensor1);
  soilHumidity2 = analogRead(soilSensor2);
  soilHumidity3 = analogRead(soilSensor3);
  soilHumidity4 = analogRead(soilSensor4);
}
void controlValve(int soil_sensor) {
  switch (soil_sensor) {
    case 1:  //
      digitalWrite(valve_pin1, HIGH);
      digitalWrite(valve_pin2, LOW);
      digitalWrite(valve_pin3, LOW);
      digitalWrite(valve_pin4, LOW);
      break;
    case 2:  //
      digitalWrite(valve_pin1, LOW);
      digitalWrite(valve_pin2, HIGH);
      digitalWrite(valve_pin3, LOW);
      digitalWrite(valve_pin4, LOW);
      break;

    case 3:  //
      digitalWrite(valve_pin1, LOW);
      digitalWrite(valve_pin2, LOW);
      digitalWrite(valve_pin3, HIGH);
      digitalWrite(valve_pin4, LOW);
      break;

    case 4:  //
      digitalWrite(valve_pin1, LOW);
      digitalWrite(valve_pin2, LOW);
      digitalWrite(valve_pin3, LOW);
      digitalWrite(valve_pin4, HIGH);
      break;

    case 5:  //
      digitalWrite(valve_pin1, LOW);
      digitalWrite(valve_pin2, LOW);
      digitalWrite(valve_pin3, LOW);
      digitalWrite(valve_pin4, LOW);
      break;
  }
}
void displayValues(int sensor1_status, int sensor2_status, int tank_sensor_status, int soil_sensor_status, int pump_status, int valve_status) {
  lcd.begin(20, 4);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Sensor 1: ");
  lcd.print(sensor1_status);

  lcd.setCursor(0, 1);
  lcd.print("Sensor 2: ");
  lcd.print(sensor2_status);

  lcd.setCursor(0, 2);
  lcd.print("Tank Sensor: ");
  lcd.print(tank_sensor_status);

  lcd.setCursor(0, 3);
  lcd.print("Soil Sensor: ");
  lcd.print(soil_sensor_status);
}
void sendDataRF(int sensor1_status, int sensor2_status, int tank_sensor_status, int soil_sensor_status, int pump_status, int valve_status) {
  byte data[6] = { sensor1_status, sensor2_status, tank_sensor_status, soil_sensor_status, pump_status, valve_status };

  driver.send(data, sizeof(data));
  driver.waitPacketSent();  
}
