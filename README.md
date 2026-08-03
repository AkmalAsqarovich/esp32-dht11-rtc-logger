




# ESP32 + DHT11 + DS3231 + SD Card — Harorat/Namlik Logger

ESP32 asosida qurilgan, DHT11 sensori orqali harorat va namlikni, DS3231 RTC
moduli orqali vaqtni o'lchab, natijalarni SD kartaga CSV formatda yozadigan
loyiha. Yig'ilgan ma'lumotlar keyinchalik SQLite bazasiga import qilinadi
va tahlil qilinadi.

## Uskunalar

- ESP32 dev board
- DHT11 (harorat va namlik sensori)
- DS3231 RTC moduli (real vaqt)
- MicroSD card module (SPI)

## Ulanish (pinlar)

| Modul     | ESP32 pin |
|-----------|-----------|
| DHT11     | GPIO 4    |
| SD CS     | GPIO 5    |
| RTC (I2C) | SDA/SCL (standart I2C pinlar) |

## Fayl tuzilishi

```
.
├── asosiy.ino          # Arduino/ESP32 firmware kodi
├── data/
│   ├── data.csv         # SD kartadan olingan namuna log fayli
│   └── schema.sql        # SQLite jadval sxemasi va CSV import skripti
├── .gitignore
└── README.md
```

> Eslatma: `data.db` (SQLite baza fayli) repoga qo'shilmagan, chunki u
> generatsiya qilinadigan binary fayl. Uni quyidagi buyruq bilan o'zingiz
> hosil qilishingiz mumkin:
> ```bash
> sqlite3 data.db < data/schema.sql
> ```

## Ishlash tamoyili

1. `setup()` da SD karta, RTC ishga tushiriladi. RTC quvvatni yo'qotgan
   bo'lsa (`lostPower()`), vaqt kompyuter vaqtiga qarab qayta sozlanadi.
2. `loop()` har 2 soniyada DHT11 va RTC dan o'qiydi, lekin **5 daqiqada
   bir marta** (`delta` o'zgaruvchisi orqali) natijani `/data.csv` fayliga
   yozadi: `temperature_dht, humadity_dht, temperature_rtc, time_day, time_second`.
3. CSV fayl `schema.sql` yordamida SQLite bazasiga import qilinadi —
   bo'sh qatorlar va noto'g'ri (`temperature_dht` bo'sh) yozuvlar
   filtrlanadi, `time_second` ustuni UNIQUE bo'lgani uchun takroriy
   yozuvlar avtomatik e'tiborga olinmaydi.

## Ma'lumotlarni import qilish

```bash
sqlite3 data.db < data/schema.sql
```

## Kelajakdagi rejalar

- [ ] Web dashboard yoki grafik orqali vizualizatsiya
- [ ] Wi-Fi orqali real-vaqt ma'lumot yuborish (masalan MQTT)
- [ ] Sensorlarni kalibrlash

## loyiha haqida video: 
https://youtu.be/SmfQdMWrRA8?si=iwXz6mTU3QW8eMVX
