//************************************************************
// this is a simple example that uses the painlessMesh library and echos any
// messages it receives
//
//************************************************************
#include "painlessMesh.h"
#include <U8g2lib.h>

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

// Prototypes
void receivedCallback( uint32_t from, String &msg );

painlessMesh  mesh;

void setup() {
  Serial.begin(115200);
  //u8g2.begin();
    
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT );
  mesh.onReceive(&receivedCallback);
}

void loop() {
  mesh.update();
  //u8g2.setFont(u8g2_font_4x6_tr);
  //u8g2.drawStr(1,20,"Mode: ");
  //delay(100);
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("echoNode: Received from %u msg=%s\n", from, msg.c_str());
  mesh.sendSingle(from, msg);
}