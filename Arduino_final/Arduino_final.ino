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
int timeNow;
int timeNow2;
int timeNow3;
bool writing = false;

const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

bool alarmArmed = false;
int fanSpeed = 0;
bool autoMode = false;
bool autoTemp = 0;
bool inTmp = true;
bool outTmp = false;
bool elCon = false;

void toggleLed(String, String);

void sendToWiFi(char*);

String splitString(String, char[], uint8_t);

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
  timeNow = millis();
  timeNow2 = timeNow;
  timeNow3 = timeNow2;
  //mySerial.println("Hello, world?");
}

void loop() {
  /*if (Serial.available()  > 0) {
    serial_command = Serial.read();
    }*/
  // Separating topic and message
  while (mySerial.available() > 0) {
    timeNow = millis();
    timeArrived = millis();
    msg = (String)mySerial.readString();
    t = splitString(msg, "&", 0);
    p = splitString(msg, "&", 1);
    Serial.println(t);
    Serial.println(p);
    t.trim();
    p.trim();
    // Converting message to char array to send to Arduino
    int str_len = msg.length() + 1;
    char mssgArr[str_len];
    msg.toCharArray(mssgArr, str_len);
    if (t.equals("il")) {
      if (p.equals("1")) {
        indoorLightOn();
        sendToWiFi(mssgArr);

      } else if (p.equals("0")) {
        indoorLightOff();
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("ol")) {
      if (p.equals("1")) {
        outdoorLightOn();
        sendToWiFi(mssgArr);

      } else if (p.equals("0")) {
        outdoorLightOff();
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("al")) {
      if (p.equals("1")) {
        alarmArmed = true;
        sendToWiFi(mssgArr);

      } else if (p.equals("0")) {
        alarmArmed = false;
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("fa")) {
      if (p.equals("1")) {
        fanOn();
        sendToWiFi(mssgArr);

      } else if (p.equals("0")) {
        fanOff();
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("fs")) {
      if (p.equals("125")) {
        fanSpeed = 125;
        sendToWiFi(mssgArr);

      } else if (p.equals("195")) {
        fanSpeed = 195;
        sendToWiFi(mssgArr);

      } else if (p.equals("255")) {
        fanSpeed = 255;
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("hi")) {
      if (p.equals("1")) {
        heatOn();
        sendToWiFi(mssgArr);
      } else if (p.equals("0")) {
        heatOff();
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("hl")) {
      if (p.equals("1")) {
        //heatWindOn();
        sendToWiFi(mssgArr);
      } else if (p.equals("0")) {
        //heatWindOff();
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("am")) {
      if (p.equals("1")) {
        autoMode = true;
        sendToWiFi(mssgArr);
      } else if (p.equals("0")) {
        autoMode = false;
        sendToWiFi(mssgArr);

      }
    } else if (t.equals("at")) {
      autoTemp = p.toInt();
      Serial.println("auto temp: ");
      Serial.println(p);
      sendToWiFi(mssgArr);

    }
  }
  //sendTempData();
}

void sendTempData() {
  String msg = "ti&22.2";
  int str_len = msg.length() + 1;
  char mssgArr[str_len];
  msg.toCharArray(mssgArr, str_len);
  sendToWiFi(mssgArr);
  delay(800);
  msg = "to&18.2";
  str_len = msg.length() + 1;
  mssgArr[str_len];
  msg.toCharArray(mssgArr, str_len);
  sendToWiFi(mssgArr);
  delay(800);
  msg = "ec&500";
  str_len = msg.length() + 1;
  mssgArr[str_len];
  msg.toCharArray(mssgArr, str_len);
  sendToWiFi(mssgArr);
  delay(500);
}

void printReaction() {
  timeReacted = millis();
  Serial.print("Reacted in ");
  Serial.print(timeReacted - timeArrived);
  Serial.print(" ms");
  Serial.println();
}
