
#include "queue_linkedlist.h"
#include <stdio.h>

/* ===== IMPLEMENTASI FUNGSI LINKED LIST ===== */

boolean linkedlist_is_empty(AntrianDokter L) {
    return L.First == Nil;
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
    q->First = Nil;
    q->Last = Nil;
    q->jumlah = 0;
}

boolean queue_is_empty(AntrianDokter *q) {
    return q->First == Nil;
}

boolean queue_is_full(AntrianDokter *q) {
    // Karena queue berbasis linked list, selalu mengembalikan false
    return false;
}   

void queue_enqueue(AntrianDokter *q, User *value) {
    // Buat salinan User di heap
    User *newUser = malloc(sizeof(User));
    if (newUser != NULL) {
        *newUser = *value; // Salin isi user ke memori baru
        address P = linkedlist_alokasi(newUser);
        if (P != Nil) {
            if (queue_is_empty(q)) {
                q->First = P;
            } else {
                q->Last->next = P;
            }
            q->Last = P;
            q->jumlah++;
        } else {
            printf("Gagal alokasi node baru!\n");
            free(newUser);
        }
    } else {
        printf("Gagal alokasi User baru!\n");
    }
}


int queue_dequeue(AntrianDokter *q) {
    if (!queue_is_empty(q)) {
        address P = q->First;
        int id_pasien = P->pasien->pasien_data->id; // Simpan ID pasien yang akan dihapus
        q->First = P->next; // Pindahkan First ke node berikutnya
        linkedlist_dealokasi(&P); // Dealokasi node yang dihapus
        q->jumlah--;
        
        if (q->First == Nil) { // Jika antrian menjadi kosong
            q->Last = Nil;
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