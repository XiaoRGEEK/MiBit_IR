// Auto-generated. Do not edit.



    //% color=#31C7D5 weight=10 
    //% icon="\uf1eb"
declare namespace Explorer_IR {

    /**
     * set button pressed event handler.
     */
    //% blockId=explorer_ir_button_pressed_event
    //% block="on button |%btn| pressed" shim=Explorer_IR::onPressEvent
    function onPressEvent(btn: RemoteButton, body: () => void): void;
    /**
     * initialises local variablesssss
     */
    //% blockId=ir_init
    //% block="connect ir receiver to %pin" shim=Explorer_IR::initIR
    function initIR(pin: Pins): void;

}

// Auto-generated. Do not edit. Really.
