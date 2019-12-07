#include <ESP8266_Simple.h>
#include <SoftwareSerial.h>
#include <XBOXRECV.h>
#include <SPI.h>
#include <Servo.h>

#if 0
  #define INCLUDE_CONTROLLER
#endif

#if 1
  #define INCLUDE_GPS
#endif

#if 1
  #define INCLUDE_WIFI
  // These are the SSID and PASSWORD to connect to your Wifi Network
  //  put details appropriate for your network between the quote marks,
  //  eg  #define ESP8266_SSID "YOUR_SSID"
  #define ESP8266_SSID  "UnwiredHome"
  #define ESP8266_PASS  "L3nticular"
#endif

#ifdef INCLUDE_CONTROLLER
// XBox Controller members
USB Usb;
XBOXRECV Xbox(&Usb);

// internal state members
enum DIRECTION {
  STRAIGHT,
  BACKWARDS,
  GOLEFT,
  GORIGHT,
  STOP
};

int pinLB=17;     // Define a 14 Pin
int pinLF=14;     // Define a 15 Pin
int pinRB=15;    // Define a 16 Pin
int pinRF=16;    // Define a 17 Pin
DIRECTION currentDirection = STOP;

void go()     // go
{
  //Serial.println("straight");
  digitalWrite(pinRF,HIGH);  // 16 feet for high level
  digitalWrite(pinRB,LOW);   //17 feet for low level
  //analogWrite(MotorRPWM,180);//Set the output speed(PWM)
  digitalWrite(pinLF,HIGH);  // 14 feet for high level
  digitalWrite(pinLB,LOW);   //15 feet for high level
  //analogWrite(MotorLPWM,180);//Set the output speed(PWM)
}

void right()        //right
{
  //Serial.println("go_right");
  digitalWrite(pinRB,LOW);   
  digitalWrite(pinRF,HIGH);
  //analogWrite(MotorRPWM,250);
  digitalWrite(pinLB,LOW);
  digitalWrite(pinLF,LOW);
}
    
void left()         //left
{
  //Serial.println("go_left");
  digitalWrite(pinRB,LOW);
  digitalWrite(pinRF,LOW);
  digitalWrite(pinLB,LOW);   
  digitalWrite(pinLF,HIGH);
  //analogWrite(MotorLPWM,250);
}
    
void stopp()         //stop
{
  //Serial.println("stop");
  digitalWrite(pinRB,LOW);
  digitalWrite(pinRF,LOW);
  digitalWrite(pinLB,LOW);
  digitalWrite(pinLF,LOW);
}

void back()          //back
{
  //Serial.println("back");
  digitalWrite(pinRF,LOW);  
  digitalWrite(pinRB,HIGH);
  //analogWrite(MotorRPWM,0);
  digitalWrite(pinLF,LOW);  
  digitalWrite(pinLB,HIGH);
  //analogWrite(MotorLPWM,230);
}

void move(DIRECTION dir) {
  switch(dir) {
    case STRAIGHT:
      go();
      break;
    case BACKWARDS:
      back();
      break;
    case GOLEFT:
      left();
      break;
    case GORIGHT:
      right();
      break;
    case STOP:
    default:
      stopp();
      break;
  }
}
#endif

// we use longitude/latitude outside the GPS context too, so define globally.
String RMClatitude,RMClongitude;
#ifdef INCLUDE_GPS
// GPS members
String data="";
int mark = 0;
boolean Mark_Start=false;
boolean valid=false;
String GGAUTCtime,GGAlatitude,GGAlongitude,GPStatus,SatelliteNum,HDOPfactor,Height,
PositionValid,RMCUTCtime,Speed,Direction,Date,Declination,Mode;
SoftwareSerial SerialGPS(18, 19); // use pin 18 & 19 as Rx and Tx

// GPS helper methods
String reader(){
  String value="";
  int temp;
startover:
  while (SerialGPS.available() > 0){
    delay(2);
    temp=SerialGPS.read();
    if((temp==',')||(temp=='*')){
      if(value.length()){
        return value;
      }
      else {
        return "";
      }     
    }
    else if(temp=='$'){
      // failure
      Mark_Start=false;
    }
    else{
      value+=char(temp);
    }
  }
  while (!(SerialGPS.available()>0)){
  }
  goto startover;
}
#endif

#ifdef INCLUDE_WIFI
ESP8266_Simple wifi(4,3);

unsigned long httpCommand(char *buffer, int bufferLength)
{  
  Serial.println("Evoked /command handler.");
  static int cnt = 0;
  
  cnt++;
  String numberString = String(cnt);

  memset(buffer,0,bufferLength);
  strncpy_P(buffer, numberString.c_str(), bufferLength-strlen(buffer));
  
  // And return the type and HTTP response code combined with "|" (bitwise or)
  // Valid  types are: ESP8266_HTML, ESP8266_TEXT, ESP8266_RAW
  // Valid  response codes are: any standard HTTP response code (typically, 200 for OK, 404 for not found, and 500 for error)
  
  return ESP8266_HTML | 200;
}

unsigned long http404(char *buffer, int bufferLength)
{  
  Serial.println("Evoked 404 handler.");
  memset(buffer, 0, bufferLength);  
  strcpy_P(buffer, PSTR("<h1>Error, Unknown Command</h1>\r\n<p>Try <a href=\"/command\">/command</a>.</p>"));
  return ESP8266_HTML | 404;
}

unsigned long httpGPS(char *buffer, int bufferLength)
{  
  Serial.println("Evoked GPS handler.");
  memset(buffer, 0, bufferLength);
  strncpy_P(buffer, PSTR("{\"latitude\": \""), bufferLength);
  strncpy(buffer+strlen(buffer), RMClatitude.c_str(), bufferLength-strlen(buffer));
  strncpy_P(buffer+strlen(buffer), PSTR("\", \"longitude\": \""), bufferLength-strlen(buffer));
  strncpy(buffer+strlen(buffer), RMClongitude.c_str(), bufferLength-strlen(buffer));
  strncpy_P(buffer+strlen(buffer), PSTR("\"}"), bufferLength-strlen(buffer));
  Serial.println("Send GPS response");
  Serial.print("Longitude: ");
  Serial.println(RMClongitude);
  Serial.print("Latitude: ");
  Serial.println(RMClatitude);
  return ESP8266_HTML | 200;
}
#endif

void setup()
{
  Serial.begin(9600); // Serial Port - USB connection to PC for debugging

#ifdef INCLUDE_GPS
  Serial.println("Begin GPS setup");
  SerialGPS.begin(9600); // 9600 is the baud rate
  Serial.println("GPS setup finished!");

  Serial.println("Read GPS data");
  bool dataRead = false;
  do {
    // get GPS data
    SerialGPS.listen();
    delay(2);
    while(SerialGPS.available() > 0) {    
      Serial.println("GPS available");
      if(Mark_Start){
        data=reader();
        //Serial.println(data);
        if(data.equals("GPGGA")){
          //Serial.println(1);
          GGAUTCtime=reader();
          GGAlatitude=reader();
          GGAlatitude+=reader();
          GGAlongitude=reader();
          GGAlongitude+=reader();
          GPStatus=reader();
          SatelliteNum=reader();
          HDOPfactor=reader();
          Height=reader();
          Mark_Start=false;
          valid=true;
          data="";
  
        }
        else if(data.equals("GPGSA")){\
          Mark_Start=false;
          data="";
        }
        else if(data.equals("GPGSV")){\
          Mark_Start=false;
          data="";
        }
        else if(data.equals("GPRMC")){\
          RMCUTCtime=reader();
          PositionValid=reader();
          RMClatitude=reader();
          RMClatitude+=reader();
          RMClongitude=reader();
          RMClongitude+=reader();
          Speed=reader();
          Direction=reader();
          Date=reader();
          Declination=reader();
          Declination+=reader();
          Mode=reader();
          valid=true;
          Mark_Start=false;
          data="";
        }
        else if(data.equals("GPVTG")){\
          Mark_Start=false;
          data="";
        }
        else{\
          Mark_Start=false;
          data="";
          break;
        }
      }
      if(valid){
        if(PositionValid!="A"){
          Serial.println("Your position is not valid.");
        }
        Serial.print("Date:");
        Serial.println(Date);
        Serial.print("UTCtime:");
        Serial.print(RMCUTCtime);
        Serial.print("   ");
        Serial.println(GGAUTCtime);
        Serial.print("Latitude:");
        Serial.print(RMClatitude);
        Serial.print("   ");
        Serial.println(GGAlatitude);
        Serial.print("Longitude:");
        Serial.print(RMClongitude);
        Serial.print("   ");
        Serial.println(GGAlongitude);
        Serial.print("GPStatus:");
        Serial.println(GPStatus);
        Serial.print("SatelliteNum:");
        Serial.println(SatelliteNum);
        Serial.print("HDOPfactor:");
        Serial.println(HDOPfactor);
        Serial.print("Height:");
        Serial.println(Height);
        Serial.print("Speed:");
        Serial.println(Speed);
        Serial.print("Direction:");
        Serial.println(Direction);
        Serial.print("Declination:");
        Serial.println(Declination);
        Serial.print("Mode:");
        Serial.println(Mode);   
        valid=false;
        dataRead=true;
        break;
      }
      if(SerialGPS.find("$")){
        Mark_Start=true;
      }
    }
  }
  while(!dataRead);
#endif   

#if defined INCLUDE_WIFI && defined INCLUDE_GPS
// stop GPS serial if we also have WiFi, so they don't interfere
Serial.println("Stop GPS serial.");
SerialGPS.end();
#endif

// WiFi has to be initialized after GPS, since we cannot lose listen status on the WiFi Serial Port!                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
#ifdef INCLUDE_WIFI
  Serial.println("Begin WiFi setup");

  static ESP8266_HttpServerHandler myServerHandlers[] = {
    { PSTR("GET /command"), httpCommand },
    { PSTR("GET /gps"), httpGPS },
    { PSTR("GET "), http404 }
  };
  
  wifi.begin(9600); // Serial Port - WiFi module
  wifi.setupAsWifiStation(ESP8266_SSID, ESP8266_PASS, &Serial);
  wifi.startHttpServer(80, myServerHandlers, sizeof(myServerHandlers), 250, &Serial);
  Serial.println("WiFi setup finished!");
#endif

#ifdef INCLUDE_CONTROLLER
  // Setup motor pins
  pinMode(pinLB, OUTPUT); // Define 14 pin for the output (PWM)
  pinMode(pinLF, OUTPUT); // Define 15 pin for the output (PWM)
  pinMode(pinRB, OUTPUT); // Define 16 pin for the output (PWM) 
  pinMode(pinRF, OUTPUT); // Define 17 pin for the output (PWM)
  if (Usb.Init() == -1) {
    while (1); //halt
  }
#endif
}

void loop() 
{
#ifdef INCLUDE_WIFI
  wifi.serveHttpRequest();
#endif

#ifdef INCLUDE_CONTROLLER
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        currentDirection = STOP;

        if (Xbox.getButtonPress(UP, i)) {
          currentDirection = STRAIGHT;
        }
        if (Xbox.getButtonPress(DOWN, i)) {
          currentDirection = BACKWARDS;
        }
        if (Xbox.getButtonPress(LEFT, i) && currentDirection != BACKWARDS) {
          currentDirection = GOLEFT;
        }
        if (Xbox.getButtonPress(RIGHT, i) && currentDirection != BACKWARDS) {
          currentDirection = GORIGHT;
        }
        
        if (Xbox.getButtonClick(SYNC, i)) {
          Xbox.disconnect(i);
        }
      }
    }
  }
  else {
    Serial.println("No Xbox controller connected!");
  }

  move(currentDirection);
#endif
}
