#include "../header/ngobatin.h"
#include <stdio.h>
#include <string.h>

PenyakitObatEntry* cariObat(const char *nama_penyakit) {
    for (int i = 0; i < totalPenyakit; i++) {
        if (strcmp(penyakitObatMap[i].nama_penyakit, nama_penyakit) == 0) {
            return &penyakitObatMap[i];
        }
    }
    return NULL; // Tidak ditemukan
}

void ngobatin(User *user_dokter) {
    if (user_dokter->role != ROLE_DOKTER) {
        printf("Hanya dokter yang punya kemampuan mengobati pasien!\n");
        return;
    }

    Dokter *dokter = user_dokter->dokter_data;

    int slot_aktif = -1;
    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (dokter->pasienDiRuangan[i] != NULL) {
            slot_aktif = i;
            break;
        }
    }

    if (slot_aktif == -1) {
        printf("[dr. %s] Kamu lagi nggak ada pasien. Ngobatin siapa?\n", user_dokter->username);
        return;
    }

    User *user_pasien = dokter->pasienDiRuangan[slot_aktif];
    Pasien *pasien = user_pasien->pasien_data;

    if (pasien->status != butuhDiberiObat) {
        printf("[dr. %s] Pasien %s belum didiagnosis. Diagnosis dulu!\n", user_dokter->username, user_pasien->username);
        return;
    }

    PenyakitObatEntry *entry = cariObat(pasien->penyakit);
    if (entry == NULL) {
        printf("[dr. %s] Tidak ada obat untuk penyakit %s!\n", user_dokter->username, pasien->penyakit);
        return;
    }

    printf("[dr. %s] Resep untuk %s (Penyakit: %s):\n", user_dokter->username, user_pasien->username, pasien->penyakit);
    for (int i = 0; i < entry->jumlah_obat; i++) {
        printf("        %d. %s\n", i+1, entry->obat[i].nama);
    }
    pasien->status = butuhMinumObat;
}