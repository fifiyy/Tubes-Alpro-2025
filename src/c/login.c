#include "../header/Login.h"
#include "../header/List_User.h"

void login_system(ListUser *users) {
    // Cek apakah sudah ada user yang login
    if (currUser != NULL) {
        printf("\nERROR: Anda sudah login sebagai %s %s. Silakan logout terlebih dahulu untuk login dengan akun lain.\n",
               role_to_string(currUser->role), currUser->username);
        return;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("\n+-----------------------------------------------+\n");
    printf("|                     LOG IN                    |\n");
    printf("+-----------------------------------------------+\n");

    printf("Masukan username: ");
    if (scanf("%49s", username) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    printf("Masukan password: ");
    if (scanf("%49s", password) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    for (int i = list_get_first_idx(*users); i <= list_get_last_idx(*users); i++) {
        User user = list_get_elmt(*users, i);
        if (strcmp(user.username, username) == 0) {
            if (strcmp(user.password, password) == 0) {
                currUser = &users->data[i];
                return;
            } else {
                printf("\nERROR: Password salah untuk pengguna yang bernama %s!\n", username);
                return;
            }
        }
    }
    
    printf("\nERROR: Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n", username);
}