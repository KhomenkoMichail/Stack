#ifndef STRUCTS_AND_ENUMS_H
#define STRUCTS_AND_ENUMS_H

typedef int stackElement_t;

enum stackErr_t {
    noErrors = 0b0,
    badStackPtr= 0b1,
    badDataPtr = 0b10,
    badSize = 0b100,
    badCapacity = 0b1000,
    badElementType = 0b10000,
    badRealloc = 0b100000,
};

struct info {
    const char* nameOfFile;
    const char* nameOfFunct;
    unsigned int numOfLine;
};

struct stack {
    stackElement_t* data;
    ssize_t size;
    ssize_t capacity;
    const char* nameOfType;
    const char* nameOfStack;
    int errorCode;
    struct info stackInfo;
};


typedef struct stack stack_t;

#endif

