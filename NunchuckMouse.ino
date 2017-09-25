#include <Wire.h>
#include <Mouse.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;
byte p_accx, p_accy, p_accz, p_zbut, p_cbut, p_joyx, p_joyy;
byte accx, accy, accz, zbut, cbut, joyx, joyy;
int ledPin = 13;

bool isMouseBegin = false;

void setup() {
  //  Serial.begin(9600);
  nunchuck_init();
  //  Serial.print("WiiChuckDemo ready\n");
}

void loop() {
  if ( loop_cnt > 100 ) {
    loop_cnt = 0;

    nunchuck_get_data();

    p_accx = accx;
    p_accy = accy;
    p_accz = accz;
    p_zbut = zbut;
    p_cbut = cbut;
    p_joyx = joyx;
    p_joyy = joyy;

    joyx = nunchuck_joyx();
    joyy = nunchuck_joyy();
    accx  = nunchuck_accelx();
    accy  = nunchuck_accely();
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton();

    if (isMouseBegin) {
      mouseAction();
    } else if (cbut == 1 && !isMouseBegin) {
      isMouseBegin = true;
      Mouse.begin();
    }

    //    Serial.print("joyx: "); Serial.print((byte)joyx, DEC);
    //    Serial.print("\tjoyy: "); Serial.print((byte)joyy, DEC);
    //    Serial.print("\taccx: "); Serial.print((byte)accx, DEC);
    //    Serial.print("\taccy: "); Serial.print((byte)accy, DEC);
    //    Serial.print("\tzbut: "); Serial.print((byte)zbut, DEC);
    //    Serial.print("\tcbut: "); Serial.println((byte)cbut, DEC);
  }
  loop_cnt++;
  delay(1);
}

void mouseAction() {
  if (isPressed(p_cbut, cbut)) {
    Mouse.press(MOUSE_LEFT);
  } else if (isReleased(p_cbut, cbut)) {
    Mouse.release(MOUSE_LEFT);
  }

  if (isPressed(p_zbut, zbut)) {
    Mouse.press(MOUSE_RIGHT);
  } else if (isReleased(p_zbut, zbut)) {
    Mouse.release(MOUSE_RIGHT);
  }

  int RANGE = 20;
  byte p_x = map(p_joyx, 30, 230, -RANGE, RANGE);
  byte p_y = map(p_joyy, 30, 230, RANGE, -RANGE);
  byte x = map(joyx, 30, 230, -RANGE, RANGE);
  byte y = map(joyy, 30, 230, RANGE, -RANGE);

  byte x_val = x;
  byte y_val = y;
  //  byte x_val = x * abs(x - p_x);
  //  byte y_val = y * abs(y - p_y);
  Mouse.move(x_val, y_val, 0);

}

bool isPressed(byte p, byte n) {
  return (p == 0 && n == 1);
}

bool isReleased(byte p, byte n) {
  return (p == 1 && n == 0);
}


