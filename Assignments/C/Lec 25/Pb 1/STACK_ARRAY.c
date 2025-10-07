#include <stdint.h>
#include <stdio.h>

#include "STACK_ARRAY.h"

static STACK_VALUE_TYPE stack_arr[STACK_SIZE];
static int32_t top;

void stack_init(void) { top = -1; }

uint8_t is_stack_empty(void) { return top == -1; }

uint8_t is_stack_full(void) { return top == (uint32_t)STACK_SIZE - 1u; }

uint32_t get_stack_size(void) { return top + 1u; }

STACK_VALUE_TYPE stack_peek(void) { return stack_arr[top]; }

void stack_push(STACK_VALUE_TYPE val) { stack_arr[++top] = val; }

STACK_VALUE_TYPE stack_pop(void) { return stack_arr[top--]; }

void stack_print(void) {for (uint32_t i = 0; i<=top; i++) printf("%d ", stack_arr[top-i]);}