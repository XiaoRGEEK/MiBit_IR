#include <map>
#include <vector>
#include "pxt.h"
#include "ReceiverIR.h"

using namespace pxt;
typedef vector<Action> vA;

enum class Pins{
  P0 = 3,
  P1 = 2,
  P2 = 1,
  P3 = 4,
  P4 = 5,
  P5 = 17,
  P6 = 12,
  P7 = 11,
  P8 = 18,
  P9 = 10,
  P10 = 6,
  P11 = 26,
  P12 = 20,
  P13 = 23,
  P14 = 22,
  P15 = 21,
  P16 = 16,
  P19 = 0,
  P20 = 30,
};

enum class RemoteButton
{
  //% block=Power
  Power = 0x45,
  //% block=Menu
  Menu = 0x47,
  //% block=Test
  Test = 0x44,
  //% block=Plus  
  Plus = 0x40,
  //% block=Return
  Return = 0x43,
  //% block=Left
  Left = 0x07,
  //% block=Play
  Play = 0x15,
  //% block=Right
  Right = 0x09,
  //% block=Num0
  Num0 = 0x16,
  //% block=Minus
  Minus = 0x19,
  //% block=Cancle
  Cancle = 0x0D,
  //% block=Num1
  Num1 = 0x0C,
  //% block=Num2
  Num2 = 0x18,
  //% block=Num3
  Num3 = 0x5E,
  //% block=Num4
  Num4 = 0x08,
  //% block=Num5
  Num5 = 0x1C,
  //% block=Num6
  Num6 = 0x5A,
  //% block=Num7
  Num7 = 0x42,
  //% block=Num8
  Num8 = 0x52,
  //% block=Num9
  Num9 = 0x4A,
};

//% color=#5b78fa weight=10 
//% icon="\uf1eb"
namespace Explorer_IR { 
  map<RemoteButton, vA> actions;
  map<RemoteButton, uint32_t> lastact;
  Timer tsb; 
  uint8_t buf[32];
  uint32_t now;
  ReceiverIR *rx;
  RemoteIR::Format fmt = RemoteIR::UNKNOWN;
  int msg;
  int IRcallbackNum;

  void cA(vA runner) {
      for(int i = 0; i < runner.size(); i++) { 
          runAction0(runner[i]);
      } 
  }

  void onReceivable() {
    int x = rx->getData(&fmt, buf, 32 * 8);
    if(actions.find((RemoteButton)buf[2]) == actions.end()) 
        return;
    now = tsb.read_ms();
    if(now - lastact[(RemoteButton)buf[2]] < 100) return;
    lastact[(RemoteButton)buf[2]] = now;
    msg=(int)buf[2];
    cA(actions[(RemoteButton)msg]);  
  }

  void monitorIR(){
    while(1){
      while(rx->getState() != ReceiverIR::Received){ 
        uBit.sleep(50);
      }
      onReceivable();
    }
  }

  void initIR(Pins pin){
    rx = new ReceiverIR((PinName)pin);
    tsb.start(); //interrupt timer for debounce
    create_fiber(monitorIR);
  }  

  /**
  * set button pressed event handler.
  */
  //% blockId=explorer_ir_button_pressed_event
  //% block="on button |%btn| pressed"
  void onPressEvent(RemoteButton btn, Action body) {
    static bool inited = false;
    if (!inited) {
      initIR(Pins::P2);
      inited = true;
    }

    if(actions.find(btn) == actions.end()) {
        vector<Action> act;
        actions[btn] = act;
    } 
    actions[btn].push_back(body);
  }
}