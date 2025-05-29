#include "dokter.h"
#include <stdio.h>
#include <stdlib.h>

Pasien* assignPasienKeDokter(Dokter* dokter, Pasien* pasien) {
    if (dokter == NULL || pasien == NULL) {
        printf("Error: Data dokter atau pasien tidak valid\n");
        return NULL;
    }

    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (dokter->pasienDiRuangan[i] == pasien) {
            printf("Pasien sudah terdaftar di ruangan dokter ini\n");
            return NULL;
        }
    }

    AntrianNode* current = dokter->antrian.front;
    while (current != NULL) {
        if (&current->pasien == pasien) {
            printf("Pasien sudah berada dalam antrian dokter ini\n");
            return NULL;
        }
        current = current->next;
    }

    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (dokter->pasienDiRuangan[i] == NULL) {
            dokter->pasienDiRuangan[i] = pasien;
            pasien->posisiAntrian = 0;
            pasien->id_dokter = dokter->id;
            printf("Pasien berhasil didaftarkan ke ruangan\n");
            return pasien;
        }
    }

    int jumlahSebelum = banyakAntrian(&dokter->antrian);
    enqueue(&dokter->antrian, pasien);
    
    if (banyakAntrian(&dokter->antrian) > jumlahSebelum) {
        pasien->posisiAntrian = dokter->antrian.jumlah;
        pasien->id_dokter = dokter->id;
        printf("Pasien berhasil didaftarkan ke antrian\n");
        return pasien;
    }

    printf("Gagal mendaftarkan pasien ke antrian\n");
    return NULL;
}