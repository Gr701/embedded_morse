//Worked together in a session Mark, Timo and Anatolii on designing, testing and implementing

#include "sensorManager.h"

void sensorFxn(UArg arg0, UArg arg1) {
    float ax, ay, az, gx, gy, gz;

    //open power pin and power the MPU
    PIN_Config MpuPinConfig[] = {
        Board_MPU_POWER |
        PIN_GPIO_OUTPUT_EN |
        PIN_GPIO_HIGH |
        PIN_PUSHPULL |
        PIN_DRVSTR_MAX,
        PIN_TERMINATE
    };
    PIN_State MpuPinState;
    PIN_Handle hMpuPin = PIN_open(&MpuPinState, MpuPinConfig);
    if (hMpuPin == NULL) {
        System_abort("MPU power pin open FAIL");
    }
    PIN_setOutputValue(hMpuPin, Board_MPU_POWER, Board_MPU_POWER_ON);
    Task_sleep(100000 / Clock_tickPeriod);
    System_printf("MPU power is ON\n");
    System_flush();

    //open i2c protocol
    const I2CCC26XX_I2CPinCfg i2cMPUCfg = {
        .pinSDA = Board_I2C0_SDA1,
        .pinSCL = Board_I2C0_SCL1
    };
    I2C_Handle i2cMPU;
    I2C_Params i2cMPUParams;
    I2C_Params_init(&i2cMPUParams);
    i2cMPUParams.bitRate = I2C_400kHz;
    i2cMPUParams.custom = (uintptr_t)&i2cMPUCfg;
    i2cMPU = I2C_open(Board_I2C, &i2cMPUParams);
    if (i2cMPU == NULL) {
        System_abort("Error initializing I2C for MPU\n");
    }

    //setup and calibration
    System_printf("MPU - setup and calibration.....\n");
    System_flush();
    mpu9250_setup(&i2cMPU);
    System_printf("MPU - setup and calibration OK\n");
    System_flush();

    //get data
    int i = 0;
    while (true) {
        if (programState == LISTENING) {
            //System_printf(outgoingMessage);   System_printf("sensor off\n");   System_flush();
            Task_sleep(1000000 / Clock_tickPeriod);
        }
        else if (programState == SENDING) {
            mpu9250_get_data(&i2cMPU, &ax, &ay, &az, &gx, &gy, &gz);
            //char str[100];
            //sprintf(str, "%6.3f, %6.3f, %6.3f, %6.3f, %6.3f, %6.3f\n", ax, ay, az, gx, gy, gz);   System_flush();
            //System_printf(str);
            if (abs(az + 1) > 1.5) {
                char sos[15] = {' ', ' ', '.', '.', '.', ' ', '-', '-', '-', ' ', '.', '.', '.', ' ', ' '};
                int j = 0;
                for (j = 0; j < 15; j++) {
                    outgoingMessage[i++] = sos[j];
                    i %= 15;
                }
                Task_sleep(500000 / Clock_tickPeriod);
            } else if (abs(gx) > 200) {
                outgoingMessage[i++] = '.';
                i %= 15;
                Task_sleep(500000 / Clock_tickPeriod);
            } else if (abs(gy) > 150) {
                outgoingMessage[i++] = '-';
                i %= 15;
                Task_sleep(500000 / Clock_tickPeriod);
            } else if (abs(gz) > 175) {
                outgoingMessage[i++] = ' ';
                i %= 15;
                Task_sleep(500000 / Clock_tickPeriod);
            }
        }
        Task_sleep(100000 / Clock_tickPeriod);
    }
}
