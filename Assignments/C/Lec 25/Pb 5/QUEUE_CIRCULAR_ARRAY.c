#include <stdint.h>
#include <stdio.h>

#include "QUEUE_CIRCULAR_ARRAY.h"

static QUEUE_VALUE_TYPE queue_arr[QUEUE_SIZE];
static int32_t front, rear;

void queue_init(void) { front = rear = -1; }

uint8_t is_queue_empty(void) { return front == -1; }

uint8_t is_queue_full(void) { return (front == rear + 1) || ((front == 0) && (rear == (uint32_t)QUEUE_SIZE - 1u)); }

uint32_t get_queue_size(void) {
    if (is_queue_empty()) return 0;
    if (front <= rear) return rear - front + 1u;
    return rear + 1u + (uint32_t)QUEUE_SIZE - front;
}

void enqueue(QUEUE_VALUE_TYPE value) {
    if (!is_queue_full()) {
        if (is_queue_empty())
            rear = front = 0;
        else if (rear == (uint32_t)QUEUE_SIZE - 1u)
            rear = 0;
        else
            rear++;
        queue_arr[rear] = value;
    }
}

QUEUE_VALUE_TYPE queue_peek(void) {
    if (!is_queue_empty())
        return queue_arr[front];
}

QUEUE_VALUE_TYPE dequeue(void) {
    QUEUE_VALUE_TYPE return_value;
    if (!is_queue_empty()) {
        return_value = queue_arr[front];
        if (front == rear)
            front = rear = -1;
        else
            front = front == (uint32_t)QUEUE_SIZE - 1u ? 0 : front + 1;
        return return_value;
    }
}

void queue_print(void) {
    if (is_queue_empty()) return;
    if (front <= rear)
        for (int i = front; i <= rear; i++)
            printf("%d ", queue_arr[i]);
    else {
        for (uint32_t i = front; i < (uint32_t)QUEUE_SIZE - 1u; i++)
            printf("%d ", queue_arr[i]);
        for (uint32_t i = 0; i <= rear; i++)
            printf("%d ", queue_arr[i]);
    }
}