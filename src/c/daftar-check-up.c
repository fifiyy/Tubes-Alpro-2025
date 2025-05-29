#include "../header/daftar-check-up.h"
#include <stdio.h>
#include <string.h>

// Validasi input angka positif
boolean validasiFloat(float nilai, const char* namaVar) {
    if (nilai <= 0) {
        printf("%s harus positif!\n", namaVar);
        return false;
    }
    return true;
}

boolean validasiInt(int nilai, const char* namaVar) {
    if (nilai <= 0) {
        printf("%s harus positif!\n", namaVar);
        return false;
    }
    return true;
}


// Tampilkan daftar dokter yang tersedia
void displayDokter(Dokter *dokter, int banyakDokter) {
    printf("\nBerikut adalah daftar dokter yang tersedia:\n");
    for (int i = 0; i < banyakDokter; i++) {
        printf("%d. dr. %s (Ruangan %c) - Antrian: %d\n", 
               i + 1, 
               dokter[i].nama, 
               dokter[i].ruangan,
               banyakAntrian(&dokter[i].antrian));
    }
}

void daftarCheckUp(User *user, Dokter *dokter, int banyakDokter) {
    if (user->role != ROLE_PASIEN) {
        printf("ERROR: Hanya pasien yang bisa daftar check-up.\n");
        return;
    }

    Pasien *pasien = user->pasien_data;

    // Cek apakah pasien sudah dalam antrian
    if (pasien->posisiAntrian >= 0) {
        printf("Anda sudah terdaftar di antrian!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    printf("\n===== INPUT DATA MEDIS =====\n");

    do {
        printf("Suhu tubuh (Celcius): ");
        scanf("%f", &pasien->suhu);
    } while (!validasiFloat(pasien->suhu, "Suhu"));
    do {
        printf("Tekanan darah (sistol/diastol, contoh: 120 80): ");
        scanf("%d %d", &pasien->tekananDarah[0], &pasien->tekananDarah[1]);
    } while (pasien->tekananDarah[0] <= 0 || pasien->tekananDarah[1] <= 0);
    do {
        printf("Detak jantung (bpm): ");
        scanf("%d", &pasien->detakJantung);
    } while (!validasiInt(pasien->detakJantung, "Detak jantung"));
    do {
        printf("Saturasi oksigen (persentase): ");
        scanf("%f", &pasien->saturasiOksigen);
    } while (!validasiFloat(pasien->saturasiOksigen, "Saturasi oksigen"));
    do {
        printf("Kadar gula darah (mg/dL): ");
        scanf("%d", &pasien->kadarGulaDarah);
    } while (!validasiInt(pasien->kadarGulaDarah, "Kadar gula darah"));
    do {
        printf("Berat badan (kg): ");
        scanf("%f", &pasien->beratBadan);
    } while (!validasiFloat(pasien->beratBadan, "Berat badan"));
    do {
        printf("Tinggi badan (cm): ");
        scanf("%d", &pasien->tinggiBadan);
    } while (!validasiInt(pasien->tinggiBadan, "Tinggi badan"));
    do {
        printf("Kadar kolestrol (mg/dL): ");
        scanf("%d", &pasien->kadarKolesterol);
    } while (!validasiInt(pasien->kadarKolesterol, "Kadar kolestrol"));
    do {
        printf("Trombosit (ribu/µL): ");
        scanf("%d", &pasien->trombosit);
    } while (!validasiInt(pasien->trombosit, "Trombosit"));
    
    displayDokter(dokter, banyakDokter);

    int pilihan;
    for (;;) {
        printf("Pilih dokter (1-%d): ", banyakDokter);
        scanf("%d", &pilihan);
        if (pilihan >= 1 || pilihan <= banyakDokter) {
            break;
        }
        printf("Pilihan harus berada antara 1 sampai %d\n", banyakDokter);
    }

    // Assign pasien ke dokter
    Dokter *dokterPilihan = &dokter[pilihan - 1];
    User *user_dokter = dokterPilihan;
    Pasien *result = assignPasienKeDokter(dokterPilihan, pasien);
    if (result != NULL) {
        printf("\nPendaftaran berhasil!\n");
        printf("Anda terdaftar pada antrian dr. %s di ruangan %s!\n", user_dokter->username, dokterPilihan->ruangan);
        printf("Posisi antrian Anda: %d\n", pasien->posisiAntrian);
    } else {
        printf("Gagal mendaftar!\n");
    }
}