
#ifndef STATE_H
#define STATE_H

typedef enum {
    LISTENING,
    SENDING
} ProgramState;

extern ProgramState programState;
extern bool didStateChange;

extern Char outgoingMessage[15];
extern Char incomingMessage[30];

#endif
