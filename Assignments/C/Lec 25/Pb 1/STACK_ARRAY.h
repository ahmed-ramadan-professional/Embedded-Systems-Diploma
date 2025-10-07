#include <stdint.h>
#ifndef STACK_ARRAY
#define STACK_ARRAY

#define STACK_SIZE 100
#define STACK_VALUE_TYPE int32_t

void stack_init(void);
uint8_t is_stack_empty(void);
uint8_t is_stack_full(void);
uint32_t get_stack_size(void);
STACK_VALUE_TYPE stack_peek(void);
void stack_push(STACK_VALUE_TYPE val);
STACK_VALUE_TYPE stack_pop(void);
void stack_print(void);

#endif // STACK_ARRAY
