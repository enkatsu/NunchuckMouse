#include <Wire.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;

byte accx, accy, accz, zbut, cbut, joyx, joyy;
int ledPin = 13;

void setup()
{
  Serial.begin(9600);
  nunchuck_init();

  Serial.print("WiiChuckDemo ready\n");
}

void loop() {
  if ( loop_cnt > 100 ) {
    loop_cnt = 0;

    nunchuck_get_data();

    joyx = nunchuck_joyx();
    joyy = nunchuck_joyy();
    accx  = nunchuck_accelx();
    accy  = nunchuck_accely();
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton();

    Serial.print("joyx: "); Serial.print((byte)joyx, DEC);
    Serial.print("\tjoyy: "); Serial.print((byte)joyy, DEC);
    Serial.print("\taccx: "); Serial.print((byte)accx, DEC);
    Serial.print("\taccy: "); Serial.print((byte)accy, DEC);
    Serial.print("\tzbut: "); Serial.print((byte)zbut, DEC);
    Serial.print("\tcbut: "); Serial.println((byte)cbut, DEC);
  }
  loop_cnt++;
  delay(1);
}
