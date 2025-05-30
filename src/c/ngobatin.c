#include "../header/Ngobatin.h"
#include <stdio.h>
#include <string.h>
#include "../header/Ruangan.h"
#include "../header/User.h"
#include "../header/Dokter.h"

PenyakitObatEntry* cari_obat(const char *namaPenyakit) {
    for (int i = 0; i < totalPenyakit; i++) {
        if (strcmp(penyakitObatMap[i].namaPenyakit, namaPenyakit) == 0) {
            return &penyakitObatMap[i];
        }
    }
    return NULL; // Tidak ditemukan
}

void ngobatin (User *currUser, User *users, int banyakUser, ListRuangan *ruangan) {
    if (currUser == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.");
        return;
    }

    if (currUser->role != ROLE_DOKTER) {
        printf("Hanya dokter yang punya kemampuan mengobati pasien!\n");
        return;
    }

    // Cari data dokter
    Dokter *dokter = currUser->dataDokter;
    if (dokter == NULL) {
        printf("Data dokter tidak valid!\n");
        return;
    }

    // Cari ruangan dokter
    Ruangan *ruanganDokter = NULL;
    for (int i = 0; i < ruangan->jumlah; i++) {
        if (ruangan->ruang[i].dokter != NULL && 
            ruangan->ruang[i].dokter->id == dokter->id) {
                ruanganDokter = &ruangan->ruang[i];
                break;
        }
    }

    if (ruanganDokter == NULL) {
        printf("[dr. %s] Kamu belum memiliki ruangan!\n", currUser->username);
        return;
    }

    // Cari pasien yang sedang aktif
    int slot = -1;
    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (ruanganDokter->pasienDiRuangan[i].id != 0) {
            slot = i;
            break;
        }
    }

    if (slot == -1) {
        printf("[dr. %s] Kamu lagi nggak ada pasien. Ngobatin siapa?\n", currUser->username);
        return;
    }

    // Ambil data pasien aktif
    Pasien *pasien = &ruanganDokter->pasienDiRuangan[slot];

    User *userPasien = NULL;
    for (int i = 0; i < banyakUser; i++) {
        if (users[i].role == ROLE_PASIEN && 
            users[i].dataPasien != NULL && 
            users[i].dataPasien->id == pasien->id) {
            userPasien = &users[i];
            break;
        }
    }
    if (userPasien == NULL) {
        printf("[dr. %s] Data pasien tidak valid!\n", currUser->username);
        return;
    }

    // Cek status pasien
    if (pasien->status != butuhDiberiObat) {
        printf("[dr. %s] Pasien %s belum didiagnosis. Diagnosis dulu!\n", currUser->username, userPasien->username);
        return;
    }

    PenyakitObatEntry *entry = cariObat(pasien->penyakit);
    if (entry == NULL) {
        printf("[dr. %s] Tidak ada obat untuk penyakit %s!\n", currUser->username, pasien->penyakit);
        return;
    }

    printf("[dr. %s] Resep untuk %s (Penyakit: %s):\n", currUser->username, userPasien->username, pasien->penyakit);
    for (int i = 0; i < entry->jumlahObat; i++) {
        printf("        %d. %s\n", i+1, entry->obat[i].nama);
    }
    pasien->status = butuhMinumObat;
}