#include "queue_linkedlist.h"
#include <stdio.h>

/* ===== IMPLEMENTASI FUNGSI LINKED LIST ===== */

boolean linkedlist_is_empty(LinkedList L) {
    return L.First == Nil;
}

void linkedlist_create_empty(LinkedList *L) {
    L->First = Nil;
}

address linkedlist_alokasi(infotype X) {
    address p = (address)malloc(sizeof(ElmtList));
    if (p != Nil) {
        p->info = X;
        p->next = Nil;
    }
    return p;
}

void linkedlist_dealokasi(address *P) {
    free(*P);
    *P = Nil;
}

address linkedlist_search(LinkedList L, infotype X) {
    address p = L.First;
    while (p != Nil && p->info != X) {
        p = p->next;
    }
    return p;
}

void linkedlist_insert_first(LinkedList *L, address P) {
    if (P != Nil) {
        P->next = L->First;
        L->First = P;
    }
}

void linkedlist_insert_last(LinkedList *L, address P) {
    if (linkedlist_is_empty(*L)) {
        linkedlist_insert_first(L, P);
    } else {
        address last = L->First;
        while (last->next != Nil) {
            last = last->next;
        }
        last->next = P;
    }
}

void linkedlist_del_first(LinkedList *L, address *P) {
    *P = L->First;
    if (*P != Nil) {
        L->First = (*P)->next;
        (*P)->next = Nil;
    }
}

/* ===== IMPLEMENTASI FUNGSI QUEUE ===== */

void queue_init(QueueLinkedList *q) {
    linkedlist_create_empty(&q->list);
    q->rear = Nil;
}

boolean queue_is_empty(QueueLinkedList *q) {
    return linkedlist_is_empty(q->list);
}

boolean queue_is_full(QueueLinkedList *q) {
    return false;
}

void queue_enqueue(QueueLinkedList *q, int value) {
    address P = linkedlist_alokasi(value);
    if (P != Nil) {
        if (queue_is_empty(q)) {
            q->list.First = P;
            q->rear = P;
        } else {
            q->rear->next = P;
            q->rear = P;
        }
    } else {
        printf("Alokasi memori gagal!\n");
    }
}

int queue_dequeue(QueueLinkedList *q) {
    if (!queue_is_empty(q)) {
        address P;
        int value;
        linkedlist_del_first(&q->list, &P);
        value = P->info;

        if (linkedlist_is_empty(q->list)) {
            q->rear = Nil;
        }

        linkedlist_dealokasi(&P);
        return value;
    } else {
        printf("Queue kosong!\n");
        return SENTINEL;
    }
}

int queue_front(QueueLinkedList *q) {
    if (!queue_is_empty(q)) {
        return q->list.First->info;
    } else {
        printf("Queue kosong!\n");
        return SENTINEL;
    }
}

int queue_size(QueueLinkedList *q) {
    int count = 0;
    address P = q->list.First;
    while (P != Nil) {
        count++;
        P = P->next;
    }
    return count;
}
