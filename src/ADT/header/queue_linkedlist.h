#ifndef QUEUE_LINKEDLIST_H
#define QUEUE_LINKEDLIST_H

#include "boolean.h"
#include <stdlib.h>

#define Nil NULL
#define SENTINEL -1

typedef int infotype;

/* Struktur node untuk list */
typedef struct tElmtlist *address;
typedef struct tElmtlist {
    infotype info;
    address next;
} ElmtList;

typedef struct {
    address First;
} LinkedList;

/* Struktur Queue berbasis Linked List */
typedef struct {
    LinkedList list;
    address rear;
} QueueLinkedList;

/* ===== FUNGSI-FUNGSI LINKED LIST ===== */
boolean linkedlist_is_empty(LinkedList L);
/* Mengirim true jika list kosong */

void linkedlist_create_empty(LinkedList *L);
/* Menginisialisasi list kosong */

address linkedlist_alokasi(infotype X);
/* Alokasi memori untuk node baru dengan nilai X */

void linkedlist_dealokasi(address *P);
/* Dealokasi node */

address linkedlist_search(LinkedList L, infotype X);
/* Mencari elemen dengan info = X */

void linkedlist_insert_first(LinkedList *L, address P);
/* Menambahkan elemen di awal list */

void linkedlist_insert_last(LinkedList *L, address P);
/* Menambahkan elemen di akhir list */

void linkedlist_del_first(LinkedList *L, address *P);
/* Menghapus elemen pertama list dan mengembalikan alamatnya */

/* ===== FUNGSI-FUNGSI QUEUE ===== */
void queue_init(QueueLinkedList *q);
/* Inisialisasi Queue */

boolean queue_is_empty(QueueLinkedList *q);
/* Mengirim true jika queue kosong */

boolean queue_is_full(QueueLinkedList *q);
/* Karena queue berbasis linked list, selalu mengembalikan false */

void queue_enqueue(QueueLinkedList *q, int value);
/* Menambahkan elemen ke belakang queue */

int queue_dequeue(QueueLinkedList *q);
/* Menghapus elemen dari depan queue dan mengembalikan nilainya */

int queue_front(QueueLinkedList *q);
/* Mengambil nilai elemen di depan queue tanpa menghapus */

int queue_size(QueueLinkedList *q);
/* Menghitung jumlah elemen dalam queue */

#endif // QUEUE_LINKEDLIST_H
