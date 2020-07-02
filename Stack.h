#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>


typedef struct stack Stack;

Stack* stack_create(int size);
int stack_push(Stack* s, int a);
int stack_pop(Stack* s, int* val);
int stack_top(Stack *s, int *val);
int stack_empty(Stack* s);
#endif