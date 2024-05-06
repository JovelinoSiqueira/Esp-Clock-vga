// REQUIRES the following Arduino libraries:
// - ESP32Time Library: https://github.com/fbiego/ESP32Time
// - VGA Library: https://github.com/bitluni/ESP32Lib
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// - Getting Started ESP32 / ESP32S : https://www.youtube.com/watch?v=9b0Txt-yF7E
// Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESP32Lib.h>
#include <ESP32Time.h>
//#include "DHT.h"
#include <Ressources/Font6x8.h>
#include <Ressources/CodePage437_8x8.h>
#include <Ressources/CodePage437_9x16.h>
#include "index.h"  //Web page header file
#define DHTPIN 15   
#define DHTTYPE DHT11   // DHT 11

//pin configuration
const int redPin = 27;
const int greenPin = 26;
const int bluePin = 25;
const int vsyncPin = 32;
const int hsyncPin = 33;

VGA3BitI vga;
ESP32Time rtc;
WebServer server(80);
//DHT dht(DHTPIN, DHTTYPE);
char ssid[30] = "";
char pass[30] = "";

uint32_t lastTime = 0, prevTime = 0, prevTim = 0; 
uint32_t lastdot = 0, lastblack = 0, lastdata = 0; 
uint16_t txt_length, txte_length, text_length;
bool flasher = false;
int sp0 = 120;
float Tem, Hum;
int16_t  Tz = 1; // Time Zone
int s, m, h, d, month, yr;
String text, text0, text1;
char crap[80];
unsigned int NewRTCm = 60;
int yx = 100;
int yy = yx+44;
String Message = "Great Projects wish you a very nice day.";
int r, b, g;
int ac, bc, cc;
int displa;
int xpos=36, xps=43, xpso=43;
// standard colors
uint16_t myRED = vga.RGB(255,0,0);
uint16_t myGREEN = vga.RGB(0,255,0);
uint16_t myBLUE = vga.RGB(0,0,255);
uint16_t myWHITE = vga.RGB(255, 255,255);
uint16_t myYELLOW = vga.RGB(255,255,0);
uint16_t myCYAN = vga.RGB(0,255,255);
uint16_t myMAGENTA = vga.RGB(255,0,255);
uint16_t myBLACK = vga.RGB(0,0,0);
uint16_t myCOLORS[7] = {myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myRED, myGREEN};

void(* resetFunc) (void) = 0;//declare reset function at address 0

void getWifi()
{  
  if (WiFi.status() == WL_CONNECTED) { 
    WiFi.disconnect();
    }
  WiFi.begin(ssid, pass);
  int xc = 0;
  while (WiFi.status() != WL_CONNECTED && xc < 10) {
    delay(1000);
    xc++;
  }
    Message = "IP Address: http://";
    Message += WiFi.localIP().toString().c_str();
}
void gettime()
{
  configTime(Tz * 3600, 0, "pool.ntp.org", "time.nist.gov");
}
void afficher(char segm, int xx)
{
     bc++;
  if (bc > 6) { bc = 0; }
    switch(segm)
    {
    case 0 :
        vga.fillEllipse(xx+30, yx, 30, 4, myCOLORS[bc]);
        vga.ellipse(xx+30, yx, 30, 4, myCOLORS[ac]);
        break;
    case 1 :
        vga.fillEllipse(xx+62, yx+22, 6, 20, myCOLORS[bc]);
        vga.ellipse(xx+62, yx+22, 6, 20, myCOLORS[ac]);
        break;
    case 2 :
        vga.fillEllipse(xx+62, yx+66, 6, 20, myCOLORS[bc]);
        vga.ellipse(xx+62, yx+66, 6, 20, myCOLORS[ac]);
        break;
    case 3 :
        vga.fillEllipse(xx+30, yx+88, 30, 4, myCOLORS[bc]);
        vga.ellipse(xx+30, yx+88, 30, 4, myCOLORS[ac]);
        break;
    case 4 :
        vga.fillEllipse(xx, yx+66, 6, 20, myCOLORS[bc]);
        vga.ellipse(xx, yx+66, 6, 20, myCOLORS[ac]);
        break;
    case 5 :
        vga.fillEllipse(xx, yx+22, 6, 20, myCOLORS[bc]);
        vga.ellipse(xx, yx+22, 6, 20, myCOLORS[ac]);
        break;
    case 6 :
        vga.fillEllipse(xx+30, yx+44, 30, 4, myCOLORS[bc]);
        vga.ellipse(xx+30, yx+44, 30, 4, myCOLORS[ac]);
        break;
    }
}
void affichersecond(char segment, int xx)
{
     ac++;
  if (ac > 6) { ac = 0; }
    switch(segment)
    {
    case 0 :
        vga.fillEllipse(xx+20, yy, 20, 3, myCOLORS[ac]);
        vga.ellipse(xx+20, yy, 20, 3, vga.RGB(255, 0, 0));
        break;
    case 1 :
        vga.fillEllipse(xx+42, yy+12, 5, 10, myCOLORS[ac]);
        vga.ellipse(xx+42, yy+12, 5, 10, vga.RGB(255, 0, 0));
        break;
    case 2 :
        vga.fillEllipse(xx+42, yy+34, 5, 10, myCOLORS[ac]);
        vga.ellipse(xx+42, yy+34, 5, 10, vga.RGB(255, 0, 0));
        break;
    case 3 :
        vga.fillEllipse(xx+20, yy+46, 20, 3, myCOLORS[ac]);
        vga.ellipse(xx+20, yy+46, 20, 3, vga.RGB(255, 0, 0));
        break;
    case 4 :
        vga.fillEllipse(xx, yy+34, 5, 10, myCOLORS[ac]);
        vga.ellipse(xx, yy+34, 5, 10, vga.RGB(255, 0, 0));
        break;
    case 5 :
        vga.fillEllipse(xx, yy+12, 5, 10, myCOLORS[ac]);
        vga.ellipse(xx, yy+12, 5, 10, vga.RGB(255, 0, 0));
        break;
    case 6 :
        vga.fillEllipse(xx+20, yy+24, 20, 3, myCOLORS[ac]);
        vga.ellipse(xx+20, yy+24, 20, 3, vga.RGB(255, 0, 0));
        break;
    }
}
void DisplayNumber(int x, int z) {
int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6;
  if(x != 1 && x != 4) {
  afficher(a,z);
    }
  if(x != 5 && x != 6) {
  afficher(b,z);
    }
  if(x != 2) {
  afficher(c,z);
    }
  if(x != 1 && x != 4 && x != 7) {
  afficher(d,z);
    }
  if(x == 0 || x == 2 || x == 6 || x == 8) {
  afficher(e,z);
    }
  if(x != 1 && x != 2 && x != 3 && x != 7) {
  afficher(f,z);
    }
  if(x != 0 && x != 1 && x != 7) {
  afficher(g,z);
    }
}
void Displaysecond(int x, int z) {
int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6;
  if(x != 1 && x != 4) {
  affichersecond(a,z);
    }
  if(x != 5 && x != 6) {
  affichersecond(b,z);
    }
  if(x != 2) {
  affichersecond(c,z);
    }
  if(x != 1 && x != 4 && x != 7) {
  affichersecond(d,z);
    }
  if(x == 0 || x == 2 || x == 6 || x == 8) {
  affichersecond(e,z);
    }
  if(x != 1 && x != 2 && x != 3 && x != 7) {
  affichersecond(f,z);
    }
  if(x != 0 && x != 1 && x != 7) {
  affichersecond(g,z);
    }
}
void getSyTemp()
{
  int xs=500, ys=40;
  vga.fillRect(xs+10, ys, 100, 115, myBLACK);
  for(int x=ys; x<ys+51; x+=2) {
  vga.fillRect(xs+34, x, 3, 1, vga.RGB(0xff00ff));
  }
 vga.setTextColor(vga.RGB(0xffff00));
  vga.setFont(Font6x8);
  for(int x=ys; x<ys+51; x+=10) {
  vga.fillRect(xs+34, x, 6, 1, vga.RGB(0xff00ff));
  vga.setCursor(xs+45, x-3);
  vga.print(ys+50-x);
  }
  vga.circle(xs+25, ys, 8, vga.RGB(0xff00ff));
  vga.circle(xs+25, ys, 7, vga.RGB(0xff00ff));
  vga.circle(xs+25, ys, 6, vga.RGB(0xffffff));
  vga.circle(xs+25, ys, 5, vga.RGB(0xffffff));
  vga.fillCircle(xs+25, ys+76, 20, vga.RGB(0xff00ff));
  vga.fillCircle(xs+25, ys+76, 18, vga.RGB(0xffffff));
  vga.fillCircle(xs+25, ys+76, 16, vga.RGB(0x00ff00));
  vga.fillCircle(xs+25, ys+76, 12, vga.RGB(0x0000ff));
  vga.fillRect(xs+17, ys, 2, 58, vga.RGB(0xff00ff));
  vga.fillRect(xs+19, ys, 2, 60, vga.RGB(0xffffff));
  vga.fillRect(xs+30, ys, 2, 60, vga.RGB(0xffffff));
  vga.fillRect(xs+32, ys, 2, 58, vga.RGB(0xff00ff));
  int tec = map(Tem, 0, 50, ys+50, ys);
  vga.fillRect(xs+21, ys, 9, 66, myBLACK);
  vga.fillRect(xs+21, tec, 9, ys+70-tec, vga.RGB(0x0000ff));
}
void getTemp()
{
   //    Tem = dht.readTemperature();
   //    Hum = dht.readHumidity();
  if (isnan(Tem) || isnan(Hum)) {
    delay(200);
    return;
  }
  getSyTemp();
        text1 = "Humidity: ";
        text1 += Hum;
        text1 += " %         Temperature: ";
        text1 += Tem;
        text1 += " ";
        text1 += (char)248;
        text1 += "C";
  vga.setFont(CodePage437_9x16);
      vga.fillRect(0, 25, 500, 70, myBLACK);
  vga.setCursor(58, 80);
  for (int z = 0; z < 50; z++) {
  vga.setTextColor(myCOLORS[cc]);
  vga.print(text1[z]);
     cc++;
  if (cc > 6) { cc = 0; }
  }
        yy = 30;
  int Valh = Hum;
  int dig1 = Valh / 10;
  int dig2 = Valh - (dig1 * 10);
   Displaysecond(dig1,60);
   Displaysecond(dig2,140);
  int Valt = Tem*10;
      dig1 = Valt / 100;
      Valt = Valt - (dig1*100);
      dig2 = Valt / 10;
  int dig3 = Valt - (dig2 * 10);
   Displaysecond(dig1,280);
   Displaysecond(dig2,360);
   Displaysecond(dig3,440);
   vga.fillEllipse(420, 75, 3, 3, myCOLORS[ac]);
        yy = yx+44;
  }
void getdaTe()
{
    switch (displa)
    {
      case 0: // full time date am pm
        text0 = rtc.getTime("%r  %A  %d - %B - %Y");
        displa = 1;
        break;
      case 1: // display message
        text0 = Message;
        displa = 0;
        break;
      default: // full time date
        text0 = rtc.getTimeDate(true);
        displa = 1;
        break;
    }
}
void getTim()
{
    if (NewRTCm != rtc.getMinute())
      {
      vga.fillRect(0, yx-5, 450, 100, vga.RGB(0, 0, 0));
  int Valh = rtc.getHour(true);
  int dig1 = Valh / 10;
  int dig2 = Valh - (dig1 * 10);
  int Valm = rtc.getMinute();
  int dig3 = Valm / 10;
  int dig4 = Valm - (dig3 * 10);
        DisplayNumber(dig1,20);
        DisplayNumber(dig2,120);
        DisplayNumber(dig3,260);
        DisplayNumber(dig4,360);
  getTemp();
  getdaTe();
  NewRTCm = Valm;
      }
  int Vals = rtc.getSecond();
  int dig5 = Vals / 10;
  int dig6 = Vals - (dig5 * 10);
      vga.fillRect(450, yy-5, 150, 60, myBLACK);
        Displaysecond(dig5,460);
        Displaysecond(dig6,540);
   if (!flasher) {
        vga.fillEllipse(220, yx+30, 5, 5, myCOLORS[ac]);
        vga.fillEllipse(220, yx+60, 5, 5, myCOLORS[bc]);
   } else {
        vga.fillEllipse(220, yx+30, 5, 5, myBLACK);
        vga.fillEllipse(220, yx+60, 5, 5, myBLACK);
   }
}
void scroll_txt(String txt) {
  txt_length = txt.length();
  vga.setFont(CodePage437_9x16);
  vga.setCursor(0, 2);
  vga.fillRect(0, 2, 600, 15, myBLACK);
  for (int x = 0; x < 66; x++) {
  vga.setTextColor(myCOLORS[ac]);
  vga.print(txt[x-xpos]);
     ac++;
  if (ac > 6) { ac = 0; }
  }
     xpos--;
     if (xpos < -txt_length) { xpos = 66, getdaTe();}
  }
  void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
void handleSpe0() { 
    handleRoot();
    sp0 = 10*server.arg("Speed0").toInt();
  }
void handleMesg() { 
    handleRoot();
    Message = server.arg("Message");
  }
void handleRestTime() {  
    handleRoot();
    Tz = server.arg("restmie").toInt(); 
    gettime();
    getdaTe();
}
void handleResTime() {  
    handleRoot();
    String hbuf = server.arg("htmie"); 
    String dbuf = server.arg("bday"); 
    text = hbuf[0];
    text += hbuf[1];
    h = text.toInt(); 
    text = hbuf[3];
    text += hbuf[4];
    m = text.toInt(); 
    text = hbuf[6];
    text += hbuf[7];
    s = text.toInt();
    text = dbuf[0];
    text += dbuf[1];
    text += dbuf[2];
    text += dbuf[3];
    yr = text.toInt(); 
    text = dbuf[5];
    text += dbuf[6];
    month = text.toInt();
    text = dbuf[8];
    text += dbuf[9];
    d = text.toInt();
  rtc.setTime(s, m, h, d, month, yr); 
  getdaTe();
}
void handleWifi() { 
  text = server.arg("usname");
  int len = text.length() + 1; 
  text.toCharArray(ssid, len);
  text = server.arg("pssw");
  len = text.length() + 1;
  text.toCharArray(pass, len); 
    handleRoot();
    delay(1000);  
    getWifi(); 
}
void handlestate() {
  String content = "<?xml version = \"1.0\" ?>";
  content += "<inputs><analog>";
  content += Tem;
  content += "</analog><analog>";
  content += Hum;
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}
void handleRestesp() {  
    handleRoot();
    delay(4000);     
    resetFunc();
}
void setup() {
  Serial.begin(115200);
  //dht.begin();
  rtc.setTime(30, 0, 1, 29, 4, 2021);  // 01:00:30 29th Avril 
  WiFi.softAP("VGA_AP");
  Serial.println("IP Address: http://192.168.4.1");
  delay(2000);
  Mode myMode = vga.MODE640x480.custom(600, 200);
  vga.init(myMode, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  getTemp();
  server.on("/", handleRoot); 
  server.on("/MesSpeed0", handleSpe0); 
  server.on("/readtemhu", handlestate); 
  server.on("/Mywifi", handleWifi); 
  server.on("/myMesg", handleMesg); 
  server.on("/resttime", handleRestTime);   
  server.on("/restime", handleResTime); 
  server.on("/restesp", handleRestesp);
  server.begin();
}
void loop() {
  server.handleClient();
  if(millis() - lastTime >= 1000) {
      getTim();
      flasher = !flasher;
      lastTime = millis();
    }
    if (millis() - prevTime >= sp0) {
     scroll_txt(text0); 
    prevTime = millis();
  }
}
