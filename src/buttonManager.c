//Worked together in a session Mark, Timo and Anatolii on designing, testing and implementing

#include "buttonManager.h"

void buttonFxn(PIN_Handle handle, PIN_Id pinId) {
    System_printf("button %d pressed\n", pinId);
    if (pinId == 0 && programState == SENDING) {
        programState = LISTENING;
        didStateChange = true;
        System_printf("LISTENING mode is on\n");
    } else if (pinId == 4 && programState == LISTENING) {
        programState = SENDING;
        didStateChange = true;
        System_printf("SENDING mode is on\n");
    }
    System_flush();
}

void registerButton() {
    listenButtonHandle = PIN_open(&listenButtonState, listenButtonConfig);
    if (listenButtonHandle == NULL) {
        System_abort("Error initializing listen button\n");
    }
    if (PIN_registerIntCb(listenButtonHandle, &buttonFxn) != 0) {
        System_abort("Error registering button callback function");
    }

    sendButtonHandle = PIN_open(&sendButtonState, sendButtonConfig);
    if (sendButtonHandle == NULL) {
        System_abort("Error initializing send button\n");
    }
    if (PIN_registerIntCb(sendButtonHandle, &buttonFxn) != 0) {
        System_abort("Error registering button callback function");
    }

    System_printf("buttons are registered\n");
    System_flush();
}
