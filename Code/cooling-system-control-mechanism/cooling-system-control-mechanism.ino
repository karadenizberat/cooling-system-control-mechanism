#include <Wire.h>                                                          //including necessary libraries
#include <EEPROM.h>                          
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128                                                   //Adjusting OLED screen sizes                   
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pinler
const int ROLE_PIN = 2;                                                    //relay pin
const int YESIL_LED = 13;                                                  //Green-Led
const int KIRMIZI_LED = 12;                                                //Red-Led
const int artirButon = 8;                                                  //increase button
const int azaltButon = 9;                                                  //decrement button
const int sistemButon = 7;                                                 //Open-Close button

// NTC Sensör ayarları 
const int ntcPin = A0;                                                     //NTC sensor mathematical settings
const float beta = 3950.0; 
const float roomTempResistance = 100000.0;
const float nominalTemp = 25.0;
const float nominalResistance = 100000.0;

// Değişkenler                                                             //variables
int hedefSicaklik = 5;
int sistemDurumu = 0;
unsigned long sonGuncellemeZamani = 0;
const unsigned long ekranGuncellemeAraligi = 500;
bool artirildi = false;
bool azaltildi = false;
bool sistemButonaBasildi = false;

void setup() {
  pinMode(ROLE_PIN, OUTPUT);
  pinMode(YESIL_LED, OUTPUT);
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(sistemButon, INPUT_PULLUP);
  pinMode(artirButon, INPUT_PULLUP);
  pinMode(azaltButon, INPUT_PULLUP);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED baglanti hatasi!"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Sistem baslatiliyor"));                             //Printing text on the OLED screen "system initializing"
  display.display();
  delay(200);

  hedefSicaklik = EEPROM.read(0);                                        //setting the temperature to the value entered by the user
  sistemDurumu = EEPROM.read(1);
  if (hedefSicaklik < -20 || hedefSicaklik > 10) hedefSicaklik = 5;
  if (sistemDurumu != 0 && sistemDurumu != 1) sistemDurumu = 0;
}

float readTemperature() {
  int adcValue = analogRead(ntcPin);
  if (adcValue == 0) adcValue = 1;

  float resistance = (1023.0 / (float)adcValue) - 1.0;
  resistance = roomTempResistance * resistance;

  float steinhart;
  steinhart = resistance / nominalResistance;
  steinhart = log(steinhart);
  steinhart /= beta;
  steinhart += 1.0 / (nominalTemp + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  return steinhart;
}

void loop() {
  unsigned long simdikiZaman = millis();

  // Sistem butonu (aç/kapa)                                               //system button open close
 if (digitalRead(sistemButon) == HIGH && !sistemButonaBasildi) {
  sistemDurumu = !sistemDurumu;
  EEPROM.write(1, sistemDurumu);
  sistemButonaBasildi = true;
 }

 if (digitalRead(sistemButon) == LOW) {
  sistemButonaBasildi = false;
 }

  // Sistem kapalıysa
  if (sistemDurumu == 0) {
    digitalWrite(ROLE_PIN, HIGH);
    digitalWrite(YESIL_LED, LOW);
    digitalWrite(KIRMIZI_LED, LOW);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Sistem Kapali"));
    display.display();
    return;
  }

  // Sıcaklık ölçümü                                                      //temperature measurement
  float sicaklik = readTemperature();

  // Röle ve LED kontrolü
  if (sicaklik >= hedefSicaklik + 3) {
    digitalWrite(ROLE_PIN, LOW);
    digitalWrite(YESIL_LED, HIGH);
    digitalWrite(KIRMIZI_LED, LOW);
  } else if (sicaklik <= hedefSicaklik) {
    digitalWrite(ROLE_PIN, HIGH);
    digitalWrite(YESIL_LED, LOW);
    digitalWrite(KIRMIZI_LED, HIGH);
  }

  // Artırma butonu (tek basışla artış)
  if (digitalRead(artirButon) == HIGH && !artirildi) {
    hedefSicaklik = min(hedefSicaklik + 1, 10);
    EEPROM.write(0, hedefSicaklik);
    sonGuncellemeZamani = 0;
    artirildi = true;
  }
  if (digitalRead(artirButon) == LOW) {
    artirildi = false;
  }

  // Azaltma butonu (tek basışla azalış)
  if (digitalRead(azaltButon) == HIGH && !azaltildi) {
    hedefSicaklik = max(hedefSicaklik - 1, -20);
    EEPROM.write(0, hedefSicaklik);
    sonGuncellemeZamani = 0;
    azaltildi = true;
  }
  if (digitalRead(azaltButon) == LOW) {
    azaltildi = false;
  }

  // Ekran güncelleme
  if (simdikiZaman - sonGuncellemeZamani >= ekranGuncellemeAraligi) {
    sonGuncellemeZamani = simdikiZaman;

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(F("Teknik Kardesler"));                               //Printing text on the OLED screen"Company name"
    
    display.setCursor(0, 15);
    display.print(F("Ortam: "));
    display.print(sicaklik, 1);
    display.print(F(" C"));

    display.setCursor(0, 30);
    display.print(F("Hedef: "));
    display.print(hedefSicaklik);
    display.print(F(" C"));

    display.setCursor(0, 45);
    display.print(F("Durum: "));
    display.print(digitalRead(ROLE_PIN) ? F("KAPALI") : F("ACIK"));

    display.display();
  }
}
