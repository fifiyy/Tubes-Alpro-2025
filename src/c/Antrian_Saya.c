#include "../header/Antrian_Saya.h"
#include <stdio.h>
#include <string.h>

void cek_antrian_saya (User *user, User *users, ListRuangan *ruangan, int banyakUser) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        // return;
    }
=======
// void cek_antrian_saya (User *user, User *users, ListRuangan *ruangan, int banyakUser) {
//     if (currUser == NULL) {
//         printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
//         return;
//     }
>>>>>>> main
    
    if (user->role != ROLE_PASIEN) {
        printf("\nERROR: Hanya pasien yang bisa melihat antrian!\n");
        return;
    }
    
    Pasien *pasien = user->dataPasien;
    printf("\n+-----------------------------------------------+\n");
    printf("|                 STATUS ANTRIAN                |\n");
    printf("+-----------------------------------------------+\n");
    
    // Cek apakah pasien ada di antrian/ruangan manapun (berdasarkan queue)
    int found = 0;
    int posisi = -1;
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
        if (found) break;
    }

    if (!found) {
        if (pasien->posisiAntrian < 0) {
            printf("[@%s] Kamu nih belum terdaftar dalam antrian check-up (berkata dengan nada lemah lembut gemulai). Daftar dulu coba :D\n", user->username);
            printf("\nHELP: Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
        }
        return;
    }

    // Jika posisi < MAX_PASIEN_RUANGAN, berarti sudah di ruangan
    if (posisi < ruangan->ruang[idxRuang].kapasitas) {
        printf("[@%s] Kamu lagi di ruangan dokter, loh. Dokternya ga lagi tidur kan?\n", user->username);
        return;
    }

    // Jika posisi >= MAX_PASIEN_RUANGAN, tampilkan status antrian
    // Cari dokter dari id ruangan
    if (idxRuang < 0 || idxRuang >= ruangan->jumlah) {
        printf("\nERROR: Ruangan tidak ditemukan!\n");
        return;
    }
    if (ruangan->ruang[idxRuang].Antrian.first == NULL) {
        printf("\nERROR: Antrian ruangan %d kosong!\n", ruangan->ruang[idxRuang].nomor);
        return;
    }
    // Cari dokter yang menangani pasien ini
    Ruangan *ruanganDokter = &ruangan->ruang[idxRuang];
    Dokter *dokterPasien = ruanganDokter->dokter;

    if (dokterPasien == NULL) {
        printf("\nERROR: Dokter pasien %s tidak ditemukan!\n", user->username);
        return;
    }
    int kapasitas = ruangan->ruang[idxRuang].kapasitas;
    int totalQueue = queue_size(&ruangan->ruang[idxRuang].Antrian);
    int totalAntrian = totalQueue - kapasitas;
    if (totalAntrian < 0) totalAntrian = 0;

    int posisiAntrian = posisi - kapasitas + 1;
    if (posisiAntrian < 1) posisiAntrian = 1;

    printf("[@%s] Status antrian Anda:\n", user->username);
    printf("    Dokter: dr. %s\n", dokterPasien->username);
    printf("    Ruangan: %d\n", dokterPasien->nomorRuangan);
    printf("    Posisi antrian: %d dari %d\n", posisiAntrian, totalAntrian);
}