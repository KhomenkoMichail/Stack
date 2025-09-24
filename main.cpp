
#include <stdio.h>
#include <typeinfo>


#include "structsAndEnums.h"
#include "stackFunctions.h"

int main(void) {
    struct stack stk = {};
    struct info stackInfo = {};
    struct info dumpInfo = {};
    STACK_CTOR(stk, stackInfo, 5);


    if (stackPush(&stk, 10, stdout, &dumpInfo))
        return 0;
    if (stackPush(&stk, 20, stdout, &dumpInfo))
        return 0;
    if (stackPush(&stk, 30, stdout, &dumpInfo))
        return 0;

    if (stackPop (&stk, stdout, &dumpInfo))
        return 0;
    if (stackPop (&stk, stdout, &dumpInfo))
        return 0;
    stk.size = -3;
    if (stackPop (&stk, stdout, &dumpInfo))
        return 0;


/*
    printf("stk.size == %d\n", stk.size);
    printf("stk.capacity == %d\n", stk.capacity);
    printf("stk.info.nameOfStack == %s\n", stk.info.nameOfStack);
    printf("stk.info.nameOfFile == %s\n", stk.info.nameOfFile);
    printf("stk.info.nameOfFunct == %s\n", stk.info.nameOfFunct);
    printf("stk.info.numOfLine == %d\n", stk.info.numOfLine);
    printf("stk.type == %s\n", txDemangle(typeid(stk.data[0]).name()).c_str());
*/
}
