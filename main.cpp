#include <stdio.h>
#include <typeinfo>

#include "structsAndEnums.h"
#include "stackFunctions.h"

int main(void) {
    struct stack stk = {};
    struct info stackInfo = {};
    struct info dumpInfo = {};

    FILE* logFile = fopen("writeDump.log", "w");

    int x = 0;

    STACK_CTOR(stk, stackInfo, 2);
    STACK_PUSH(&stk, 10, logFile, &dumpInfo);

    STACK_POP(&stk, &x, logFile, &dumpInfo);

    printf("x = %d\n", x);

    return 0;
}
