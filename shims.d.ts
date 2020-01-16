// Auto-generated. Do not edit.



    //% color=#5b78fa weight=10 
    //% icon="\uf1eb"
declare namespace MiBit_IR {

    /**
     * set button pressed event handler.
     */
    //% blockId=mibit_ir_button_pressed_event
    //% block="on button |%btn| pressed" shim=MiBit_IR::onPressEvent
    function onPressEvent(btn: RemoteButton, body: () => void): void;
    /**
     * initialises local variablesssss
     */
    //% blockId=ir_initIR
    //% block="connect ir receiver to %pin" shim=MiBit_IR::initIR
    function initIR(pin: Pins): void;
}

// Auto-generated. Do not edit. Really.
