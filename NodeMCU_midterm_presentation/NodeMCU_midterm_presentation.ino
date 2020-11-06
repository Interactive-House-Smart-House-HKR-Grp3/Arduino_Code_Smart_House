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
/*
  "Nemanja",
  "aezakmikjkszpj",
  "http://smart-mqtthive.duckdns.org",  // MQTT Broker server ip
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted

*/

SoftwareSerial mySerial(4, 5); // RX, TX
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

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

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
      client.subscribe("smart_house/indoor_light");
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
  // put your setup code here, to run once:
  Serial.begin(57600);
  while(!Serial){
    ;}

  Serial.println("Serial started!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");

  setup_wifi();
  client.subscribe("smart_house/indoor:light");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


String msg1;
String t = "";
String p = "";

void loop() {

  // put your main code here, to run repeatedly:
//  state = !state;
//    mySerial.write(state);
//    Serial.print("Sent: ");
//    Serial.print(state);
//    Serial.println();
//    delay(1000);


  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "hello world #%ld", value);
 
  }
    delay(100);
    readFromArduino();
    t="";
    p="";

  
}

void readFromArduino(){
      while (mySerial.available() > 0) {
    msg1 = (String)mySerial.readString();
    for (int i = 0; i < msg1.length(); i++) {
      if (msg1.substring(i, i + 1) == "&") {
        t = msg1.substring(0, i);
        p = msg1.substring(i + 1);
        break;
      }
    }
    printSmt(t,p);

  }
  }
void printSmt(String a, String b){
    Serial.println("From arduino:");
    Serial.println(a);
    Serial.println(b);
    delay(10);
  }
