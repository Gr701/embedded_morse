//Worked together in a session Mark, Timo and Anatolii on designing, testing and implementing

#include "uartManager.h"
#include <xdc/runtime/System.h>

void uartReadCallback(UART_Handle uart, char* rxBuf, size_t length) {
    static int itIn = 0;
    if (rxBuf[0] == 45 || rxBuf[0] == 46) {
        incomingMessage[itIn] = rxBuf[0];
        //System_printf("callback wrote %d at %d\n", incomingMessage[itIn], itIn);   System_flush();
        itIn++;
        itIn %= 30;
    }
    char c;
    UART_read(uart, &c, 1);
}

void uartFxn(UArg arg0, UArg arg1) {

    //open connection to serial port defined by Board_UART0
    UART_Handle uart;
    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_TEXT;
    uartParams.readDataMode = UART_DATA_TEXT;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.readMode = UART_MODE_CALLBACK;
    uartParams.readCallback = &uartReadCallback;
    uartParams.baudRate = 9600;
    uartParams.dataLength = UART_LEN_8;
    uartParams.parityType = UART_PAR_NONE;
    uartParams.stopBits = UART_STOP_ONE;
    uart = UART_open(Board_UART0, &uartParams);

    char msg[10];
    int itOut = 0;
    Char uartBuffer;
    while (true) {
        if (programState == LISTENING) {
            UART_read(uart, &uartBuffer, 1);
        } else if (programState == SENDING) {
            if (outgoingMessage[itOut] != '\0') {
                sprintf(msg, "%c\r\n\0", outgoingMessage[itOut]);
                UART_write(uart, msg, 4);
                Task_sleep(100000 / Clock_tickPeriod);
                outgoingMessage[itOut] = '\0';
                itOut++;
                itOut %= 15;
            }
        }
        Task_sleep(100000 / Clock_tickPeriod);
    }
}
