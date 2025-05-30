#include "../header/antrian_saya.h"
#include <stdio.h>
#include <string.h>

void checkAntrianSaya(User *user, Dokter *dokter, int banyakDokter) {
    if (user->role != ROLE_PASIEN) {
        printf("ERROR: Hanya pasien yang bisa melihat antrian!\n");
        return;
    }

    Pasien *pasien = user->pasien_data;

    // Check if patient is already in a room
    for (int i = 0; i < banyakDokter; i++) {
        for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
            if (dokter[i].pasienDiRuangan[j] == pasien) {
                printf("\nAnda sedang berada di dalam ruangan dokter!\n");
                return;
            }
        }
    }

    // Check if patient is in queue
    if (pasien->posisiAntrian <= 0) {
        printf("\nAnda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
        return;
    }

    // Find the doctor the patient is assigned to
    Dokter *dokterPasien = NULL;
    for (int i = 0; i < banyakDokter; i++) {
        if (dokter[i].id == pasien->id_dokter) {
            dokterPasien = &dokter[i];
            break;
        }
    }

    if (dokterPasien == NULL) {
        printf("\nError: Dokter tidak ditemukan!\n");
        return;
    }

    int totalAntrian = banyakAntrian(&dokterPasien->antrian);
    
    printf("\nStatus antrian Anda:\n");
    printf("Dokter: dr. %s\n", dokterPasien->nama);
    printf("Ruangan: %c\n", dokterPasien->ruangan);
    printf("Posisi antrian: %d dari %d\n", pasien->posisiAntrian, totalAntrian);
}