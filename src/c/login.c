#include <stdio.h>
#include <string.h>
#include "../header/login.h"

// Variabel global
User currentUser;
int isLoggedIn = 0;

// Menyimpan user yang login
void setCurrentUser(User user) {
    currentUser = user;
    isLoggedIn = 1;
}

// Proses login
void login(User users[], int jumlahUser) {
    char inputUsername[50];
    char inputPassword[50];

    printf(">>> LOGIN\n");
    printf("Username: ");
    scanf("%s", inputUsername);
    printf("Password: ");
    scanf("%s", inputPassword);

    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(users[i].username, inputUsername) == 0) {
            if (strcmp(users[i].password, inputPassword) == 0) {
                setCurrentUser(users[i]);

                // Sambutan berdasarkan role
                if (strcmp(currentUser.role, "manager") == 0) {
                    printf("Selamat pagi Manager %s!\n", currentUser.username);
                } else if (strcmp(currentUser.role, "dokter") == 0) {
                    printf("Selamat pagi Dokter %s!\n", currentUser.username);
                } else if (strcmp(currentUser.role, "pasien") == 0) {
                    printf("Selamat pagi %s! Ada keluhan apa?\n", currentUser.username);
                }
                return;
            } else {
                printf("Password salah untuk pengguna bernama %s!\n", inputUsername);
                return;
            }
        }
    }

    printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama  %s!\n", inputUsername);
}

// Proses logout
void logout() {
    if (isLoggedIn) {
        isLoggedIn = 0;
        printf("Sampai jumpa, %s!\n", currentUser.username);
    } else {
        printf("Logout gagal! Anda belum login.\n");
    }
}
