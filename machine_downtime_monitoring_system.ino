#define BLYNK_TEMPLATE_ID "TMPLI3nv5am6"
#define BLYNK_TEMPLATE_NAME "Machine downtime monitoring system"
#define BLYNK_AUTH_TOKEN "ANgnrHXlx9rwZ2LK6AIeLYalFRsPL46p"

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
WidgetLCD lcd(V4);

char auth[] = "ANgnrHXlx9rwZ2LK6AIeLYalFRsPL46p";
char ssid[] = "STUDENT";
char pass[] = "iot@2025";

#define BLYNK_TIMEOUT_MS 5000
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define vibration
int soundValue = analogRead(A0);
#define VibrationDetected


#define v  D1  // Connect vibration sensor to D1 pin
#define sound_analog A0
int threshold = 600; // Adwjust the threshold value based on your sensor

BlynkTimer timer;
bool isMachineRunning = false;
// bool isVibrationDetected = false;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(D1, INPUT);
  //pinMode(sound_digital, INPUT);
  pinMode(sound_analog, INPUT);

  dht.begin();
  timer.setInterval(5000L, notify);
}


void loop() {
  notify();
  Blynk.run();
  timer.run();



}
void notify()
{
  float t = dht.readTemperature();
  Serial.println(t);
  int vib = digitalRead(D1);
   Serial.println(D1);
   
  if (t <= 40.0 && vib == 1  ) {
    Serial.println("machine downtime started");
    Blynk.logEvent("off", "Machine downtime started");
    lcd.clear();
    lcd.print(0, 1, "machine is downtime");
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V2, vib);
    Blynk.virtualWrite(V3, soundValue);


  }
}
