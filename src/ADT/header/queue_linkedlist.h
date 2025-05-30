
#ifndef QUEUE_LINKED_LIST_H
#define QUEUE_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "../../header/user.h"

// Forward declaration instead of including user.h

#define Nil NULL
#define SENTINEL -1

/* Struktur node untuk list */
typedef struct AntrianNode *address;

typedef struct AntrianNode {
    User *pasien; // Data pasien
    address next;
} AntrianNode;

typedef struct {
    address first; // Pointer ke elemen pertama
    address last;  // Pointer ke elemen terakhir
    int jumlah; // Jumlah elemen dalam list
} AntrianDokter;

/* Struktur Queue berbasis Linked List */
typedef struct {
    int idDokter; // ID dokter
    AntrianDokter antrian; // Antrian pasien untuk dokter tersebut
} MapDokterAntrian;

/* ===== FUNGSI-FUNGSI LINKED LIST ===== */
boolean linkedlist_is_empty(AntrianDokter L);
/* Mengirim true jika list kosong */

address linkedlist_alokasi(User *X);
/* Alokasi memori untuk node baru dengan nilai X */

void linkedlist_dealokasi(address *P);
/* Dealokasi node */

/* ===== FUNGSI-FUNGSI QUEUE ===== */
void queue_init(AntrianDokter *q);
/* Inisialisasi Queue */

boolean queue_is_empty(AntrianDokter *q);
/* Mengirim true jika queue kosong */

boolean queue_is_full(AntrianDokter *q);
/* Jumlah pasien mengantri di ruangan maksimal adalah 3 orang */

void queue_enqueue(AntrianDokter *q, User *value);
/* Menambahkan elemen ke belakang queue */

int queue_dequeue(AntrianDokter *q);
/* Menghapus elemen dari depan queue dan mengembalikan nilainya */

int queue_size(AntrianDokter *q);
/* Menghitung jumlah elemen dalam queue */

#endif // QUEUE_LINKEDLIST_H