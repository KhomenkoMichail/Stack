#ifndef STACK_FUNCTIONS_H
#define STACK_FUNCTIONS_H

#include "structsAndEnums.h"

#define STACK_CTOR(stackName, stackInfoName, capacity)\
    stackInfoName.nameOfFile = __FILE__;\
    stackInfoName.nameOfFunct = __func__;\
    stackInfoName.numOfLine = __LINE__;\
    stackCtor(&stackName, capacity, #stackName, stackInfoName);\

#define STACK_ERRORS_CHECK(stackAddress, filePtr, dumpInfoAddress) \
        dumpInfoAddress->nameOfFile = __FILE__; \
        dumpInfoAddress->nameOfFunct = __func__; \
        dumpInfoAddress->numOfLine = __LINE__;\
    if(stackVerifier(stackAddress)) { \
        stackDump(stackAddress, filePtr, *dumpInfoAddress);\
        return stackAddress->errorCode;\
    }\

int stackCtor (stack_t* stack, ssize_t capacity, const char* nameOfStack, struct info creationInfo);

int stackPush (stack_t* stack, stackElement_t value, FILE* file, struct info* dumpInfo);

int fprintfElement (FILE* file, stackElement_t element);

int stackPop (stack_t* stack, FILE* file, struct info* dumpInfo);

int stackVerifier (stack_t* stack);

void stackDump (stack_t* stack, FILE* file, struct info dumpInfo);

void fprintfErrorForDump (stack_t* stack, FILE* file);

#endif
