CREATE TABLE IF NOT EXISTS "data"(
    "id" INTEGER,
    "temperature_dht" TEXT,
    "humadity_dht" TEXT,
    "temperature_rtc",
    "time_day" TEXT,
    "time_second" TEXT UNIQUE,
    PRIMARY KEY("id")
);

.import --csv data.csv temp

DELETE FROM "temp"
WHERE "temperature_dht" IS NULL OR "temperature_dht" = ''; 

INSERT OR IGNORE INTO "data" ("temperature_dht", "humadity_dht", "temperature_rtc", "time_day", "time_second")
SELECT "temperature_dht", "humadity_dht", "temperature_rtc", "time_day", "time_second" FROM "temp";

drop table temp;