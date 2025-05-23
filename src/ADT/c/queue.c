#include <stdio.h>
#include "../header/queue.h"

void queue_init_queue(struct Queue *q) {
    q->count = 0;
}

boolean queue_is_empty(struct Queue *q) {
    return q->count == 0;
}

boolean queue_is_full(struct Queue *q) {
    return q->count == MAX_SIZE;
}

void queue_enqueue(struct Queue *q, int value) {
    if (!queue_is_full(q)) {
        q->items[q->count] = value;
        q->count++;
    }
    else {
        printf("Queue penuh!\n");
    }
}

int queue_dequeue(struct Queue *q) {
    if (!queue_is_empty(q)) {
        int value = q->items[0];
        for (int i = 1; i < q->count; i++) {
            q->items[i - 1] = q->items[i];
        }
        q->count--;
        return value;
    } else {
        printf("Queue kosong!\n");
        return SENTINEL;
    }
}

int queue_front(struct Queue *q) {
    if (!queue_is_empty(q)) {
        return q->items[0];
    } else {
        printf("Queue kosong!\n");
        return SENTINEL;
    }
}

int queue_size(struct Queue *q) {
    return q->count;
}
