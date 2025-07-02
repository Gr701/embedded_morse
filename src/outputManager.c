//Worked Mark on designing, testing and implementing

#include "outputManager.h"

int melody2[] = {
    392, 261, 311, 349, 392, 261, 311, 349,
    392, 261, 311, 349, 392, 261, 311, 349,
    392, 261, 329, 349, 392, 261, 329, 349,
    392, 261, 329, 349, 392, 261, 329, 349,
    392, 261,

    311, 349, 392, 261, 311, 349,
    293,
    349, 233,
    311, 293, 349, 233,
    311, 293, 261,

    392, 261,

    311, 349, 392, 261, 311, 349,
    293,
    349, 233,
    311, 293, 349, 233,
    311, 293, 261,
    392, 261,
    311, 349, 392, 261, 311, 349,

    293,
    349, 233,
    293, 311, 293, 233,
    261,
    523,
    466,
    261,
    392,
    311,
    311, 349,
    392,

    523,
    466,
    261,
    392,
    311,
    311, 293,
    523, 392, 415, 466, 523, 392, 415, 466,
    523, 392, 415, 466, 523, 392, 415, 466,

    0, 831, 932, 1046, 784, 831, 932,
    1046, 784, 831, 932, 1046, 784, 831, 932
};

int durations2[] = {
    8, 8, 16, 16, 8, 8, 16, 16,
    8, 8, 16, 16, 8, 8, 16, 16,
    8, 8, 16, 16, 8, 8, 16, 16,
    8, 8, 16, 16, 8, 8, 16, 16,
    4, 4,

    16, 16, 4, 4, 16, 16,
    1,
    4, 4,
    16, 16, 4, 4,
    16, 16, 1,

    4, 4,

    16, 16, 4, 4, 16, 16,
    1,
    4, 4,
    16, 16, 4, 4,
    16, 16, 1,
    4, 4,
    16, 16, 4, 4, 16, 16,

    2,
    4, 4,
    8, 8, 8, 8,
    1,
    2,
    2,
    2,
    2,
    2,
    4, 4,
    1,

    2,
    2,
    2,
    2,
    2,
    4, 4,
    8, 8, 16, 16, 8, 8, 16, 16,
    8, 8, 16, 16, 8, 8, 16, 16,

    4, 16, 16, 8, 8, 16, 16,
    8, 16, 16, 16, 8, 8, 16, 16
};

//state led
PIN_State stateLedState;
const PIN_Id stateLedId = Board_LED0;
PIN_Config stateLedConfig[] = {
    stateLedId | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};
PIN_Handle stateLed;

//message led
PIN_State messageLedState;
const PIN_Id messageLedId = Board_LED1;
PIN_Config messageLedConfig[] = {
    messageLedId | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};
PIN_Handle messageLed;

//buzzer
PIN_State buzzerState;
PIN_Config buzzerConfig[] = {
    Board_BUZZER | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};
PIN_Handle buzzer;

void buzzerOpen() {
    Power_setDependency(PowerCC26XX_PERIPH_GPT0);
    Power_setConstraint(PowerCC26XX_SB_DISALLOW);
    TimerConfigure(GPT0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM);
    PINCC26XX_setMux(buzzer, Board_BUZZER, IOC_PORT_MCU_PORT_EVENT0);

}

bool buzzerSetFrequency(uint16_t freq) {
    if (freq < 3 || freq > 8000) {
        return false;
    }

    TimerDisable(GPT0_BASE, TIMER_A);

    uint32_t ticks = 48000000 / freq;
    uint32_t loadLow = ticks & 0x0000FFFF;
    uint32_t loadHigh = (ticks & 0x00FF0000) >> 16;
    uint32_t matchLow = (ticks / 2) & 0x0000FFFF;
    uint32_t matchHigh = ((ticks / 2) & 0x00FF0000) >> 16;

    TimerLoadSet(GPT0_BASE, TIMER_A, loadLow);
    TimerPrescaleMatchSet(GPT0_BASE, TIMER_A, loadHigh);
    TimerMatchSet(GPT0_BASE, TIMER_BOTH, matchLow);
    TimerPrescaleMatchSet(GPT0_BASE, TIMER_A, matchHigh);

    TimerEnable(GPT0_BASE, TIMER_A);
    return true;
}

void buzzerClose() {
    PINCC26XX_setMux(buzzer, Board_BUZZER, IOC_PORT_GPIO);
    Power_releaseDependency(PowerCC26XX_PERIPH_GPT0);
    Power_releaseConstraint(PowerCC26XX_SB_DISALLOW);
}

void playDot() {
    PIN_setOutputValue(messageLed, messageLedId, 1);
    buzzerOpen();
    buzzerSetFrequency(1700);
    Task_sleep(100000 / Clock_tickPeriod);
    PIN_setOutputValue(messageLed, messageLedId, 0);
    buzzerClose();
    Task_sleep(25000 / Clock_tickPeriod);
}

void playDash() {
    PIN_setOutputValue(messageLed, messageLedId, 1);
    buzzerOpen();
    buzzerSetFrequency(1500);
    Task_sleep(300000 / Clock_tickPeriod);
    PIN_setOutputValue(messageLed, messageLedId, 0);
    buzzerClose();
    Task_sleep(25000 / Clock_tickPeriod);
}

void playMusic() {
    int length = sizeof(durations2) / sizeof(int);
    static int i;
    for (i = 0; i < 30; i++) {
        i %= 130;
        buzzerOpen();
        buzzerSetFrequency(melody2[i] * 4);
        Task_sleep(durations2[i] * 10000 / 1.2 / Clock_tickPeriod);
        buzzerClose();
        Task_sleep(durations2[i] * 13000 / 1.2 / Clock_tickPeriod);
    }
}

void outputFxn(UArg arg0, UArg arg1) {
    //open pins
    stateLed = PIN_open(&stateLedState, stateLedConfig);
    if (stateLed == NULL) {
        System_abort("Error initializing LED pin\n");
    }

    messageLed = PIN_open(&messageLedState, messageLedConfig);
    if (messageLed == NULL) {
        System_abort("Error initializing LED pin\n");
    }

    buzzer = PIN_open(&buzzerState, buzzerConfig);
    if (buzzer == NULL) {
        System_abort("Error initializing BUZZER\n");
    }

    static int itrIn = 0;
    static int itrOut = 0;
    while (true) {
        if (didStateChange) {
            didStateChange = false;
            playMusic();
        }
        if (programState == LISTENING) {
            PIN_setOutputValue(stateLed, stateLedId, 1);
            switch (incomingMessage[itrIn]) {
                case '.':
                    incomingMessage[itrIn] = '\0';
                    itrIn++;
                    itrIn %= 30;
                    playDot();
                    break;
                case '-':
                    incomingMessage[itrIn] = '\0';
                    itrIn++;
                    itrIn %= 30;
                    playDash();
                default:
                    Task_sleep(100000 / Clock_tickPeriod);
                    break;
            }
        } else if (programState == SENDING) {
            PIN_setOutputValue(stateLed, stateLedId, 0);
            switch (outgoingMessage[itrOut]) {
                case '.':
                    itrOut++;
                    itrOut %= 15;
                    playDot();
                    break;
                case '-':
                    itrOut++;
                    itrOut %= 15;
                    playDash();
                    break;
                case ' ':
                    itrOut++;
                    itrOut %= 15;
                    Task_sleep(100000 / Clock_tickPeriod);
                    break;
                default:
                    Task_sleep(100000 / Clock_tickPeriod);
                    break;
            }
        }
    }

}
