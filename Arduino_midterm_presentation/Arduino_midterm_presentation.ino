#include <SoftwareSerial.h>


SoftwareSerial mySerial(A4, A5); // RX, TX
int i;
bool substring = false;
char* topic;
char* payload;

String t = "";
String p = "";

int timeArrived = 0;
int timeReacted = 0;

char serial_command = 0;

void toggleLed(String a, String b);

void setup() {
  pinMode(12, OUTPUT); //MUX1
  pinMode(13, OUTPUT); //MUX2
  pinMode(11, OUTPUT); //MUX3
  pinMode(8, OUTPUT);  //MUX4

  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Serial started!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  //mySerial.println("Hello, world?");
}
String msg;
int timeNow = millis();
int timeNow2 = millis();
int timeNow3 = millis();
bool writing = false;
void loop() {
  if (Serial.available()  > 0) {
    serial_command = Serial.read();
  }

  // Separating topic and message
  while (mySerial.available() > 0) {
    timeArrived = millis();
    msg = (String)mySerial.readString();
    for (int i = 0; i < msg.length(); i++) {
      if (msg.substring(i, i + 1) == "&") {
        t = msg.substring(0, i);
        p = msg.substring(i + 1);
        break;
      }
    }
    toggleLed2(t, p); // Toggle the light
  }

  // Test reading from com port
  // (good for testing all MUX functions)
  if (serial_command == '1') {
    Serial.println("I received: 1");
    delay(10);
  }

  if (serial_command == '2') {
    Serial.println("I received: 2");
    delay(10);
  }

  if (serial_command == '3') {
    Serial.println("I received: 3");
    delay(10);
  }

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

void toggleLed2(String a, String b) {
  a.trim();
  b.trim();
  if (a == "smart_house/indoor_light") {
    Serial.println(a);
    Serial.println(b);
    if (b == "true") {
      //digitalWrite(13, HIGH);
      indoorLightOn();
      mySerial.write("smart_house/indoor_light&true");
      //mySerial.write('\n');
    } else     if (b == "false") {
      //digitalWrite(13, LOW);
      indoorLightOff();
      mySerial.write("smart_house/indoor_light&false");
      //mySerial.write('\n');
    }
  }
}

void toggleLed(String a, String b) {
  a.trim();
  b.trim();
  if (a == "smart_house/indoor_light") {
    Serial.println(a);
    Serial.println(b);
    if (b == "true") {
      digitalWrite(13, HIGH);
      mySerial.write("smart_house/gui/indoor_light&true");
      mySerial.write('\n');
      //indoorLightOn();
      timeReacted = millis();
      Serial.print("Reacted in ");
      Serial.print(timeReacted - timeArrived);
      Serial.print(" ms");
      Serial.println();
    } else if (b == "false") {
      digitalWrite(13, LOW);
      //indoorLightOff();
      mySerial.write("smart_house/gui/indoor_light&false");
      mySerial.write('\n');
      timeReacted = millis();
      Serial.print("Reacted in ");
      Serial.print(timeReacted - timeArrived);
      Serial.print(" ms");
      Serial.println();
    }
    delay(10);
  }

}
