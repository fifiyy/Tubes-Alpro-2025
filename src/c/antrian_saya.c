#include "../header/antrian_saya.h"
#include <stdio.h>
#include <string.h>

void cek_antrian_saya (User *user, Dokter *dokter, ListRuangan *ruangan, int banyakDokter) {
    if (user->role != ROLE_PASIEN) {
        printf("ERROR: Hanya pasien yang bisa melihat antrian!\n");
        return;
    }

    Pasien *pasien = user->dataPasien;

    // Check if patient is already in a room
    for (int i = 0; i < ruangan->jumlah; i++) {
        for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
            if (ruangan->ruang[i].pasienDiRuangan[j].id == pasien->id) {
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
        if (dokter[i].id == pasien->idDokter) {
            dokterPasien = &dokter[i];
            break;
        }
    }

    if (dokterPasien == NULL) {
        printf("\nError: Dokter tidak ditemukan!\n");
        return;
    }

    // Find the room and calculate queue position
    int idx_ruang = dokterPasien->ruangan - 1;
    if (idx_ruang < 0 || idx_ruang >= ruangan->jumlah) {
        printf("\nError: Ruangan dokter tidak valid!\n");
        return;
    }

    int total_antrian = queue_size(&ruangan->ruang[idx_ruang].Antrian);
    int pasien_dalam_ruangan = 0;
    for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
        if (ruangan->ruang[idx_ruang].pasienDiRuangan[j].id != 0) {
            pasien_dalam_ruangan++;
        }
    }

    printf("\nStatus antrian Anda:\n");
    printf("Dokter: Dr. %s\n", dokterPasien->username);
    printf("Ruangan: A%d\n", dokterPasien->ruangan);
    printf("Posisi antrian: %d dari %d\n", 
           pasien->posisiAntrian, 
           total_antrian - pasien_dalam_ruangan);
}