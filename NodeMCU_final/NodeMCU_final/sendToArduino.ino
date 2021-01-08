
/*
   This page is used to send data to Arduino

   Topic aliases created to shorten the time needed to send
   data to Arduino board. e.g. Instead of writing "smart_house/gui/fire_alarm&false"
   to software serial, we are writing "fa&0"
   This enables us to always know the position of substrings

   Topic aliases:
   Sending:
   Name                      Topic String                       Message              Alias
   Fire alarm                smart_house/gui/fire_alarm         1/0                  fa
   Housebreak alarm          smart_house/gui/hbreak_alarm       1/0                  hb
   Water leakage             smart_house/gui/leakage            1/0                  le
   Temp. Indoor              smart_house/gui/temp_indoor        double in Celsius    ti
   Temp. outdoor             smart_house/gui/temp_outdoor       double in Celsius    to
   Stove                     smart_house/gui/stove              1/0                  st
   Window                    smart_house/gui/window             1/0                  wi
   Electricity consumption   smart_house/gui/el_consumption     Int in Watt          ec
   Twilight system           smart_house/gui/twilight           int                  tw
   Power cut                 smart_house/gui/power_cut          1/0                  pc
   Indoor light              smart_house/gui/indoor_light       1/0                  il
   Outdoor light             smart_house/gui/outdoor_light      1/0                  ol
   Arming alarm              smart_house/gui/alarm              1/0                  al
   Fan on/off                smart_house/gui/fan                1/0                  fa
   Fan speed                 smart_house/gui/fan_speed          int                  fs
   Heating indoor            smart_house/gui/heating_in         1/0                  hi
   Heating loft              smart_house/gui/heating_loft       1/0                  hl
   Auto mode                 smart_house/gui/auto_mode          1/0                  am
   Door                      smart_house/gui/door               1/0                  do

   Receiving:
   Name                      Topic String                       Message           Alias
   Indoor light              smart_house/cmd/indoor_light       1/0               il
   Outdoor light             smart_house/cmd/outdoor_light      1/0               ol
   Arming alarm              smart_house/cmd/alarm              1/0               al
   Fan on/off                smart_house/cmd/fan                1/0               fa
   Fan speed                 smart_house/cmd/fan_speed          int               fs
   Heating indoor            smart_house/cmd/heating_in         1/0               hi
   Heating loft              smart_house/cmd/heating_loft       1/0               hl
   Auto mode                 smart_house/cmd/auto_mode          1/0               am
   Auto mode temp value      smart_house/cmd/am_temp_value      int               at

*/

void sendToArduino(char* dataToSend) {
  mySerial.write(dataToSend);
  Serial.write(dataToSend);
  mySerial.write('\n');
  Serial.write('\n');
}
