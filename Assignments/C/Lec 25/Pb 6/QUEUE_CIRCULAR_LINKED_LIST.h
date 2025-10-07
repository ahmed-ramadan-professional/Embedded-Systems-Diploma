#include <stdint.h>
#ifndef QUEUE_CIRCULAR_LINKED_LIST
#define QUEUE_CIRCULAR_LINKED_LIST

#define QUEUE_VALUE_TYPE int32_t

void queue_init(void);
uint8_t is_queue_empty(void);
uint32_t get_queue_size(void);
QUEUE_VALUE_TYPE queue_peek(void);
void enqueue(QUEUE_VALUE_TYPE value);
QUEUE_VALUE_TYPE dequeue(void);
void queue_print(void);

#endif // QUEUE_CIRCULAR_LINKED_LIST
