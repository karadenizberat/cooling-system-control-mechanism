# 🚐 Vehicle Refrigerator Controller (ATmega-based)

This project is designed to control compact refrigerators used in
vehicles. It is based on an ATmega microcontroller and includes:

-   ❄️ Real-time temperature monitoring with an NTC sensor\
-   🔌 Relay control for compressor on/off\
-   📟 OLED display to show ambient and target temperatures\
-   💾 EEPROM storage for saving power state and target temperature\
-   🔘 Button interface to adjust temperature and toggle system on/off

The system continuously monitors ambient temperature and activates the
cooling system when needed. It is ideal for automotive refrigeration
applications requiring reliability and efficiency.

------------------------------------------------------------------------

## 🛠️ Hardware Components

-   ATmega microcontroller (e.g. ATmega328P)
-   NTC Thermistor
-   Relay module (12V/24V depending on compressor)
-   OLED Display (SSD1306 - 128x64)
-   EEPROM (onboard)
-   Push Buttons (Increase / Decrease / Power)
-   Green & Red LEDs for status indication

------------------------------------------------------------------------

## 📁 File Structure

Vehicle-Fridge-Controller/ │ ├── kod/ → Arduino source code (.ino file)
├── eagle/ → Circuit schematic (.sch) & PCB layout (.brd) ├── img/ →
Circuit photos, 3D renders, real setup images └── README.md → Project
description (this file)

------------------------------------------------------------------------

## 🔧 Setup Instructions

1.  Upload the `.ino` code to the ATmega chip using Arduino or ISP
    method.
2.  Wire the components as shown in the schematic (see `eagle/` and
    `img/` folders).
3.  Adjust the target temperature using the buttons.
4.  OLED will show real-time ambient temperature, target, and system
    state.
5.  System state and target temperature are stored in EEPROM, so they
    persist after power-off.

------------------------------------------------------------------------

## 🇹🇷 Proje Açıklaması (Türkçe)

Bu proje, araçlarda kullanılan küçük buzdolaplarını kontrol etmek
amacıyla geliştirilmiştir. ATmega mikrodenetleyici tabanlıdır ve:

-   🌡️ NTC sensörü ile sıcaklık ölçümü\
-   🔁 Röle modülü ile kompresör kontrolü\
-   🖥️ OLED ekran ile sıcaklık ve sistem durumu gösterimi\
-   💾 EEPROM ile sıcaklık ve sistem durumu kaydı\
-   🔘 Butonlarla sıcaklık ayarlama ve sistemi aç/kapatma

Sistem, belirlenen hedef sıcaklığa göre otomatik olarak kompresörü
devreye alır veya durdurur.

------------------------------------------------------------------------

## 📸 Görseller

Aşağıda sistemin gerçek devresi, Eagle şeması ve çalışma görüntüleri yer
alabilir. Bunları `img/` klasöründe saklayın.

------------------------------------------------------------------------

## 🧠 Lisans ve Katkı

Bu proje MIT lisansı altındadır. Dilerseniz fork edip geliştirmelere
katkı sağlayabilirsiniz.

------------------------------------------------------------------------

## 📬 İletişim / Communication

Geliştirici / Developer : \[Berat Karadeniz\]\
GitHub: \[https://github.com/karadenizberat\] LinkedIn:
\[https://www.linkedin.com/in/karadenizberat/\]
