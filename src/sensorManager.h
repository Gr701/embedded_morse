#ifndef SRC_SENSORMANAGER_H_
#define SRC_SENSORMANAGER_H_

//#include <xdc/std.h>
#include "stdio.h"
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CCC26XX.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>
#include "Board.h"
#include "sensors/mpu9250.h"

#include "globals.h"

void sensorFxn(UArg arg0, UArg arg1);

#endif /* SRC_SENSORMANAGER_H_ */
