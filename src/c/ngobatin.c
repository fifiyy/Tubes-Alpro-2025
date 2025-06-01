#include "../header/Ngobatin.h"
#include <stdio.h>
#include <string.h>
#include "../../ADT/header/Ruangan.h"
#include "../header/User.h"
#include "../header/Dokter.h"

PenyakitObatEntry* cari_obat(const char *namaPenyakit) {
    for (int i = 0; i < jumlahPenyakit; i++) {
        if (strcmp(penyakitObatMap[i].namaPenyakit, namaPenyakit) == 0) {
            return &penyakitObatMap[i];
        }
    }
    return NULL; // Tidak ditemukan
}

void ngobatin (User *currUser, User *users, int banyakUser, ListRuangan *ruangan) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_DOKTER) {
        printf("\nERROR: Hanya dokter yang punya kemampuan mengobati pasien!\n");
        return;
    }

    // Cari data dokter
    Dokter *dokter = currUser->dataDokter;
    if (dokter == NULL) {
        printf("\nERROR: Data dokter tidak valid!\n");
      
        return;
    }

    // Cari ruangan dokter
    Ruangan *ruanganDokter = NULL;
    for (int i = 0; i < ruangan->jumlah; i++) {
        if (ruangan->ruang[i].dokter != NULL && ruangan->ruang[i].dokter->id == dokter->id) {
            ruanganDokter = &ruangan->ruang[i];
            break;
        }
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                    NGOBATIN                   |\n");
    printf("+-----------------------------------------------+\n");

    if (ruanganDokter == NULL) {
        printf("[dr. %s] Kamu belum memiliki ruangan!\n", currUser->username);
        return;
    }

    // Cari pasien pertama di antrian
    address current = ruanganDokter->Antrian.first;
    if (current == NULL || current->pasien->dataPasien == NULL) {
        printf("[dr. %s] Kamu lagi nggak ada pasien. Ngobatin siapa?\n", currUser->username);
        return;
    }
    Pasien *pasien = current->pasien->dataPasien;
    User *userPasien = current->pasien;

    if (pasien->status == butuhDiagnosa) {
        printf("[dr. %s] Pasien @%s belum didiagnosis. Diagnosis dulu sebelum mengobati!\n", currUser->username, userPasien->username);
        return;
    }
    if (pasien->status == butuhPulang) {
        printf("[dr. %s] Pasien @%s sudah sembuh, tidak perlu diobati lagi.\n", currUser->username, userPasien->username);
        return;
    }
    if (pasien->status == butuhMinumObat) {
        printf("[dr. %s] Pasien @%s sudah diberi obat, tidak perlu diobati lagi.\n", currUser->username, userPasien->username);
        return;
    }

    PenyakitObatEntry *entry = cari_obat(pasien->penyakit);
    if (entry == NULL) {
        printf("[dr. %s] Tidak ada obat untuk penyakit %s!\n", currUser->username, pasien->penyakit);
        return;
    }

    printf("[dr. %s] Resep untuk @%s (Penyakit: %s):\n", currUser->username, userPasien->username, pasien->penyakit);
    for (int i = 0; i < entry->jumlahObat; i++) {
        printf("        %d. %s\n", i+1, entry->obat[i].nama);
    }

    // Simpan daftar obat ke pasien
    pasien->jumlahObat = entry->jumlahObat;
    pasien->jumlahObatResep = entry->jumlahObat;
    
    for (int i = 0; i < entry->jumlahObat; i++) {
        pasien->daftarObat[i] = entry->obat[i];
        pasien->daftarObatResep[i] = entry->obat[i];
    }
    pasien->status = butuhMinumObat;
}