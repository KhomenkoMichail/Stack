#include <stdio.h>

#include "stackFunctions.h"
#include "structsAndEnums.h"
#include "calcFunctions.h"

void stackAdd (stack_t* stack, FILE* file, struct info* dumpInfo) {

    int firstOperand = stackPop(stack, file, dumpInfo);
    int secondOperand = stackPop(stack, file, dumpInfo);

    int sum = firstOperand + secondOperand;

    stackPush(stack, sum, file, dumpInfo);

