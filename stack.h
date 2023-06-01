#ifndef PRACTIC3_STACK_H
#define PRACTIC3_STACK_H

struct stack {
    char data;
    stack* tail;
};

struct stack_i {
    double data;
    stack_i* tail;
};

stack* push(stack* str, char c);
bool empty(stack* str);
stack* pop(stack* str);
char top(stack* str);
stack_i* push(stack_i* s, double num);
bool empty(stack_i* str);
stack_i* pop(stack_i* str);
double top(stack_i* str);
int priority(char c);
void output_stack(stack* s);
int turnon(int k);

#endif //PRACTIC3_STACK_H
