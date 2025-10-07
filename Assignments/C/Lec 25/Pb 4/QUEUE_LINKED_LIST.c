#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "QUEUE_LINKED_LIST.h"

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
    while (ptr != NULL) {
        counter++;
        ptr = ptr->next;
    }
    return counter;
}

void enqueue(QUEUE_VALUE_TYPE value) {
    if (rear == NULL) {
        rear = (QueueNode_t *)malloc(sizeof(QueueNode_t));
        rear->next = NULL;
        rear->value = value;
        return;
    }

    QueueNode_t *ptr = rear;
    while (ptr && ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    ptr->next->value = value;
    ptr->next->next = NULL;
}

QUEUE_VALUE_TYPE queue_peek(void) {
    if (rear) return rear->value;
}

QUEUE_VALUE_TYPE dequeue(void) {
    if (!is_queue_empty()) {
        QUEUE_VALUE_TYPE temp_value = rear->value;
        QueueNode_t *temp_ptr = rear;
        rear = rear->next;
        free(temp_ptr);
        return temp_value;
    }
}

void queue_print(void) {
    QueueNode_t *ptr = rear;
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
}