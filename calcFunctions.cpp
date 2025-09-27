#include <stdio.h>
#include <math.h>
#include <string.h>

#include "stackFunctions.h"
#include "structsAndEnums.h"
#include "calcFunctions.h"

int stackAdd (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    stackElement_t firstOperand = 0;
    stackElement_t secondOperand = 0;

    STACK_POP(stack, &firstOperand, file, dumpInfo);
    STACK_POP(stack, &secondOperand, file, dumpInfo);

    stackElement_t sum = secondOperand + firstOperand;

    STACK_PUSH(stack, sum, file, dumpInfo);

    return noErrors;
}

int stackSub (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    stackElement_t firstOperand = 0;
    stackElement_t secondOperand = 0;

    STACK_POP(stack, &firstOperand, file, dumpInfo);
    STACK_POP(stack, &secondOperand, file, dumpInfo);

    stackElement_t diff = secondOperand - firstOperand;

    STACK_PUSH(stack, diff, file, dumpInfo);

    return noErrors;
}

int stackMul (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    stackElement_t firstOperand = 0;
    stackElement_t secondOperand = 0;

    STACK_POP(stack, &firstOperand, file, dumpInfo);
    STACK_POP(stack, &secondOperand, file, dumpInfo);

    stackElement_t product = secondOperand * firstOperand;

    STACK_PUSH(stack, product, file, dumpInfo);

    return noErrors;
}

int stackDiv (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    stackElement_t firstOperand = 0;
    stackElement_t secondOperand = 0;

    STACK_POP(stack, &firstOperand, file, dumpInfo);
    STACK_POP(stack, &secondOperand, file, dumpInfo);

    if (firstOperand == 0) {
        STACK_PUSH(stack, secondOperand, file, dumpInfo);
        STACK_PUSH(stack, firstOperand, file, dumpInfo);

        fprintf(file, "ERROR! DIVISION BY ZERO IS IMPOSSIBLE!\n");
        printf("ERROR! DIVISION BY ZERO IS IMPOSSIBLE!\n");

        dumpInfo->nameOfFunct = __func__;
        dumpInfo->nameOfFile = __FILE__;
        dumpInfo->numOfLine = __LINE__;
        stackDump(stack, file, *dumpInfo);
        stackDump(stack, stdout, *dumpInfo);

        return divisionByZero;
    }


    stackElement_t quotient  = secondOperand / firstOperand;

    STACK_PUSH(stack, quotient, file, dumpInfo);

    return noErrors;
}

int stackPow (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    stackElement_t firstOperand = 0;
    stackElement_t secondOperand = 0;

    STACK_POP(stack, &firstOperand, file, dumpInfo);
    STACK_POP(stack, &secondOperand, file, dumpInfo);

    stackElement_t result = 1;
    for (int i = 0; i < firstOperand; i++)
        result *= secondOperand;

    STACK_PUSH(stack, result, file, dumpInfo);

    return noErrors;
}

int stackSqrt (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    stackElement_t operand = 0;

    STACK_POP(stack, &operand, file, dumpInfo);

    if (operand < 0) {
        STACK_PUSH(stack, operand, file, dumpInfo);

        fprintf(file, "ERROR! THE RADICAL EXPRESSION IS LESS THAN ZERO!\n");
        printf("ERROR! THE RADICAL EXPRESSION IS LESS THAN ZERO!\n");

        dumpInfo->nameOfFunct = __func__;
        dumpInfo->nameOfFile = __FILE__;
        dumpInfo->numOfLine = __LINE__;
        stackDump(stack, file, *dumpInfo);
        stackDump(stack, stdout, *dumpInfo);

        return badSqrt;
    }

    stackElement_t result = (stackElement_t)sqrt(operand);
    STACK_PUSH(stack, result, file, dumpInfo);

    return noErrors;
}

int stackOut (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    stackElement_t element = 0;
    STACK_POP(stack, &element, file, dumpInfo);
    printf("%d\n", element);

    return noErrors;
}

void readCommands (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(file);
    assert(dumpInfo);

    char command[10] = {};

    while(1) {
        scanf("%s", command);
        if (executeCommand(command, stack, file, dumpInfo))
            break;
    }
}

int executeCommand (const char* command, stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(command);
    assert(file);
    assert(dumpInfo);

    if (strcmp(command, "PUSH") == 0) {
        stackElement_t value = 0;
        if (scanf("%d", &value) != 1) {
            fprintf(file, "ERROR PUSH COMMAND! BAD OR NO PUSH VALUE! TRY AGAIN!\n");
            printf("ERROR PUSH COMMAND! BAD OR NO PUSH VALUE! TRY AGAIN!\n");
            return 0;
        }

        STACK_PUSH(stack, value, file, dumpInfo);
        return noErrors;
    }

    if (strcmp(command, "ADD") == 0) {
        int errorCode = stackAdd(stack, file, dumpInfo);
        return errorCode;
    }

    if (strcmp(command, "SUB") == 0) {
        int errorCode = stackSub(stack, file, dumpInfo);
        return errorCode;
    }

    if (strcmp(command, "MUL") == 0) {
        int errorCode = stackMul(stack, file, dumpInfo);
        return errorCode;
    }

    if (strcmp(command, "DIV") == 0) {
        int errorCode = stackDiv(stack, file, dumpInfo);
        return errorCode;
    }

    if (strcmp(command, "POW") == 0) {
        int errorCode = stackPow(stack, file, dumpInfo);
        return errorCode;
    }

    if (strcmp(command, "SQRT") == 0) {
        int errorCode = stackSqrt(stack, file, dumpInfo);
        return errorCode;
    }

    if (strcmp(command, "OUT") == 0) {
        int errorCode = stackOut(stack, file, dumpInfo);
        return errorCode;
    }

    if (strcmp(command, "HLT") == 0)
        return 1;

    fprintf(file, "ERROR! UNKNOWN COMMAND: \"%s\" ENTER ONLY AVAILABLE COMANDS!\n", command);
    printf("ERROR! UNKNOWN COMMAND: \"%s\" ENTER ONLY AVAILABLE COMANDS!\n", command);
    return 0;
}

