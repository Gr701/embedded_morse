#ifndef SRC_BUTTONMANAGER_H_
#define SRC_BUTTONMANAGER_H_


#include <xdc/runtime/System.h>
#include <ti/drivers/PIN.h>
#include "Board.h"

#include "globals.h"
#include "outputManager.h"

static PIN_Handle listenButtonHandle;
static PIN_State listenButtonState;
static PIN_Config listenButtonConfig[] = {
    Board_BUTTON0 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};

static PIN_Handle sendButtonHandle;
static PIN_State sendButtonState;
static PIN_Config sendButtonConfig[] = {
    Board_BUTTON1 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};

void buttonFx();

void registerButton();

#endif /* SRC_BUTTONMANAGER_H_ */
