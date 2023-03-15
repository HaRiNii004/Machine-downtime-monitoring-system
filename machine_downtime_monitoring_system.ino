#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Blynk.h>

char auth[] = "YOUR_AUTH_TOKEN";
char ssid[] = "STUDENT";
char pass[] = "iot@2025";

#define BLYNK_TEMPLATE_ID "TMPLI3nv5am6"
#define BLYNK_TEMPLATE_NAME "Machine downtime monitoring system"
#define BLYNK_AUTH_TOKEN "ANgnrHXlx9rwZ2LK6AIeLYalFRsPL46p"

#define BLYNK_PRINT Serial
#define BLYNK_TIMEOUT_MS 5000
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int vibrationPin = D1;  // Connect vibration sensor to D1 pin
int soundPin = D2; // Connect sound sensor to D1 pin
int threshold = 600; // Adjust the threshold value based on your sensor

BlynkTimer timer;
bool isMachineRunning = false;
bool isVibrationDetected = false;


void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  while (!Blynk.connected()) {
    delay(1000);
  }
  pinMode(vibrationPin, INPUT);
  timer.setInterval(5000L, checkMachineStatus);
  pinMode(soundPin, INPUT);
  
  dht.begin();
  }


void loop() {
  Blynk.run();
  timer.run();
}

void checkMachineStatus() {
  //  float temperature = bme.readTemperature();
  //  float humidity = bme.readHumidity();
  //  float pressure = bme.readPressure() / 100.0F;
  float temperature = random(100,200)/10;
  float humidity = random(300,400)/10;
  float pressure = random(400,500)/10;;

  int vibrationValue = digitalRead(vibrationPin);
  isVibrationDetected = (vibrationValue == HIGH);

  if (temperature >= 40.0 || isVibrationDetected) {
    if (!isMachineRunning) {
      Serial.println("Machine downtime started.");
      isMachineRunning = true;
    }
  } else {
    if (isMachineRunning) {
      Serial.println("Machine downtime ended.");
      isMachineRunning = false;
    }
  }
}

    
    void checkSoundLevel() {
  int soundValue = analogRead(soundPin);
  Serial.println(soundValue);
  
  if (soundValue > threshold) {
     Serial.println("Machine downtime started.");
  }
    }
  //Blynk.virtualWrite(V0, temperature);
  //Blynk.virtualWrite(V1, humidity);
  //Blynk.virtualWrite(V2, VibrationisDetected);
