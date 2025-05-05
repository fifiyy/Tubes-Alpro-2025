#include <stdio.h>
#include <string.h>
#include "register.h"

// Cek apakah username sudah digunakan
int isUsernameUnique(User users[], int jumlahUser, char username[]) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 0; // tidak unik
        }
    }
    return 1; // unik
}

// Fungsi register pasien baru
void registerPasien(User users[], int *jumlahUser) {
    char username[50], password[50];

    printf(">>> REGISTRASI PASIEN\n");
    printf("Masukkan username: ");
    scanf("%s", username);

    if (!isUsernameUnique(users, *jumlahUser, username)) {
        printf("Username sudah digunakan. Gagal registrasi.\n");
        return;
    }

    printf("Masukkan password: ");
    scanf("%s", password);

    // Tambahkan data user baru
    strcpy(users[*jumlahUser].username, username);
    strcpy(users[*jumlahUser].password, password);
    strcpy(users[*jumlahUser].role, "pasien");

    (*jumlahUser)++; // increment jumlah user
    printf("Registrasi berhasil! Selamat datang, %s\n", username);
}
