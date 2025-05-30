#include "../header/register.h"
#include "../ADT/header/list_user.h"
#include "../ADT/header/set.h"
#include "../header/user.h"    

boolean is_username_unique(const Set *usernames, const char* username) {
    return !set_is_member(*usernames, username); // Gunakan fungsi IsMember dari Set
}

void register_pasien(ListUser *users, Set *usernames) {
    if (current_user != NULL) {
        printf("Anda sudah login. Silakan logout terlebih dahulu.\n");
        return;
    }
    
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (!is_alpha_string(username)) {
        printf("Username hanya boleh berisi huruf!\n");
        return;
    }
    
    if (!is_username_unique(usernames, username)) {
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
        return;
    }
    
    printf("Password: ");
    if (scanf("%49s", password) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (IsFull(*users)) {
        printf("Kapasitas user penuh!\n");
        return;
    }
    
    User new_user;
    strcpy(new_user.username, username);
    strcpy(new_user.password, password);
    new_user.role = ROLE_PASIEN;

    new_user.dataPasien = (Pasien*) malloc(sizeof(Pasien));
    if (new_user.dataPasien == NULL) {
        printf("Gagal mengalokasikan memori untuk pasien baru.\n");
        return;
    }
    new_user.dataPasien->id = NbElmt(*users) + 1; // ID unik berdasarkan jumlah user
    new_user.dataPasien->jumlahObat = 0; // Inisialisasi jumlah obat
    new_user.dataPasien->id_dokter = -1; // Belum ada dokter yang ditugaskan
    new_user.dataPasien->posisiAntrian = -1; // Pasien belum dalam antrian
    new_user.dataPasien->keluhan[0] = '\0'; // Inisialisasi keluhan kosong
    new_user.dataPasien->status = butuhDiagnosa; // Status awal pasien
    
    SetEl(users, NbElmt(*users), new_user);
    SetLength(users, NbElmt(*users) + 1);
    set_insert(usernames, username); // Tambahkan username ke dalam Set
    
    printf("Pasien %s berhasil ditambahkan!\n", username);
}
