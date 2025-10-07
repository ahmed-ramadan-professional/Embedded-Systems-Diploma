#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "STACK_LINKED_LIST.h"

typedef struct StackNode_s {
    STACK_VALUE_TYPE value;
    struct StackNode_s *next;
} StackNode_t;

static StackNode_t *top;

void stack_init(void) { top = NULL; }

uint8_t is_stack_empty(void) { return top == NULL; }

uint32_t get_stack_size(void) {
    StackNode_t *ptr = top;
    uint32_t counter = 0;
    while (ptr != NULL) {
        counter++;
        ptr = ptr->next;
    }
    return counter;
}

STACK_VALUE_TYPE stack_peek(void) { return top->value; }

void stack_push(STACK_VALUE_TYPE value) {
    StackNode_t *temp = top;
    top = (StackNode_t *)malloc(sizeof(StackNode_t));
    top->value = value;
    top->next = temp;
}

STACK_VALUE_TYPE stack_pop(void) {
    STACK_VALUE_TYPE temp_value = top->value;
    StackNode_t *temp_ptr = top;
    top = top->next;
    free(temp_ptr);
    return temp_value;
}

void stack_print(void) {
    StackNode_t *ptr = top;
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
}