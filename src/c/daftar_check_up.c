#include "../header/Daftar_Check_Up.h"
#include <stdio.h>
#include <string.h>
#include "../header/User.h"
#include "../header/Dokter.h"
#include "../header/Ruangan.h"

// Validasi input angka positif
boolean validasi_float (float nilai, const char* namaVar) {
    if (nilai <= 0) {
        printf("%s harus positif!\n", namaVar);
        return false;
    }
    return true;
}

boolean validasi_integer (int nilai, const char* namaVar) {
    if (nilai <= 0) {
        printf("%s harus positif!\n", namaVar);
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
            printf("ERROR: Data dokter tidak valid untuk %s!\n", users[i].username);
            continue; // skip invalid entries 
        }

        Dokter *dokter = users[i].dataDokter;
        banyakDokter++;
        
        if (dokter->ruangan == '\0') {
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
        
        printf("%d. dr. %s (Ruangan %d) - Antrian: %d\n", 
               banyakDokter,
               users[i].username,
               dokter->ruangan,
               ruanganDokter ? ruanganDokter->Antrian.jumlah : 0);
    }
}

void daftar_check_up(User *currUser, User *users, int banyakUser, ListRuangan *ruangan) {
    if (currUser == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.");
        return;
    }
    
    if (currUser->role != ROLE_PASIEN) {
        printf("ERROR: Hanya pasien yang bisa daftar check-up.\n");
        return;
    }

    if (currUser->dataPasien == NULL) {
        printf("ERROR: Data pasien tidak valid!\n");
        return;
    }

    Pasien *pasien = currUser->dataPasien;

    // Cek apakah pasien sudah dalam antrian
    if (pasien->posisiAntrian >= 0) {
        printf("Anda sudah terdaftar di antrian!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    //cek apakah pasien sudah berada di ruangan/antrian (berdasarkan queue, bukan array manual)
    for (int i = 0; i < ruangan->jumlah; i++) {
        Ruangan *r = &ruangan->ruang[i];
        address curr = r->Antrian.first;
        while (curr != NULL) {
            if (curr->pasien->dataPasien == pasien) {
                printf("Anda sudah berada di ruangan %d (atau antrian ruangan %d)\n", r->nomor, r->nomor);
                return;
            }
            curr = curr->next;
        }
    }

    // Hitung jumlah dokter yang tersedia
    int banyakDokter = 0;
    for (int i = 0; i < banyakUser; i++) {
        if (users[i].role == ROLE_DOKTER) {
            banyakDokter++;
        }
    }

    printf("\n===== INPUT DATA MEDIS =====\n");

    do {
        printf("Suhu tubuh (Celcius): ");
        scanf("%f", &pasien->suhu);
    } while (!validasi_float(pasien->suhu, "Suhu"));
    do {
        printf("Tekanan darah (sistol/diastol, contoh: 120 80): ");
        scanf("%d %d", &pasien->tekananDarah[0], &pasien->tekananDarah[1]);
    } while (pasien->tekananDarah[0] <= 0 || pasien->tekananDarah[1] <= 0);
    do {
        printf("Detak jantung (bpm): ");
        scanf("%d", &pasien->detakJantung);
    } while (!validasi_integer(pasien->detakJantung, "Detak jantung"));
    do {
        printf("Saturasi oksigen (persentase): ");
        scanf("%f", &pasien->saturasiOksigen);
    } while (!validasi_float(pasien->saturasiOksigen, "Saturasi oksigen"));
    do {
        printf("Kadar gula darah (mg/dL): ");
        scanf("%d", &pasien->kadarGulaDarah);
    } while (!validasi_integer(pasien->kadarGulaDarah, "Kadar gula darah"));
    do {
        printf("Berat badan (kg): ");
        scanf("%f", &pasien->beratBadan);
    } while (!validasi_float(pasien->beratBadan, "Berat badan"));
    do {
        printf("Tinggi badan (cm): ");
        scanf("%d", &pasien->tinggiBadan);
    } while (!validasi_integer(pasien->tinggiBadan, "Tinggi badan"));
    do {
        printf("Kadar kolestrol (mg/dL): ");
        scanf("%d", &pasien->kadarKolesterol);
    } while (!validasi_integer(pasien->kadarKolesterol, "Kadar kolestrol"));
    do {
        printf("Trombosit (ribu/µL): ");
        scanf("%d", &pasien->trombosit);
    } while (!validasi_integer(pasien->trombosit, "Trombosit"));
    
    
    display_dokter(users, banyakUser, ruangan);

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
        printf("Dokter tidak ditemukan!\n");
        return;
    }

    // Assign pasien ke dokter
    Pasien *result = assign_pasien_ke_dokter(currUser, dokterPilihan, pasien, ruangan);
    if (result != NULL) {
        // Jika pasien dimasukkan ke ruangan
        if (dokterPilihan->ruangan == '\0') {
            printf("Dokter %s belum memiliki ruangan, mendaftarkan ke antrian.\n", userDokter->username);
        } else {
            printf("Pasien berhasil didaftarkan ke ruangan %d.\n", dokterPilihan->ruangan);
        }

        // jika pasien didaftarkan ke antrian
        if (result->posisiAntrian == -1) {
            printf("Pasien berhasil didaftarkan ke antrian dokter %s.\n", userDokter->username);
            pasien->posisiAntrian = result->posisiAntrian;
        } else {
            pasien->posisiAntrian = result->posisiAntrian;
        }
        printf("\nPendaftaran berhasil!\n");
        printf("Anda terdaftar pada antrian dr. %s di ruangan %d!\n", 
               userDokter->username, 
               dokterPilihan->ruangan);
        printf("Posisi antrian Anda: %d\n", result->posisiAntrian);
    } else {
        printf("Gagal mendaftar!\n");
    }
}
