#include "Queue_Linkedlist.h"
#include <stdio.h>

/* ===== IMPLEMENTASI FUNGSI LINKED LIST ===== */

boolean linkedlist_is_empty(AntrianDokter L) {
    return L.first == Nil;
}

address linkedlist_alokasi(User *X) {
    address p = (address)malloc(sizeof(AntrianNode));
    if (p != Nil) {
        p->pasien = X;
        p->next = Nil;
    }
    return p; // Mengembalikan alamat node baru
}

void linkedlist_dealokasi(address *P) {
    free(*P);
    *P = Nil;
}

/* ===== IMPLEMENTASI FUNGSI QUEUE ===== */

void queue_init(AntrianDokter *q) {
    q->first = Nil;
    q->last = Nil;
    q->jumlah = 0;
}

boolean queue_is_empty(AntrianDokter *q) {
    return q->first == Nil;
}

boolean queue_is_full(AntrianDokter *q) {
    // Karena queue berbasis linked list, selalu mengembalikan false
    return false;
}   

void queue_enqueue(AntrianDokter *q, User *value) {
    address P = linkedlist_alokasi(value); // LANGSUNG pakai value, JANGAN malloc User baru!
    if (P != Nil) {
        if (queue_is_empty(q)) {
            q->first = P;
        } else {
            q->last->next = P;
        }
        q->last = P;
        q->jumlah++;
    } else {
        printf("Gagal alokasi node baru!\n");
    }
}


int queue_dequeue(AntrianDokter *q) {
    if (!queue_is_empty(q)) {
        address P = q->first;
        int id_pasien = P->pasien->dataPasien->id; // Simpan ID pasien yang akan dihapus
        q->first = P->next; // Pindahkan first ke node berikutnya
        linkedlist_dealokasi(&P); // Dealokasi node yang dihapus
        q->jumlah--;
        
        if (q->first == Nil) { // Jika antrian menjadi kosong
            q->last = Nil;
        }
        
        return id_pasien; // Kembalikan ID pasien yang dihapus
    } else {
        printf("Antrian kosong!\n");
        return SENTINEL; // Kembalikan nilai sentinel jika antrian kosong
    }
}

int queue_size(AntrianDokter *q) {
    return q->jumlah;
}