#include <TXLib.h>
#include <stdio.h>
#include <typeinfo>


#include "structsAndEnums.h"
#include "stackFunctions.h"

int main(void) {
    struct stack stk = {};
    struct info dumpInfo = {};
    STACK_CTOR(stk, 5);

    if (stackPush(&stk, 10, stdout, &dumpInfo))

    stackPop (&stk, stdout, &dumpInfo);


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
