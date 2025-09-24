#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <typeinfo>


#include "stackFunctions.h"
#include "structsAndEnums.h"

int stackCtor (stack_t* stack, ssize_t capacity, const char* nameOfStack) {
    assert(stack);
    assert(capacity > 0);

    stack->data = (stackElement_t*)calloc(capacity, sizeof(stackElement_t));
    stack->size = 0;
    stack->capacity = capacity;

    stack->stackInfo.nameOfFunct = __func__;
    stack->stackInfo.nameOfFile = __FILE__;
    stack->stackInfo.numOfLine = __LINE__;
    stack->nameOfStack = nameOfStack;
    stack->errorCode = noErrors;

    return stack->errorCode;
}

int stackPush (stack_t* stack, stackElement_t value, FILE* file, struct info* dumpInfo) {
    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    stack->data[stack->size] = value;
    stack->size++;

    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    return stack->errorCode;
}

int fprintfElement (FILE* file, stackElement_t element) {
    assert(file);

    if (typeid(stackElement_t) == typeid(int)) {
        fprintf(file, "%d\n", (int)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(double)) {
        fprintf(file, "%lf\n", (double)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(float)) {
        fprintf(file, "%f\n", (float)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(char)) {
        fprintf(file, "%c\n", (char)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(char*)) {
        fprintf(file, "%s\n", (char*)element);
        return 0;
    }

    return 1;
}

int stackPop (stack_t* stack, FILE* file, struct info* dumpInfo) {
    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    stack->size--;
    if (fprintfElement(file,stack->data[stack->size]) != 0) {
        stack->errorCode = badElementType;
        stackDump(stack, file, *dumpInfo);
    }

    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    return stack->errorCode;
}

int stackVerifier (stack_t* stack) {
    if (stack == NULL) {
        stack->errorCode |= badStackPtr;
        return stack->errorCode;
    }

    if (stack->data == NULL)
        stack->errorCode |= badDataPtr;

    if ((stack->size < 0) || (stack->size > stack->capacity))
        stack->errorCode |= badSize;

    if (stack->capacity < 0)
        stack->errorCode |= badCapacity;

return stack->errorCode;
}

void stackDump (stack_t* stack, FILE* file, struct info dumpInfo) {
    assert(stack);

    fprintf(file, "stackDump() from %s at %s:%d\n", dumpInfo.nameOfFunct, dumpInfo.nameOfFile, dumpInfo.numOfLine);
    fprintf(file, "stack <%s> [%p] from %s at %s:%d\n", stack->nameOfType, stack, stack->stackInfo.nameOfFunct, stack->stackInfo.nameOfFile, stack->stackInfo.numOfLine);

    fprintfErrorForDump(stack, file);
    fprintf(file, "{\n");

    fprintf(file, "     size = %d", stack->size);
    if (stack->errorCode & badSize)
        fprintf(file, "(BAD SIZE!)\n");
    else fprintf(file, "\n");

    fprintf(file, "     capacity = %d", stack->capacity);
    if (stack->errorCode & badCapacity)
        fprintf(file, "(BAD CAPACITY!)\n");
    else fprintf(file, "\n");

    fprintf(file, "     data [%p]", stack->data);
    if (stack->errorCode & badDataPtr)
        fprintf(file, "(BAD DATA POINTER!)\n");
    else fprintf(file, "\n");

    fprintf(file, "     {\n");
    for(ssize_t elementNum = 0; elementNum < stack->capacity; elementNum++) {
        if(elementNum < stack->size)
            fprintf(file, "         *");
        fprintf(file, "[%d] = ", elementNum);
        fprintfElement(file, (stack->data)[elementNum]);
    }

    fprintf(file, "     }\n");
    fprintf(file, "}\n");
}


void fprintfErrorForDump (stack_t* stack, FILE* file) {
    assert(stack);
    assert(file);

    if (stack->errorCode & badStackPtr)
        fprintf(file, "_______________________ERROR! BAD STACK POINTER(%d)\n", badStackPtr);

    if (stack->errorCode & badDataPtr)
        fprintf(file, "_______________________ERROR! BAD DATA POINTER(%d)\n", badDataPtr);

    if (stack->errorCode & badSize)
        fprintf(file, "_______________________ERROR! BAD SIZE(%d)\n", badSize);

    if (stack->errorCode & badCapacity)
        fprintf(file, "_______________________ERROR! BAD CAPACITY(%d)\n", badCapacity);

    if (stack->errorCode & badElementType)
        fprintf(file, "_______________________ERROR! BAD CAPACITY(%d)\n", badElementType);

}



