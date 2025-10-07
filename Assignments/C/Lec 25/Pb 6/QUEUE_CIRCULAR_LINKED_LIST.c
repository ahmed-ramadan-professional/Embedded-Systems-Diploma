#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "QUEUE_CIRCULAR_LINKED_LIST.h"

typedef struct QueueNode_s {
    QUEUE_VALUE_TYPE value;
    struct QueueNode_s *next;
} QueueNode_t;

static QueueNode_t *rear;

void queue_init(void) { rear = NULL; }

uint8_t is_queue_empty(void) { return rear == NULL; }

uint32_t get_queue_size(void) {
    QueueNode_t *ptr = rear;
    uint32_t counter = 0;
    if (!ptr) return counter;
    do {
        counter++;
        ptr = ptr->next;
    } while (ptr != rear);
    return counter;
}

void enqueue(QUEUE_VALUE_TYPE value) {
    QueueNode_t *r = rear;
    if (rear == NULL) {
        rear = (QueueNode_t *)malloc(sizeof(QueueNode_t));
        rear->next = rear;
        rear->value = value;
        return;
    }

    QueueNode_t *first = rear->next;
    rear->next = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    rear->next->value = value;
    rear->next->next = first;
    rear = rear->next;
}

QUEUE_VALUE_TYPE queue_peek(void) {
    if (rear) return rear->next->value;
}

QUEUE_VALUE_TYPE dequeue(void) {
    if (!is_queue_empty()) {
        QUEUE_VALUE_TYPE return_value = rear->next->value;
        if (rear->next == rear) {
            free(rear);
            rear = NULL;
            return return_value;
        }
        QueueNode_t *temp = rear->next;
        rear->next = rear->next->next;
        free(temp);
        return return_value;
    }
}

void queue_print(void) {
    QueueNode_t *r = rear;
    if (!rear) return;
    QueueNode_t *ptr = rear->next;
    do {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    } while (ptr != rear->next);
}