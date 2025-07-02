//Worked together in a session Mark, Timo and Anatolii on designing, testing and implementing

#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include "Board.h"

#include "globals.h"
#include "sensorManager.h"
#include "buttonManager.h"
#include "uartManager.h"
#include "outputManager.h"

#define STACKSIZE = 2048
Char sensorTaskStack[2048];
Char uartTaskStack[2048];
Char outputTaskStack[2048];

//init globals.h
ProgramState programState = LISTENING;
bool didStateChange = false;
Char outgoingMessage[15] = {0};
Char incomingMessage[30] = {0};

int main(void) {
    //the beginning
    System_printf("I AM WORKING!!!\n");
    System_flush();

    //inits
    Board_initGeneral();
    Board_initI2C();
    registerButton();

    //sensor task
    Task_Params sensorTaskParams;
    Task_Params_init(&sensorTaskParams);
    sensorTaskParams.stackSize = 2048;
    sensorTaskParams.stack = &sensorTaskStack;
    Task_Handle sensorTask = Task_create(sensorFxn, &sensorTaskParams, NULL);
    if (sensorTask == NULL) {
        System_abort("Task create failed!\n");
    }

    //uart task
    Task_Params uartTaskParams;
    Task_Params_init(&uartTaskParams);
    uartTaskParams.stackSize = 2048;
    uartTaskParams.stack = &uartTaskStack;
    Task_Handle uartTask = Task_create(uartFxn, &uartTaskParams, NULL);
    if (uartTask == NULL) {
        System_abort("Task create failed!\n");
    }

    //output task
    Task_Params outputTaskParams;
    Task_Params_init(&outputTaskParams);
    outputTaskParams.stackSize = 2048;
    outputTaskParams.stack = &outputTaskStack;
    Task_Handle outputTask = Task_create(outputFxn, &outputTaskParams, NULL);
    if (outputTask == NULL) {
        System_abort("Task create failed\n");
    }

    //the end
    System_printf("WE GOT TO THE MAIN END\n");
    System_flush();
    BIOS_start();
    return 0;
}
