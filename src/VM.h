#ifndef CVIN_VM_H
#define CVIN_VM_H

#include "Program.h"

struct VM{
    struct Program* program;
    unsigned int instructionPointer;
    bool hasExec;
};

/**
 * Executes the instruction the VM is currently on.
 * @param vm - VM to be executed
 */
void executeVM(struct VM* vm);

/**
 * Draws the VM results to the screen
 * @param vm - VM to be drawn
 */
void drawVM(struct VM* vm);

/**
 * Increments the instruction pointer of the VM
 * @param vm - VM to be incremented
 */
void stepVM(struct VM* vm);

#endif //CVIN_VM_H
