#include <TXLib.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <typeinfo>


#include "stackFunctions.h"
#include "structsAndEnums.h"

const stackElement_t POISON = 0xBADBABE;
const int MAX_CAPACITY = 100000000;

int stackCtor (stack_t* stack, ssize_t capacity, const char* nameOfStack, struct info creationInfo) {
    assert(stack);

    stack->size = 0;
    stack->capacity = capacity;
    stack->nameOfStack = nameOfStack;
    stack->errorCode = noErrors;
    stack->nameOfType = txDemangle(typeid((stack->data)[0]).name()).c_str();

    stack->stackInfo.nameOfFunct = creationInfo.nameOfFunct;
    stack->stackInfo.nameOfFile = creationInfo.nameOfFile;
    stack->stackInfo.numOfLine = creationInfo.numOfLine;

    if ((capacity <= 0) || (capacity > MAX_CAPACITY)) {
        stack->errorCode |= badCapacity;
        return stack->errorCode;
    }

    stack->data = (stackElement_t*)calloc(capacity, sizeof(stackElement_t));
    for(ssize_t numOfElement = 0; numOfElement < capacity; numOfElement++)
        stack->data[numOfElement] = POISON;

    return stack->errorCode;
}

int stackPush (stack_t* stack, stackElement_t value, FILE* file, struct info* dumpInfo) {
    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    stack->data[stack->size] = value;
    stack->size++;

    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stackElement_t* testBuffer = (stackElement_t*)realloc(stack->data, stack->capacity);

        if (testBuffer == NULL)
            stack->errorCode = badRealloc;

        else {
            free(stack->data);
            stack->data = testBuffer;
            stack->data[stack->size - 1] = value;
            for(ssize_t numOfElement = stack->size; numOfElement < stack->capacity; numOfElement++)
                stack->data[numOfElement] = POISON;
        }
    }

    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    return stack->errorCode;
}

int fprintfElement (FILE* file, stackElement_t element) {
    assert(file);

    if (element == POISON) {
        fprintf(file, "\"%X\" (POISON)\n", (int)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(int)) {
        fprintf(file, "\"%d\"\n", (int)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(double)) {
        fprintf(file, "\"%lf\"\n", (double)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(float)) {
        fprintf(file, "\"%f\"\n", (float)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(char)) {
        fprintf(file, "\"%c\"\n", (char)element);
        return 0;
    }
    if (typeid(stackElement_t) == typeid(char*)) {
        fprintf(file, "\"%s\"\n", (char*)element);
        return 0;
    }

    return 1;
}

stackElement_t stackPop (stack_t* stack, FILE* file, struct info* dumpInfo) {
    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    stack->size--;
    stackElement_t element = stack->data[stack->size];
    stack->data[stack->size] = POISON;

    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    return element;
}

int stackVerifier (stack_t* stack) {
    if (stack == NULL) {
        stack->errorCode |= badStackPtr;
        return stack->errorCode;
    }

    if (stack->data == NULL)
        stack->errorCode |= badDataPtr;

    if ((stack->size < 0) || ((stack->size > stack->capacity) && (stack->capacity >= 0))  || (stack->size > MAX_CAPACITY))
        stack->errorCode |= badSize;

    if ((stack->capacity <= 0) || (stack->capacity > MAX_CAPACITY))
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
        fprintf(file, "  (BAD SIZE!)\n");
    else fprintf(file, "\n");

    fprintf(file, "     capacity = %d", stack->capacity);
    if (stack->errorCode & badCapacity)
        fprintf(file, "  (BAD CAPACITY!)\n");
    else fprintf(file, "\n");

    fprintf(file, "     data [%p]", stack->data);
    if (stack->errorCode & badDataPtr)
        fprintf(file, "  (NULL DATA POINTER!)\n");
    else fprintf(file, "\n");

    fprintf(file, "     {\n");
    if (!(stack->errorCode & badCapacity))
        fprintfStackData(file, *stack);

    fprintf(file, "     }\n");
    fprintf(file, "}\n");
}


void fprintfErrorForDump (stack_t* stack, FILE* file) {
    assert(stack);
    assert(file);

    if (stack->errorCode & badStackPtr)
        fprintf(file, "_______________________ERROR! NULL STACK POINTER(%d)\n", badStackPtr);

    if (stack->errorCode & badDataPtr)
        fprintf(file, "_______________________ERROR! NULL DATA POINTER(%d)\n", badDataPtr);

    if (stack->errorCode & badSize)
        fprintf(file, "_______________________ERROR! BAD SIZE(%d)\n", badSize);

    if (stack->errorCode & badCapacity)
        fprintf(file, "_______________________ERROR! BAD CAPACITY(%d)\n", badCapacity);

    if (stack->errorCode & badElementType)
        fprintf(file, "_______________________ERROR! UNSUPPORTED DATA TYPE!(%d)\n", badElementType);

    if (stack->errorCode & badRealloc)
        fprintf(file, "_______________________ERROR! REALLOC DID NOT WORK CORRECTLY!(%d)\n", badRealloc);

}

int stackDtor (stack_t* stack, FILE* file, struct info* dumpInfo) {
    assert(stack);
    STACK_ERRORS_CHECK(stack, file, dumpInfo);

    free(stack->data);

    return(stack->errorCode);
}

void fprintfStackData (FILE* file, stack_t stack) {
    assert(file);

    for(ssize_t elementNum = 0; elementNum < stack.capacity; elementNum++) {
        if((elementNum < stack.size) && !(stack.errorCode & badSize)) {
            fprintf(file, "         *");
            fprintf(file, "[%d] = ", elementNum);
            fprintfElement(file, (stack.data)[elementNum]);
        }
        else {
            fprintf(file, "          [%d] = ", elementNum);
            fprintfElement(file, (stack.data)[elementNum]);
        }
    }
}



