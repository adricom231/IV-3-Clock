#include <WiFi.h>
#include "time.h"
#include "sntp.h"

String hour = "";
String minute = "";
String sec = "";
String combined = "";
String mon = "";
String day = "";
String year = "";
String date_s = "";

int state;
int booted;
int next_state;

int current_time = 0;
int current_date = 0;
int set_time = 0;
int set_date = 0;

const char* ssid       = "your ssid";
const char* password   = "your password";

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;

const char* time_zone = "your time zone";


int latchPin_enable = 7;
int clockPin_enable = 8;
int dataPin_enable = 9;

int latchPin_vfd = 2;
int clockPin_vfd = 1;
int dataPin_vfd = 44;

int SW1 = 4;
int SW2 = 43;
int SW3 = 6;


bool first_boot;
//1- right bottom
//2- przecinek
//- 3right top
//4- top
//5- middle
//6- left top
//7- left bottom
//8- bottom
byte data =B11111111;
byte data_z = B00000000;
byte data_0 =B10110111; 
byte data_9 =B10111101; 
byte data_8 =B10111111;
byte data_7 =B10110000;
byte data_6 =B10011111;
byte data_5 =B10011101;
byte data_4 =B10101100;
byte data_3 =B10111001;
byte data_2 =B00111011;
byte data_1 =B10100000;
byte data_midle =B00001000;

void timeavailable(struct timeval *t)
{

}

void updateTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    delay(50);
    return;
  }
  hour = String(timeinfo.tm_hour);

  if(timeinfo.tm_min < 10){
    minute = ("0" + String(timeinfo.tm_min));
  }
  else {
    minute = String(timeinfo.tm_min);
  }

  if(timeinfo.tm_sec < 10){
    sec = ("0" + String(timeinfo.tm_sec));
  }
  else {
    sec = String(timeinfo.tm_sec);
  }

  combined = hour + minute + sec;
  current_time = combined.toInt();
  
  day = String(timeinfo.tm_mday);
  if((timeinfo.tm_mon + 1) < 10){
    mon = ("0" + String(timeinfo.tm_mon + 1));
  }
  else{
    mon = String(timeinfo.tm_mon + 1);
  }
  year = String(timeinfo.tm_year - 100);

  date_s = day + mon + year;
  current_date = date_s.toInt();
}

void enable_all(){
    digitalWrite(latchPin_enable, LOW);
    shiftOut(dataPin_enable, clockPin_enable, MSBFIRST, data);
    digitalWrite(latchPin_enable, HIGH);
}




  


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(latchPin_vfd, OUTPUT);
  pinMode(clockPin_vfd, OUTPUT);
  pinMode(dataPin_vfd, OUTPUT);
  pinMode(latchPin_enable, OUTPUT);
  pinMode(clockPin_enable, OUTPUT);
  pinMode(dataPin_enable, OUTPUT);
  pinMode(SW1 , INPUT);
  pinMode(SW2 , INPUT);
  pinMode(SW3 , INPUT);
  display_start(1);

  sntp_set_time_sync_notification_cb( timeavailable );
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  configTzTime(time_zone, ntpServer1, ntpServer2);
  WiFi.begin(ssid, password);
  display_start(2);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  display_start(3);
  state = 1;
  booted = 1;
  delay(200);

}

void loop() {
  int Bt1 = 0;
  Bt1 = digitalRead(SW1);

  if(Bt1 == HIGH) {
    if(state == 2){
      state = 0;
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if(state == 10){
      state = 1;
      booted = 2;
      set_time = 0;
      delay(1000);
    }
  } 
  int Bt2 = 0;
  Bt2 = digitalRead(SW2);
  if(Bt2 == HIGH) {
    if(state == 2){
      set_date = 0;
      state = 3;
      delay(1000);
    }
    else{
    if(state == 3){
      state = 2;
      set_time = 0;
      delay(1000);
    }}
    
  } 

    int Bt3 = 0;
    Bt3 = digitalRead(SW3);
    if(Bt3 == HIGH) {
      if(state == 2){
        set_date = 0;
        state = 4;
        delay(1000);
      }
      else{
      if(state == 4){
        state = 2;
        set_time = 0;
       delay(1000);
    }}
  } 


  if(state == 0){
    turn_off();
  }
  
  if(state == 1){
    first_b(booted);
  }

  if(state == 2){
    display_time();
  }

  if(state == 3){
    display_date();
  }

  if(state == 4){
    display_full();
  }

  
}



byte To7Segment(int input){
  byte output = B00000000;
  switch(input){
    case 0:
      output = B10110111;
      break;
    case 1:
      output = B10100000;
      break;
    case 2:
      output = B00111011;
      break;
    case 3:
      output = B10111001;
      break;
    case 4:
      output = B10101100;
      break;
    case 5:
      output = B10011101;
      break;
    case 6:
      output = B10011111;
      break;
    case 7:
      output = B10110000;
      break;
    case 8:
      output = B10111111;
      break;
    case 9:
      output = B10111101;
      break;
  }
 
  return output;
}

void display_start(int input){
  if(input == 1){
    enable_all();
    digitalWrite(latchPin_vfd, LOW);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_z);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_z);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_z);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_z);
    digitalWrite(latchPin_vfd, HIGH);
  }

  if(input == 2){
    enable_all();
    digitalWrite(latchPin_vfd, LOW);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_z);
    for(int i = 0; i < 4 ; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);
    }
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_z);
    digitalWrite(latchPin_vfd, HIGH);
  }

  if(input == 3){
    enable_all();
    digitalWrite(latchPin_vfd, LOW);
    for(int i = 0; i < 6 ; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);

    }
    digitalWrite(latchPin_vfd, HIGH);
  }
}

void turn_off(){
  byte data_t1 = B01011100;
  byte data_t2 = B00011000;
  byte data_t3 = B00000000;
  digitalWrite(latchPin_enable, LOW);
  shiftOut(dataPin_enable, clockPin_enable, LSBFIRST, data_t1);
  digitalWrite(latchPin_enable, HIGH);
  delay(100);
  digitalWrite(latchPin_enable, LOW);
  shiftOut(dataPin_enable, clockPin_enable, LSBFIRST, data_t2);
  digitalWrite(latchPin_enable, HIGH);
  delay(100);
  digitalWrite(latchPin_enable, LOW);
  shiftOut(dataPin_enable, clockPin_enable, LSBFIRST, data_t3);
  digitalWrite(latchPin_enable, HIGH);
  delay(100);
  digitalWrite(latchPin_vfd, LOW);
  for(int i = 0; i < 6; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, B00000000);
  }
  digitalWrite(latchPin_vfd, HIGH);
  state = 10;
}

void first_b(int sel){
  byte data_t1 = B01011100;
  byte data_t2 = B00011000;
  byte data_t3 = B00000000;
  updateTime();
  enable_all();
  if(current_time != set_time){
    set_time = current_time;
    int output[6] = {0};
    int convert = set_time;
    int index = 0;

    for(int c = 0; c < 6 ; c++){
      int d = convert / 10;
      output[index] = To7Segment(convert - d * 10);
      convert = d;
      index++;
    }
    digitalWrite(latchPin_vfd, LOW);
    if(sel == 2){
        digitalWrite(latchPin_enable, LOW);
        shiftOut(dataPin_enable, clockPin_enable, LSBFIRST, data_t3);
        digitalWrite(latchPin_enable, HIGH);
    }
    for(int i = 0; i< 2; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);
    }
    for(int i = 2; i < 4; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, output[i]);
    }
    for(int i = 0; i< 2; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);
    }
    digitalWrite(latchPin_vfd, HIGH);
    delay(100);

    if(sel == 2){
        digitalWrite(latchPin_enable, LOW);
        shiftOut(dataPin_enable, clockPin_enable, LSBFIRST, data_t2);
        digitalWrite(latchPin_enable, HIGH);
    }
    digitalWrite(latchPin_vfd, LOW);
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);
    for(int i = 1; i < 5; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, output[i]);
    }
    shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data_midle);
    digitalWrite(latchPin_vfd, HIGH);
    delay(100);

    if(sel == 2){
        digitalWrite(latchPin_enable, LOW);
        shiftOut(dataPin_enable, clockPin_enable, LSBFIRST, data_t1);
        digitalWrite(latchPin_enable, HIGH);
    }
    digitalWrite(latchPin_vfd, LOW);
    for(int i = 0; i < 6; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, output[i]);
    }
    digitalWrite(latchPin_vfd, HIGH);
    delay(100);
    state = 2;
  }
}
void display_full(){
    digitalWrite(latchPin_enable, LOW);
    shiftOut(dataPin_enable, clockPin_enable, MSBFIRST, data);
    digitalWrite(latchPin_enable, HIGH);
    
    digitalWrite(latchPin_vfd, LOW);
    for(int i = 0; i < 6; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, data);
    }
    digitalWrite(latchPin_vfd, HIGH);
}



void display_time(){
  updateTime();
  if(current_time != set_time){
    set_time = current_time;
    int output[6] = {0};
    int convert = set_time;
    int index = 0;

    for(int c = 0; c < 6 ; c++){
      int d = convert / 10;
      output[index] = To7Segment(convert - d * 10);
      convert = d;
      index++;
      
    }

    digitalWrite(latchPin_vfd, LOW);
    for(int i = 0; i < 6; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, output[i]);
    }
    digitalWrite(latchPin_vfd, HIGH);

    digitalWrite(latchPin_enable, LOW);
    shiftOut(dataPin_enable, clockPin_enable, MSBFIRST, data);
    digitalWrite(latchPin_enable, HIGH);
  }
}

void display_date(){
  updateTime();
    if(current_date != set_date){
    set_date = current_date;
    int output[6] = {0};
    int convert = set_date;
    int index = 0;

    for(int c = 0; c < 6 ; c++){
      int d = convert / 10;
      output[index] = To7Segment(convert - d * 10);
      convert = d;
      index++;
      
    }

    digitalWrite(latchPin_vfd, LOW);
    for(int i = 0; i < 6; i++){
      shiftOut(dataPin_vfd, clockPin_vfd, MSBFIRST, output[i]);
    }
    digitalWrite(latchPin_vfd, HIGH);

    digitalWrite(latchPin_enable, LOW);
    shiftOut(dataPin_enable, clockPin_enable, MSBFIRST, data);
    digitalWrite(latchPin_enable, HIGH);
  }
}