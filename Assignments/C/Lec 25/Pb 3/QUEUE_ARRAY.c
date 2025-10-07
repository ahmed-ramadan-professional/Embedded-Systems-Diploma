#include <stdint.h>
#include <stdio.h>

#include "QUEUE_ARRAY.h"

static QUEUE_VALUE_TYPE queue_arr[QUEUE_SIZE];
static int32_t front, rear;

void queue_init(void) { front = rear = -1; }

uint8_t is_queue_empty(void) { return (rear == -1 && front == -1) || (front == rear + 1); }

uint8_t is_queue_full(void) { return rear == (uint32_t)QUEUE_SIZE - 1u; }

uint32_t get_queue_size(void) { return rear - front + 1u; }

void enqueue(QUEUE_VALUE_TYPE value) {
    if (front == -1) {
        front = rear = 0;
    } else {
        rear++;
    }
    queue_arr[rear] = value;
}

QUEUE_VALUE_TYPE queue_peek(void) {
    if (!is_queue_empty())
        return queue_arr[front];
}

QUEUE_VALUE_TYPE dequeue(void) {
    if (!is_queue_empty())
        return queue_arr[front++];
}

void queue_print(void) {
    if (is_queue_empty()) return;
    for (uint32_t i = front; i <= rear; i++)
        printf("%d ", queue_arr[i]);
}