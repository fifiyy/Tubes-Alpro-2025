#include "../header/login.h"
#include "../header/list_user.h"

void login_system(ListUser *users) {
    // Cek apakah sudah ada user yang login
    if (currUser != NULL) {
        printf("Anda sudah login sebagai %s %s. Silakan logout terlebih dahulu untuk login dengan akun lain.\n",
               role_to_string(currUser->role), currUser->username);
        return;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    
    printf("Masukan username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    printf("Masukan password: ");
    if (scanf("%49s", password) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    for (int i = get_first_idx(*users); i <= get_last_idx(*users); i++) {
        User user = get_elmt(*users, i);
        if (strcmp(user.username, username) == 0) {
            if (strcmp(user.password, password) == 0) {
                currUser = &users->data[i];
                printf("Selamat pagi %s %s!", 
                       role_to_string(currUser->role), 
                       currUser->username);
                if (currUser->role == ROLE_PASIEN) {
                    printf(" Ada keluhan apa ?\n");
                } else {
                    printf("\n");
                }
                return;
            } else {
                printf("Password salah untuk pengguna yang bernama %s!\n", username);
                return;
            }
        }
    }
    
    printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n", username);
}