#include "FS.h" //for sd card
#include "SD.h" //for sd card
#include "SPI.h" //for sd card
#include "DHT.h" // for temp and humadity sensor
#include "Wire.h" // for time
#include "RTClib.h" // for time

#define DHTPIN 4
#define DHTTYPE DHT11


DHT dht(DHTPIN,DHTTYPE);
RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);

  if(!SD.begin(5)){
    Serial.println("Cardga ulanishda xatolik");
    return;
  }

  if(!rtc.begin()){
    Serial.println("RTC modul topilmadi");
    while(1);
  }

  if(rtc.lostPower()){
    Serial.println("RTC vaqtni sozladi");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  File file = SD.open("/data.csv",FILE_APPEND);
  if(file){
    Serial.println("SD card ochildi");
    file.println();
  } 
  file.close();

}


int delta=0;
void loop() {
  delay(2000);
  float h_dht=dht.readHumidity();
  float t_dht=dht.readTemperature();
  float t_rtc=rtc.getTemperature();
  DateTime now=rtc.now();
  File file= SD.open("/data.csv",FILE_APPEND);  ///-------------------file ochildi
  if(file){
    if(now.day()*24*60+now.hour()*60+now.minute()-delta>5){
      Serial.println("yozilayabdi");
      delta=now.day()*24*60+now.hour()*60+now.minute();
      file.print(t_dht);
      file.print(",");

      file.print(h_dht);
      file.print(",");

      file.print(t_rtc);
      file.print(",");

      file.print(now.year(), DEC);
      file.print('/');
      file.print(now.month(), DEC);
      file.print('/');
      file.print(now.day(), DEC);
      file.print(",");

      file.print(now.hour(), DEC);
      file.print(':');
      file.print(now.minute(), DEC);
      file.print(':');
      file.println(now.second(), DEC);
      delay(2000);
    }
  }
  else{
    Serial.println("File ochishda xatolik");
  }

  file.close();          ///----------------------------file yopildi
}