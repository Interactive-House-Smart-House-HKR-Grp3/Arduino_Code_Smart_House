int electricityConsumption = A0;
int temperature = A1;
int temperatureFan = A2;
int LDR = A3;

char serial_command;

void setup() {
  Serial.begin(9600);

    Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Serial started!");
  
  pinMode(0, INPUT);   //RX
  pinMode(1, INPUT);   //TX
  pinMode(2, INPUT);   //Fire alarm on/off - 1/0
  pinMode(3, INPUT);   //Burglar alarm on/off - 0/1
  pinMode(4, INPUT);   //Water leakage on/off - 1/0
  pinMode(5, INPUT);   //Oven on/off - 1/0
  pinMode(6, INPUT);   //Window on/off - 1/0
  pinMode(7, INPUT);   //Power cut on/off - 1/0
  pinMode(9, INPUT);   //Outside temperature Vout
  pinMode(10, OUTPUT); //Fan

  pinMode(12, OUTPUT); //MUX1
  pinMode(13, OUTPUT); //MUX2
  pinMode(11, OUTPUT); //MUX3
  pinMode(8, OUTPUT);  //MUX4
  
}  

void loop() {
  serial_command = 'g';
  // put your main code here, to run repeatedly:
  if (Serial.available()  > 0) {
    serial_command = Serial.read();
  }


switch(serial_command){
  case '0':
  Serial.println("Turning alarm off...");
  alarmOff();
  delay(300);
  break;

    case '1':
  Serial.println("Turning alarm on...");
  alarmOn();
  delay(300);
  break;

    case '2':
  Serial.println("Turning timer2 off...");
  timer2Off();
  delay(300);
  break;

    case '3':
  Serial.println("Turning timer2 on...");
  timer2On();
  delay(300);
  break;

    case '4':
  Serial.println("Turning indor lights on...");
  indoorLightOn();
  delay(300);
  break;

    case '5':
  Serial.println("Turning indoor light off...");
  indoorLightOff();
  delay(300);
  break;

    case '6':
  Serial.println("Turning burglar alarm on...");
  burglarAlarmOn();
  delay(300);
  break;

    case '7':
  Serial.println("Turning burglar alarm off...");
  burglarAlarmOff();
  delay(300);
  break;

    case '8':
  Serial.println("Turning fan on...");
  fanOn();
  delay(300);
  break;

    case '9':
  Serial.println("Turning fan off...");
  fanOff();
  delay(300);
  break;

    case 'a':
  Serial.println("Turning heat on..");
  heatOn();
  delay(300);
  break;

  case 'b':
  Serial.println("Turning heat off...");
  heatOff();
  delay(300);
  break;
  
    case 'c':
  Serial.println("Turning timer1 on...");
  timer1On();
  delay(300);
  break;
  
    case 'd':
  Serial.println("Turning timer1 off...");
  timer1Off();
  delay(300);
  break;

    case 'e':
  Serial.println("Turning outdoor light on...");
  outdoorLightOn();
  delay(300);
  break;
  
    case 'f':
  Serial.println("Turning outdoor light off...");
  outdoorLightOff();
  delay(300);
  break;

    default:
  break;
  }
}

void alarmOff(){
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(8, LOW); 
}

void alarmOn(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(8, LOW); 
}

void timer2On(){
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(8, HIGH); 
}

void timer2Off(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   digitalWrite(11, LOW); 
   digitalWrite(8, HIGH); 
}

void indoorLightOn(){
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, LOW); 
}

void indoorLightOff(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, LOW); 
}

void burglarAlarmOn(){
   digitalWrite(12, LOW); 
   digitalWrite(13, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, HIGH); 
}

void burglarAlarmOff(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, LOW); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, HIGH); 
}

void fanOn(){
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, LOW); 
}

void fanOff(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, LOW); 
}

void heatOn(){
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(8, HIGH); 
}

void heatOff(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(8, HIGH); 
}

void timer1On(){
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(8, LOW); 
}

void timer1Off(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, LOW); 
   digitalWrite(8, LOW); 
}

void outdoorLightOn(){
   digitalWrite(12, LOW); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, HIGH); 
}

void outdoorLightOff(){
   digitalWrite(12, HIGH); 
   digitalWrite(13, HIGH); 
   digitalWrite(11, HIGH); 
   digitalWrite(8, HIGH); 
}
