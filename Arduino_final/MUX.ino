void alarmOff() {
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  digitalWrite(8, LOW);
}

void alarmOn() {
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  digitalWrite(8, LOW);
}

void timer2On() {
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  digitalWrite(8, HIGH);
}

void timer2Off() {
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  digitalWrite(8, HIGH);
}

void indoorLightOn() {
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(8, LOW);
}

void indoorLightOff() {
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(8, LOW);
}

void burglarAlarmOn() {
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(8, HIGH);
}

void burglarAlarmOff() {
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(8, HIGH);
}

void fanOn() {
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(8, LOW);
}

void fanOff() {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(8, LOW);
}

void heatOn() {
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(8, HIGH);
}

void heatOff() {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(8, HIGH);
}

void timer1On() {
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(8, LOW);
}

void timer1Off() {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(8, LOW);
}

void outdoorLightOn() {
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(8, HIGH);
}

void outdoorLightOff() {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(8, HIGH);
}
