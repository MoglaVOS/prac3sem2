#include "stack.h"
#include <iostream>

using namespace std;

stack* push(stack* str, char c) {
    stack* next = new stack;
    next->data = c;
    next->tail = str;
    return next;
}

bool empty(stack* str) {
    if (!str) return 1;
    else return 0;
}

stack* pop(stack* str) {
    stack* prev = str->tail;
    delete str;
    str = prev;
    return str;
}

char top(stack* str) {
    return str->data;
}

stack_i* push(stack_i* s, double num) {
    stack_i* next = new stack_i;
    next->data = num;
    next->tail = s;
    return next;
}

bool empty(stack_i* str) {
    if (!str) return 1;
    else return 0;
}

stack_i* pop(stack_i* str) {
    stack_i* prev = str->tail;
    delete str;
    str = prev;
    return str;
}

double top(stack_i* str) {
    return str->data;
}

int priority(char c) {
    switch (c) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return -1;
    }
}

int turnon(int k) {
    if (!k)
        cout << "1. Обратная польская нотация\n2. Завершить работу программы\n>>";
    else cout << "3. Открыть меню\n>>";
    cin >> k;
    if (k >= 1 && k <= 3) return k;
    else return -1;
}