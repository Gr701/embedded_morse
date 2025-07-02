#ifndef SRC_UARTMANAGER_H_
#define SRC_UARTMANAGER_H_

#include <stdio.h>
#include <string.h>
#include <ti/drivers/UART.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <Board.h>

#include "globals.h"

void uartFxn(UArg arg0, UArg arg1);

#endif /* SRC_UARTMANAGER_H_ */
