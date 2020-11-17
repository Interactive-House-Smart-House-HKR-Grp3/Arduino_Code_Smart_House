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

String msg;
int timeNow = millis();
int timeNow2 = millis();
int timeNow3 = millis();
bool writing = false;

void toggleLed(String, String);

void sendToWiFi(char*);

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
    while (!mySerial.available()) {
    ;
  }
  //mySerial.println("Hello, world?");
}

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
    toggleIndoorLight(t, p); // Toggle the indoor light
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

void toggleIndoorLight(String top, String mes) {
  top.trim();
  mes.trim();
  if (top == "il") {
    Serial.println(top);
    Serial.println(mes);
    if (mes == "1") {
      indoorLightOn();
      sendToWiFi("il&1");
      printReaction();

    } else if (mes == "0") {
      indoorLightOff();
      sendToWiFi("il&0");
      printReaction();
    }
    delay(10);
  }

}

void printReaction(){
      timeReacted = millis();
      Serial.print("Reacted in ");
      Serial.print(timeReacted - timeArrived);
      Serial.print(" ms");
      Serial.println();
  }
