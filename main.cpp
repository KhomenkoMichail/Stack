
#include <stdio.h>
#include <typeinfo>

#include "structsAndEnums.h"
#include "stackFunctions.h"

int main(void) {
    struct stack stk = {};
    struct info stackInfo = {};
    struct info dumpInfo = {};
    STACK_CTOR(stk, stackInfo, 4);


    if (stackPush(&stk, 10, stdout, &dumpInfo))
        return 1;
    if (stackPush(&stk, 20, stdout, &dumpInfo))
        return 1;
    if (stackPush(&stk, 30, stdout, &dumpInfo))
        return 1;

    stk.size = -2;

    fprintfElement(stdout, stackPop (&stk, stdout, &dumpInfo));
    if (stk.errorCode)
        return 1;
    fprintfElement(stdout, stackPop (&stk, stdout, &dumpInfo));
    if (stk.errorCode)
        return 1;

    fprintfElement(stdout, stackPop (&stk, stdout, &dumpInfo));
    if (stk.errorCode)
        return 1;
    if (stackDtor(&stk, stdout, &dumpInfo))
        return 1;

    return 0;
}
