#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>       // Library LiquidCrystal
#include <RH_ASK.h>                      // Library RadioHead
#include <RHGenericDriver.h>             // Library for RF433 communication
#include <DHT.h>                         // Library DHT
#define DHTPIN A10                       // Pin for DHT11
#define DHTTYPE DHT11                    // Define the type of DHT sensor used
DHT dht(DHTPIN, DHTTYPE);                // Create an instance of the DHT
#define I2C_ADDRESS 0x27                 // I2C address of the PCF8574
LiquidCrystal_PCF8574 lcd(I2C_ADDRESS);  // Create an instance of the LCD
#define rf_tx_pin 4                      // Pin for RF transmitter
RH_ASK driver(2000, rf_tx_pin);          // baud rate of 2000 bps
#define tank_sensor_pin 5                // chave boia 100% - pino D5
#define sensorCheia 6                    // chave boia 100% - pino D7
#define sensorVazia 7                    // chave boia 75%  - pino D6
#define pump_pin 8                       // Pin for the pump
#define BUZZER 9                         // Pin for BUZZER
#define valve_pin1 10                    // Pin for the valve solenoid 1
#define valve_pin2 11                    // Pin for the valve solenoid 2
#define valve_pin3 12                    // Pin for the valve solenoid 3
#define valve_pin4 13                    // Pin for the valve solenoid 4
#define soilSensor1 A0                   // Pin for the soil moisture sensor 1
#define soilSensor2 A1                   // Pin for the soil moisture sensor 2
#define soilSensor3 A2                   // Pin for the soil moisture sensor 3
#define soilSensor4 A3                   // Pin for the soil moisture sensor 4

//DECLARANDO VARIÁVEIS
int caixa_Cheia_status;  // Read the tank sensor
int caixa_Vazia_status;  // Read the tank sensor
int tank_sensor_status;  // Read the tank sensor
//DECLARANDO VARIÁVEIS DO DHT11
float humidity;
float temperature;
//DECLARANDO VARIÁVEIS DO SENSOR UMIDADE DO SOLO
int soilHumidity1;
int soilHumidity2;
int soilHumidity3;
int soilHumidity4;

void setup() {
  // Set the pin for the soil sensor as input
  pinMode(soilSensor1, INPUT);  // Soil sensor 1
  pinMode(soilSensor2, INPUT);  // Soil sensor 2
  pinMode(soilSensor3, INPUT);  // Soil sensor 3
  pinMode(soilSensor4, INPUT);  // Soil sensor 4
  //DEFININDO OS PINOS DE ENTRADA DIGITAL
  pinMode(sensorCheia, INPUT);      // Set the pin for the sensor 1 as input
  pinMode(sensorVazia, INPUT);      // Set the pin for the sensor 2 as input
  pinMode(tank_sensor_pin, INPUT);  // Set the pin for the tank sensor as input
  //DEFININDO OS PINOS DE SAIDA DIGITAL
  pinMode(pump_pin, OUTPUT);  // Set the pin for the pump as output
  pinMode(BUZZER, OUTPUT);
  pinMode(valve_pin1, OUTPUT);
  pinMode(valve_pin2, OUTPUT);
  pinMode(valve_pin3, OUTPUT);
  pinMode(valve_pin4, OUTPUT);
  lcd.begin(40, 4);  // Inicializando o LCD com 40 colunas e 4 linhas
  lcd.clear();       //Limpa a tela
  dht.begin();       // Inicializando o sensor DHT11
}

void loop() {
  controlPump();
  controlDHT();
  controlSoil();
  controlValve(1);
  //Call function to display values
  displayValues(caixa_Vazia_status, caixa_Cheia_status, tank_sensor_status, soilHumidity1, digitalRead(pump_pin), digitalRead(valve_pin1));
  sendDataRF(digitalRead(sensorVazia), digitalRead(sensorCheia), digitalRead(tank_sensor_pin), digitalRead(soilSensor1), digitalRead(pump_pin), digitalRead(valve_pin1));
  delay(2000);
}

void controlPump() {
  // Read the sensor 1
  caixa_Vazia_status = digitalRead(sensorVazia);
  // Read the sensor 2
  caixa_Cheia_status = digitalRead(sensorCheia);
  // Read the tank sensor
  tank_sensor_status = digitalRead(tank_sensor_pin);

  // If both sensors are dry (LOW) and the tank has water (HIGH)
  if ((caixa_Vazia_status == LOW && caixa_Cheia_status == LOW && tank_sensor_status == HIGH) || (caixa_Vazia_status == HIGH && caixa_Cheia_status == LOW && tank_sensor_status == HIGH)) {
    // Turn on the pump
    digitalWrite(pump_pin, HIGH);
    // Turn off the buzzer
    digitalWrite(BUZZER, LOW);
  }
  // If both sensors are wet (HIGH)
  else if (caixa_Vazia_status == HIGH && caixa_Cheia_status == HIGH) {
    // Turn off the pump
    digitalWrite(pump_pin, LOW);
    // Turn off the buzzer
    digitalWrite(BUZZER, LOW);
    // the tank has water (LOW)
  } else if (tank_sensor_status == LOW) {
    // Turn off the pump
    digitalWrite(pump_pin, LOW);
    // Turn off the buzzer
    digitalWrite(BUZZER, LOW);
    // ERRO
  } else if (caixa_Vazia_status == LOW && caixa_Cheia_status == HIGH) {
    // Turn off the pump
    digitalWrite(pump_pin, LOW);
    // Turn on the buzzer
    digitalWrite(BUZZER, HIGH);
  }
}
void controlDHT() {
  // Lendo os valores do sensor DHT11
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}
void controlSoil() {
  // Lendo o valor do sensor de umidade do solo
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
  // Initialize the LCD
  lcd.begin(40, 4);

  // Clear the LCD
  lcd.clear();

  // Go to the first line
  lcd.setCursor(0, 0);
  lcd.print("Sensor 1: ");
  lcd.print(sensor1_status);

  // Go to the second line
  lcd.setCursor(0, 1);
  lcd.print("Sensor 2: ");
  lcd.print(sensor2_status);

  // Go to the third line
  lcd.setCursor(0, 2);
  lcd.print("Tank Sensor: ");
  lcd.print(tank_sensor_status);

  // Go to the fourth line
  lcd.setCursor(0, 3);
  lcd.print("Soil Sensor: ");
  lcd.print(soil_sensor_status);
}
void sendDataRF(int sensor1_status, int sensor2_status, int tank_sensor_status, int soil_sensor_status, int pump_status, int valve_status) {
  // Create an array to store the data
  byte data[6] = { sensor1_status, sensor2_status, tank_sensor_status, soil_sensor_status, pump_status, valve_status };

  // Send the data using RF
  driver.send(data, sizeof(data));
  driver.waitPacketSent();  // Wait for the message to be sent
}