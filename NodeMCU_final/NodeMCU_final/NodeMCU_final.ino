#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

#define STASSID "Nemanja"
#define STAPSK  "aezakmikjkszpj"

const char* ssid     = STASSID;
const char* password = STAPSK;
const char* mqtt_server = "smart-mqtthive.duckdns.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

String msg1;
String t = "";
String p = "";
/*
  "Nemanja",
  "aezakmikjkszpj",
  "http://smart-mqtthive.duckdns.org",  // MQTT Broker server ip
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted

*/

SoftwareSerial mySerial(4, 5); // RX, TX
int i;
bool state = true;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String tpc = (String) topic;
  String pld;
  String mssg;
  if (tpc.equals("smart_house/cmd/indoor_light")) {
    mssg = "il&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("true")) {
      mssg += "1";
    } else if (pld.equals("false")) {
      mssg += "0";
    }


  } else if (tpc.equals("smart_house/cmd/outdoor_light")) {
    mssg = "ol&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("true")) {
      mssg += "1";
    } else if (pld.equals("false")) {
      mssg += "0";
    }



  } else if (tpc.equals("smart_house/cmd/alarm")) {
    mssg = "al&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("true")) {
      mssg += "1";
    } else if (pld.equals("false")) {
      mssg += "0";
    }


  } else if (tpc.equals("smart_house/cmd/fan")) {
    mssg = "fa&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("true")) {
      mssg += "1";
    } else if (pld.equals("false")) {
      mssg += "0";
    }


  } else if (tpc.equals("smart_house/cmd/fan_speed")) {
    mssg = "fs&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("1")) {
      mssg += "125";
    } else if (pld.equals("2")) {
      mssg += "190";
    }
    else if (pld.equals("3")) {
      mssg += "255";
    }


  } else if (tpc.equals("smart_house/cmd/heating_in")) {
    mssg = "hi&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("true")) {
      mssg += "1";
    } else if (pld.equals("false")) {
      mssg += "0";
    }


  } else if (tpc.equals("smart_house/cmd/heating_loft")) {
    mssg = "hl&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("true")) {
      mssg += "1";
    } else if (pld.equals("false")) {
      mssg += "0";
    }


  } else if (tpc.equals("smart_house/cmd/auto_mode")) {
    mssg = "am&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    if (pld.equals("true")) {
      mssg += "1";
    } else if (pld.equals("false")) {
      mssg += "0";
    }


  } else if (tpc.equals("smart_house/cmd/am_temp_value")) {
    mssg = "at&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    mssg += pld;

  } else if (tpc.equals("smart_house/cmd/temp_indoor")) {
    mssg = "ti&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    mssg += pld;
  } else if (tpc.equals("smart_house/cmd/temp_outdoor")) {
    mssg = "to&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    mssg += pld;
  } else if (tpc.equals("smart_house/cmd/el_consumption")) {
    mssg = "ec&";
    for (int k = 0; k < length; k++) {
      pld += (char)payload[k];
    }
    pld.trim();
    mssg += pld;
  }
  // Converting message to char array to send to Arduino
  int str_len = mssg.length() + 1;
  char mssgArr[str_len];
  mssg.toCharArray(mssgArr, str_len);
  sendToArduino(mssgArr);
}

void writeToSerial(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  mySerial.write(topic);
  mySerial.write("&");
  for (int i = 0; i < length; i++) {
    mySerial.write((char)payload[i]);
    Serial.print((char)payload[i]);
  }
  mySerial.write('\r\n');
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      subscribeToTopics();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ;
  }

  Serial.println("Serial started!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  subscribeToTopics();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();

  readFromArduino();
  t = "";
  p = "";
}

void readFromArduino() { // to be replaced with new split string
  while (mySerial.available() > 0) {
    msg1 = (String)mySerial.readString();
    for (int i = 0; i < msg1.length(); i++) {
      if (msg1.substring(i, i + 1) == "&") {
        t = msg1.substring(0, i);
        p = msg1.substring(i + 1);
        break;
      }
    }
    t.trim();
    p.trim();
    printSmt(t, p);
    if (t.equals("il")) {
      if (p.equals("1")) {
        client.publish("smart_house/gui/indoor_light", "true");
      } else if (p.equals("0")) {
        client.publish("smart_house/gui/indoor_light", "false");
      }
    } else if (t.equals("ol")) {
      if (p.equals("1")) {
        client.publish("smart_house/gui/outdoor_light", "true");
      } else if (p.equals("0")) {
        client.publish("smart_house/gui/outdoor_light", "false");
      }
    } else if (t.equals("al")) {
      if (p.equals("1")) {
        client.publish("smart_house/gui/alarm", "true");
      } else if (p.equals("0")) {
        client.publish("smart_house/gui/alarm", "false");
      }
    } else if (t.equals("fa")) {
      if (p.equals("1")) {
        client.publish("smart_house/gui/fan", "true");
      } else if (p.equals("0")) {
        client.publish("smart_house/gui/fan", "false");
      }
    } else if (t.equals("fs")) {
      if (p.equals("125")) {
        client.publish("smart_house/gui/fan_speed", "1");
      } else if (p.equals("190")) {
        client.publish("smart_house/gui/fan_speed", "2");
      } else if (p.equals("255")) {
        client.publish("smart_house/gui/fan_speed", "3");
      }
    } else if (t.equals("hi")) {
      if (p.equals("1")) {
        client.publish("smart_house/gui/heating_in", "true");
      } else if (p.equals("0")) {
        client.publish("smart_house/gui/heating_in", "false");
      }
    } else if (t.equals("hl")) {
      if (p.equals("1")) {
        client.publish("smart_house/gui/heating_loft", "true");
      } else if (p.equals("0")) {
        client.publish("smart_house/gui/heating_loft", "false");
      }
    } else if (t.equals("am")) {
      if (p.equals("1")) {
        client.publish("smart_house/gui/auto_mode", "true");
      } else if (p.equals("0")) {
        client.publish("smart_house/gui/auto_mode", "false");
      }
    } else if (t.equals("at")) {
      int strlng = p.length() + 1;
      char pArr[strlng];
      p.toCharArray(pArr, strlng);
      client.publish("smart_house/gui/auto_temp_value", pArr);
    } else if (t.equals("ti")) {
      int strlng = p.length() + 1;
      char pArr[strlng];
      p.toCharArray(pArr, strlng);
      client.publish("smart_house/gui/temp_indoor", pArr);
    } else if (t.equals("to")) {
      int strlng = p.length() + 1;
      char pArr[strlng];
      p.toCharArray(pArr, strlng);
      client.publish("smart_house/gui/temp_outdoor", pArr);
    } else if (t.equals("ec")) {
      int strlng = p.length() + 1;
      char pArr[strlng];
      p.toCharArray(pArr, strlng);
      client.publish("smart_house/gui/el_consumption", pArr);
    }

  }
}
void printSmt(String a, String b) {
  Serial.println("From arduino:");
  Serial.println(a);
  Serial.println(b);
  delay(10);
}

void subscribeToTopics() {
  client.subscribe("smart_house/cmd/indoor_light");
  client.subscribe("smart_house/cmd/outdoor_light");
  client.subscribe("smart_house/cmd/alarm");
  client.subscribe("smart_house/cmd/fan");
  client.subscribe("smart_house/cmd/fan_speed");
  client.subscribe("smart_house/cmd/heating_in");
  client.subscribe("smart_house/cmd/heating_loft");
  client.subscribe("smart_house/cmd/auto_mode");
  client.subscribe("smart_house/cmd/am_temp_value");
  client.subscribe("smart_house/cmd/temp_indoor");
  client.subscribe("smart_house/cmd/temp_outdoor");
  client.subscribe("smart_house/cmd/el_consumption");
  //
}
