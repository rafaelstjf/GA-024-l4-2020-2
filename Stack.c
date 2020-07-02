#include "Stack.h"

struct stack
{
    int size;
    int occupied;
    int *array;
};

Stack *stack_create(int size)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->size = size;
    s->occupied = 0;
    s->array = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        s->array[i] = 0;
    }
    return s;
}
int stack_push(Stack *s, int a)
{
    if (s && s->occupied < s->size)
    {
        s->array[s->occupied] = a;
        s->occupied++;
        return 1;
    }
    return 0;
}
int stack_pop(Stack *s, int *val)
{
    if (s && s->occupied > 0)
    {
        s->occupied--;
        *val = s->array[s->occupied];
        return 1;
    }
    return 0;
}
int stack_top(Stack *s, int *val)
{
    if (s && s->occupied > 0)
    {
        *val = s->array[s->occupied-1];
        return 1;
    }
    return 0;
}
int stack_empty(Stack *s)
{
    return (s && s->occupied > 0) ? 0 : 1;
}