#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  //M0/ESP32/ESP8266/mega2560/Uno/Leonardo
// Set the LCD address to 0x27 for a 16 chars and 2 line display

const char * ssid = "aliersej";
const char * password = "ganggang";

int x = 32;
int y = 33;
int sw = 17;
bool a = true;
bool p = true;
int b = 18;

AsyncUDP udp;

void setup() {
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);

  Serial.begin(9600);

  u8g2.begin();    //init
  u8g2.enableUTF8Print();        // Enable UTF8 support for Arduino print（）function.
 

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }
  if (udp.listen(4000)) {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast()
                       ? "Broadcast"
                       : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();

      // reply to the client/sender
      packet.printf("Got %u bytes of data", packet.length());
    });
  }

  // Send unicast
  // udp.print("Hello Server!");
  // udp.
}

void sendMessage(String msg){
  udp.writeTo((const uint8_t *)msg.c_str(), msg.length(),
              IPAddress(192, 168, 43, 254), 6000);
}

void writeOnScreen(String write){


}

void loop() {
  //delay(500);
  int joyX = analogRead(x);
  int joyY = analogRead(y);
  int SW = digitalRead(sw);
  int B = digitalRead(b);
  u8g2.setCursor(/* x=*/0, /* y=*/30);    //Define the cursor of print function, any output of the print function will start at this position.

do
{
if(B == 0){
  //sendMessage("land");
  //sendMessage("takeoff");
  //Serial.println("button pressed");
  sendMessage("w");
   u8g2.print("Create Button");
}

  if(joyX>1700 && joyX<1800){
    joyX=1750;
  }
  if(joyY>1790 && joyY<1900){
    joyY =1850;
  }

  if(SW==0){
    sendMessage("nothing");
    u8g2.print("Nothing");
  }


if(joyY > 3000){
  sendMessage("up");
   u8g2.print("Up");
}

if(joyY < 1000){
  //sendMessage("down " + String(20));
  sendMessage("down");
   u8g2.print("Down");
}

if(joyX > 3000){
  sendMessage("right");
   u8g2.print("Right");
}

if(joyX < 1000){
  sendMessage("left");
   u8g2.print("Left");
}

 
  Serial.print("x: ");
   Serial.println(joyX);
  Serial.print("y: ");
  Serial.println(joyY);
  Serial.println();
  Serial.println("Switch");
  Serial.println(SW);
  //delay(400);
  
  /* code */
} while (u8g2.nextPage());

  u8g2.setFont(u8g2_font_logisoso34_tf);
  u8g2.setFontDirection(0);  
  u8g2.firstPage();

}