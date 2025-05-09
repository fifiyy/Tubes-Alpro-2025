#include "../../include/auth/login.h"

void login_system() {
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
    
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                current_user = &users[i];
                printf("Selamat pagi %s %s!", 
                       role_to_string(current_user->role), 
                       current_user->username);
                if (current_user->role == ROLE_PASIEN) {
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
