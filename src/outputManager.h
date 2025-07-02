#ifndef SRC_OUTPUTMANAGER_H_
#define SRC_OUTPUTMANAGER_H_


#include <xdc/runtime/System.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/drivers/pin/PINCC26XX.h>
#include <driverlib/timer.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include "Board.h"

#include "globals.h"

void outputFxn(UArg arg0, UArg arg1);

void playMusic();

#endif /* SRC_OUTPUTMANAGER_H_ */
