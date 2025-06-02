#include "../header/Daftar_Check_Up.h"
#include <stdio.h>
#include <string.h>
#include "../header/User.h"
#include "../header/Dokter.h"
#include "../header/Ruangan.h"

// Validasi input angka positif
boolean validasi_float (float nilai, const char* namaVar) {
    if (nilai <= 0) {
        printf(" ERROR: %s harus positif!\n", namaVar);
        return false;
    }
    return true;
}

boolean validasi_integer (int nilai, const char* namaVar) {
    if (nilai <= 0) {
        printf(" ERROR: %s harus positif!\n", namaVar);
        return false;
    }
    return true;
}

// Tampilkan daftar dokter yang tersedia
void display_dokter (User *users, int banyakUser, ListRuangan *ruangan) {
    printf("\nBerikut adalah daftar dokter yang tersedia:\n");
    int banyakDokter = 0;
    
    for (int i = 0; i < banyakUser; i++) {
        if (users[i].role != ROLE_DOKTER) {
            continue;
        }
        
        if (users[i].dataDokter == NULL) {
            printf("ERROR: Data dokter tidak valid untuk dr. %s!\n", users[i].username);
            continue; // skip invalid entries 
        }

        Dokter *dokter = users[i].dataDokter;
        banyakDokter++;
        
        if (dokter->nomorRuangan == '\0') {
            printf("%d. dr. %s (Belum memiliki ruangan)\n", banyakDokter, users[i].username);
            continue;
        }
        
        // Cari ruangan dokter
        Ruangan *ruanganDokter = NULL;
        for (int j = 0; j < ruangan->jumlah; j++) {
            if (ruangan->ruang[j].dokter != NULL && 
                ruangan->ruang[j].dokter->id == dokter->id) {
                ruanganDokter = &ruangan->ruang[j];
                break;
            }
        }
        
        printf("%d. dr. %s (Ruangan %d) - Total Ruangan + Antrian: %d\n", 
               banyakDokter,
               users[i].username,
               dokter->nomorRuangan,
               ruanganDokter->Antrian.jumlah);
    }
}

void daftar_check_up(User *currUser, User *users, int banyakUser, ListRuangan *ruangan) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    
    if (currUser->role != ROLE_PASIEN) {
        printf("\nERROR: Hanya pasien yang bisa daftar check-up.\n");
        return;
    }

    if (currUser->dataPasien == NULL) {
        printf("\nERROR: Data pasien tidak valid!\n");
        return;
    }

    Pasien *pasien = currUser->dataPasien;

    // Cek apakah pasien sudah dalam antrian
    if (pasien->posisiAntrian >= 0) {
        printf("[@%s] Kamu sudah terdaftar di antrian!\n", currUser->username);
        printf("    Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    if (pasien->status != butuhCheckup) {
        printf("[@%s] Kamu sudah daftar checkup, silakan tunggu anda didiagnosis.\n", currUser->username);
        return;
    }

    // Hitung jumlah dokter yang tersedia
    int banyakDokter = 0;
    for (int i = 0; i < banyakUser; i++) {
        if (users[i].role == ROLE_DOKTER) {
            banyakDokter++;
        }
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|                 DAFTAR CHECK UP               |\n");
    printf("+-----------------------------------------------+\n");

    printf(">> Input data medis:\n");
    do {
        printf("Suhu tubuh (Celcius): ");
        if (scanf("%f", &pasien->suhu) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_float(pasien->suhu, "Suhu"));
    do {
        printf("Tekanan darah (sistol/diastol, contoh: 120 80): ");
        if (scanf("%d %d", &pasien->tekananDarah[0], &pasien->tekananDarah[1]) != 2) {
            printf("\n ERROR: Input harus berupa dua angka!\n");
            while (getchar() != '\n');
            pasien->tekananDarah[0] = pasien->tekananDarah[1] = -1;
            continue;
        }
    } while (pasien->tekananDarah[0] <= 0 || pasien->tekananDarah[1] <= 0);
    do {
        printf("Detak jantung (bpm): ");
        if (scanf("%d", &pasien->detakJantung) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_integer(pasien->detakJantung, "Detak jantung"));
    do {
        printf("Saturasi oksigen (persentase): ");
        if (scanf("%f", &pasien->saturasiOksigen) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_float(pasien->saturasiOksigen, "Saturasi oksigen"));
    do {
        printf("Kadar gula darah (mg/dL): ");
        if (scanf("%d", &pasien->kadarGulaDarah) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_integer(pasien->kadarGulaDarah, "Kadar gula darah"));
    do {
        printf("Berat badan (kg): ");
        if (scanf("%f", &pasien->beratBadan) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_float(pasien->beratBadan, "Berat badan"));
    do {
        printf("Tinggi badan (cm): ");
        if (scanf("%d", &pasien->tinggiBadan) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_integer(pasien->tinggiBadan, "Tinggi badan"));
    do {
        printf("Kadar kolestrol (mg/dL): ");
        if (scanf("%d", &pasien->kadarKolesterol) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_integer(pasien->kadarKolesterol, "Kadar kolestrol"));
    do {
        printf("Trombosit (ribu/µL): ");
        if (scanf("%d", &pasien->trombosit) <=0) {
            printf("\n ERROR: Input harus berupa angka!\n");
            while (getchar() != '\n'); // flush buffer
            pasien->suhu = -1;
            continue;
        }
    } while (!validasi_integer(pasien->trombosit, "Trombosit"));
    
    
    display_dokter(users, banyakUser, ruangan);

    int pilihan;
    for (;;) {
        printf("\nPilih dokter (1-%d): ", banyakDokter);
        scanf("%d", &pilihan);
        if (pilihan >= 1 && pilihan <= banyakDokter) {
            break;
        }
        printf("ERROR: Pilihan harus berada antara 1 sampai %d\n", banyakDokter);
    }

    // Cari dokter yang dipilih
    int idxDokter = 0;
    Dokter *dokterPilihan = NULL;
    User *userDokter = NULL;
    
    for (int i = 0; i < banyakUser; i++) {
        if (users[i].role == ROLE_DOKTER) {
            idxDokter++;
            if (idxDokter == pilihan) {
                userDokter = &users[i];
                dokterPilihan = users[i].dataDokter;
                break;
            }
        }
    }

    if (dokterPilihan == NULL) {
        printf("ERROR: Dokter tidak ditemukan!\n");
        return;
    }

    // Assign pasien ke dokter
    Pasien *result = assign_pasien_ke_dokter(currUser, dokterPilihan, pasien, ruangan);
    if (result != NULL) {
        // Jika pasien dimasukkan ke ruangan
        if (dokterPilihan->nomorRuangan == '\0') {
            printf("ERROR: Dokter %s belum memiliki ruangan. Mendaftarkan ke antrian...\n", 
                userDokter->username);
        } else {
            printf(">> Pasien berhasil didaftarkan ke ruangan %d.\n", 
                dokterPilihan->nomorRuangan);
        }

        // jika pasien didaftarkan ke antrian
        if (result->posisiAntrian == -1) {
            printf(">> Pasien berhasil didaftarkan ke antrian dokter %s.\n", 
                userDokter->username);
            pasien->posisiAntrian = result->posisiAntrian;
        } else {
            pasien->posisiAntrian = result->posisiAntrian;
        }
        printf("\n>> Pendaftaran berhasil! <<\n");
        printf("[@%s] Kamu terdaftar pada antrian dr. %s di ruangan %d.\n",
               currUser->username,
               userDokter->username, 
               dokterPilihan->nomorRuangan);
        printf("[@%s] Posisi antrian Kamu: %d\n", 
            currUser->username, result->posisiAntrian);

        pasien->status = butuhDiagnosa; // Set status pasien
    } else {
        printf("ERROR: Gagal mendaftar!\n");
    }
}