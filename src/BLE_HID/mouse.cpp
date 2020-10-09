#include "mouse.h"

uint8_t report[] = { 0, 0, 0, 0 };

BLEMouse::BLEMouse(BLE &ble) : HIDServiceBase(ble,
                       MOUSE_REPORT_MAP, 
                       sizeof(MOUSE_REPORT_MAP),
                       report,
                       NULL,
                       NULL,
                       sizeof(inputReport)),
_button(0)
{
}

void BLEMouse::click(uint8_t b) {
  this->press(b);
  this->release(b);
}

//void BLEMouse::move(signed char x, signed char y, signed char wheel) {
//void BLEMouse::move(uint16_t x, uint16_t y, signed char wheel) {
void BLEMouse::move(int x, int y, signed char wheel) {
  unsigned char mouseMove[5]= { 0x00, 0x00, 0x00, 0x00, 0x00 };

  // send key code
  //mouseMove[0] = this->_button;
  //mouseMove[1] = x;
  //mouseMove[2] = y;
  //mouseMove[3] = wheel;
  //uint16_t _x = (uint16_t) ((32767l * ((uint32_t) x)) / 1053); // if 10000l limit = 5000
  //uint16_t _y = (uint16_t) ((32767l * ((uint32_t) y)) / 658);
  int _x = (int) ((32767l * ((long) x)) / 1080); // if 10000l limit = 5000
  int _y = (int) ((32767l * ((long) y)) / 810);
  //int _x = x;
  //int _y = y;

  mouseMove[0] = this->_button;
  mouseMove[1] = _x & 0xFF;
  mouseMove[2] = (_x >> 8) & 0xFF;
  mouseMove[4] = _y & 0xFF;
  mouseMove[4] = (_y >> 8) & 0xFF;

  this->send(mouseMove);
}

void BLEMouse::press(uint8_t b) {
  this->_button |= b;

  this->move(0, 0, 0);
}

void BLEMouse::release(uint8_t b) {
  this->_button &= ~b;

  this->move(0, 0, 0);
}

bool BLEMouse::isPressed(uint8_t b) {
 return ((this->_button & b) != 0);
}

