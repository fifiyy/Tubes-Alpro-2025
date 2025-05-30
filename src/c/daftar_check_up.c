#include "../header/daftar_check_up.h"
#include <stdio.h>
#include <string.h>
#include "../header/user.h"
#include "../header/dokter.h"
#include "../header/ruangan.h"

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
void displayDokter(User *users, int user_count, ListRuangan *ruangan) {
    printf("\nBerikut adalah daftar dokter yang tersedia:\n");
    int dokter_count = 0;
    
    for (int i = 0; i < user_count; i++) {
        if (users[i].role != ROLE_DOKTER) {
            continue;
        }
        
        if (users[i].dokter_data == NULL) {
            printf("ERROR: Data dokter tidak valid untuk %s!\n", users[i].username);
            continue; // Skip invalid entries 
        }

        Dokter *dokter = users[i].dokter_data;
        dokter_count++;
        
        if (dokter->ruangan == '\0') {
            printf("%d. dr. %s (Belum memiliki ruangan)\n", dokter_count, users[i].username);
            continue;
        }
        
        // Cari ruangan dokter
        Ruangan *ruangan_dokter = NULL;
        for (int j = 0; j < ruangan->jumlah; j++) {
            if (ruangan->ruang[j].dokter != NULL && 
                ruangan->ruang[j].dokter->id == dokter->id) {
                ruangan_dokter = &ruangan->ruang[j];
                break;
            }
        }
        
        printf("%d. dr. %s (Ruangan %d) - Antrian: %d\n", 
               dokter_count,
               users[i].username,
               dokter->ruangan,
               ruangan_dokter ? ruangan_dokter->Antrian.jumlah : 0);
    }
}

void daftar_checkup(User *current_user, User *users, int user_count, ListRuangan *ruangan) {
    if (current_user->role != ROLE_PASIEN) {
        printf("ERROR: Hanya pasien yang bisa daftar check-up.\n");
        return;
    }

    if (current_user->pasien_data == NULL) {
        printf("ERROR: Data pasien tidak valid!\n");
        return;
    }

    Pasien *pasien = current_user->pasien_data;

    // Cek apakah pasien sudah dalam antrian
    if (pasien->posisiAntrian >= 0) {
        printf("Anda sudah terdaftar di antrian!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    //cek apakah pasien sudah berada di ruangan
    for (int i = 0; i < ruangan->jumlah; i++) {
        Ruangan *r = &ruangan->ruang[i];
        for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
            if (r->pasienDiRuangan[j].id == pasien->id) {
                printf("Anda sudah berada di ruangan %d!\n", r->nomor);
                return;
            }
        }
    }

    // Hitung jumlah dokter yang tersedia
    int banyakDokter = 0;
    for (int i = 0; i < user_count; i++) {
        if (users[i].role == ROLE_DOKTER) {
            banyakDokter++;
        }
    }

    displayDokter(users, user_count, ruangan);

    int pilihan;
    for (;;) {
        printf("\nPilih dokter (1-%d): ", banyakDokter);
        scanf("%d", &pilihan);
        if (pilihan >= 1 && pilihan <= banyakDokter) {
            break;
        }
        printf("Pilihan harus berada antara 1 sampai %d\n", banyakDokter);
    }

    // Cari dokter yang dipilih
    int dokter_index = 0;
    Dokter *dokterPilihan = NULL;
    User *user_dokter = NULL;
    
    for (int i = 0; i < user_count; i++) {
        if (users[i].role == ROLE_DOKTER) {
            dokter_index++;
            if (dokter_index == pilihan) {
                user_dokter = &users[i];
                dokterPilihan = users[i].dokter_data;
                break;
            }
        }
    }

    if (dokterPilihan == NULL) {
        printf("Dokter tidak ditemukan!\n");
        return;
    }

    // Assign pasien ke dokter
    Pasien *result = assignPasienKeDokter(current_user, dokterPilihan, pasien, ruangan);
    if (result != NULL) {
        // Jika pasien dimasukkan ke ruangan
        if (dokterPilihan->ruangan == '\0') {
            printf("Dokter %s belum memiliki ruangan, mendaftarkan ke antrian.\n", user_dokter->username);
        } else {
            printf("Pasien berhasil didaftarkan ke ruangan %d.\n", dokterPilihan->ruangan);
        }

        // jika pasien didaftarkan ke antrian
        if (result->posisiAntrian == -1) {
            printf("Pasien berhasil didaftarkan ke antrian dokter %s.\n", user_dokter->username);
            pasien->posisiAntrian = result->posisiAntrian;
        } else {
            pasien->posisiAntrian = result->posisiAntrian;
        }
        printf("\nPendaftaran berhasil!\n");
        printf("Anda terdaftar pada antrian dr. %s di ruangan %d!\n", 
               user_dokter->username, 
               dokterPilihan->ruangan);
        printf("Posisi antrian Anda: %d\n", result->posisiAntrian);
    } else {
        printf("Gagal mendaftar!\n");
    }
}