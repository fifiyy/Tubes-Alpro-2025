#include "../header/Antrian_Saya.h"
#include <stdio.h>
#include <string.h>

void cek_antrian_saya (User *user, User *users, ListRuangan *ruangan, int banyakUser) {
    if (currUser == NULL) {
        printf("ERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    
    if (user->role != ROLE_PASIEN) {
        printf("ERROR: Hanya pasien yang bisa melihat antrian!\n");
        return;
    }

    Pasien *pasien = user->dataPasien;
    
    // Cek apakah pasien ada di antrian/ruangan manapun (berdasarkan queue)
    int found = 0;
    int posisi = 0;
    int idxRuang = -1;
    for (int i = 0; i < ruangan->jumlah; i++) {
        address curr = ruangan->ruang[i].Antrian.first;
        posisi = 0;
        while (curr != NULL) {
            if (curr->pasien->dataPasien == pasien) {
                found = 1;
                idxRuang = i;
                break;
            }
            curr = curr->next;
            posisi++;
        }
        if (found) {
            break;
        }
    }

    if (!found) {
        if (pasien->posisiAntrian < 0) {
            printf("[%s] Kamu nih belum terdaftar dalam antrian check-up (berkata dengan nada lemah lembut gemulai).\nDaftar dulu coba :D\n", user->username);
            printf("HELP: Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
        }
        return;
    }

    // Jika posisi < MAX_PASIEN_RUANGAN, berarti sudah di ruangan
    if (posisi < MAX_PASIEN_RUANGAN) {
        printf("[%s] Kamu lagi di ruangan dokter, loh. Dokternya ga lagi tidur kan?\n", user->username);
        return;
    }

    // Jika posisi >= MAX_PASIEN_RUANGAN, tampilkan status antrian
    // Cari dokter dari pasien
    Dokter *dokterPasien = NULL;
    for (int i = 0; i < banyakUser; i++) {
        if (users[i].role == ROLE_DOKTER && users[i].dataDokter != NULL && users[i].dataDokter->id == pasien->idDokter) {
            dokterPasien = users[i].dataDokter;
            break;
        }
    }
    if (dokterPasien == NULL) {
        printf("\nERROR: Dokter pasien %s tidak ditemukan!\n", user->username);
        return;
    }
    int totalAntrian = queue_size(&ruangan->ruang[idxRuang].Antrian);
    printf("[%s] Status antrian Anda:\n", user->username);
    printf("Dokter: dr. %s\n", dokterPasien->username);
    printf("Ruangan: %d\n", dokterPasien->ruangan);
    printf("Posisi antrian: %d dari %d\n", posisi - MAX_PASIEN_RUANGAN + 1, totalAntrian - MAX_PASIEN_RUANGAN);
}