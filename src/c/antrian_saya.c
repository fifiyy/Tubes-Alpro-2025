#include "../header/antrian_saya.h"
#include <stdio.h>
#include <string.h>

void cek_antrian_saya (User *user, Dokter *dokter, ListRuangan *ruangan, int banyakDokter) {
    if (user->role != ROLE_PASIEN) {
        printf("ERROR: Hanya pasien yang bisa melihat antrian!\n");
        return;
    }

    Pasien *pasien = user->dataPasien;

    // Pastiin pasien ga di ruangan
    for (int i = 0; i < ruangan->jumlah; i++) {
        for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
            if (ruangan->ruang[i].pasienDiRuangan[j].id == pasien->id) {
                printf("[%s] Kamu lagi di ruangan dokter, loh. Dokternya ga lagi tidur kan?\n", user->username);
                return;
            }
        }
    }

    // Cek udah daftar cek up belum
    if (pasien->posisiAntrian <= 0) {
        printf("[%s] Kamu nih belum terdaftar dalam antrian check-up (berkata dengan nada lemah lembut gemulai).\nDaftar dulu coba :D\n");
        printf("HELP: Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
        return;
    }

    // Cari dokter dari pasien
    Dokter *dokterPasien = NULL;
    for (int i = 0; i < banyakDokter; i++) {
        if (dokter[i].id == pasien->idDokter) {
            dokterPasien = &dokter[i];
            break;
        }
    }

    if (dokterPasien == NULL) {
        printf("\nERROR: Dokter pasien %s tidak ditemukan!\n", user->username);
        return;
    }

    // Cari ruangan dokter
    int idxRuang = dokterPasien->ruangan - 1;
    if (idxRuang < 0 || idxRuang >= ruangan->jumlah) {
        printf("\nERROR: Ruangan dokter tidak valid!\n");
        return;
    }

    int totalAntrian = queue_size(&ruangan->ruang[idxRuang].Antrian);
    int pasienDalamRuang = 0;
    for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
        if (ruangan->ruang[idxRuang].pasienDiRuangan[j].id != 0) {
            pasienDalamRuang++;
        }
    }

    printf("[%s}Status antrian Anda:\n", user->username);
    printf("Dokter: dr. %s\n", dokterPasien->username);
    printf("Ruangan: %d\n", dokterPasien->ruangan);
    printf("Posisi antrian: %d dari %d\n", 
           pasien->posisiAntrian, 
           totalAntrian - pasienDalamRuang);
}