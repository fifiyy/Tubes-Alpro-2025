#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "user.h"
#include "../ADT/header/list_user.h"
#include "boolean.h"

/**
 * @brief Node untuk antrian berbasis linked list
 */
typedef struct AntrianNode {
    Pasien pasien;               // Data pasien
    struct AntrianNode *next;    // Pointer ke node berikutnya
} AntrianNode;

/**
 * @brief Struktur antrian dokter menggunakan linked list
 */
typedef struct {
    AntrianNode *front;          // Pointer ke depan antrian
    AntrianNode *rear;           // Pointer ke belakang antrian
    int jumlah;                  // Jumlah pasien dalam antrian
} AntrianDokter;

/**
 * @brief Mapping antara dokter dan antriannya
 */
typedef struct {
    int dokter_id;               // ID dokter
    AntrianDokter antrian;       // Antrian pasien untuk dokter tersebut
} MapDokterAntrian;

// Fungsi dasar antrian
void initAntrian(AntrianDokter *q);
boolean isAntrianKosong(const AntrianDokter *q);
int banyakAntrian(const AntrianDokter *q);
void enqueue(AntrianDokter *q, Pasien *pasien);
Pasien dequeue(AntrianDokter *q);

#endif