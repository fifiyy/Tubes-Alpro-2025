#include "../header/Lupa_Password.h"
#include "../ADT/header/List_User.h"

void generate_kode_unik(const char* username, char* kodeUnik) {
    int len = strlen(username);
    int count = 1;
    int pos = 0;
    
    for (int i = 1; i <= len; i++) {
        if (i < len && username[i] == username[i-1]) {
            count++;
        } else {
            if (count > 1) {
                pos += sprintf(kodeUnik + pos, "%d", count);
            }
            kodeUnik[pos++] = username[i-1];
            count = 1;
        }
    }
    kodeUnik[pos] = '\0';
}

void lupa_password_system(ListUser *users) {
    char username[USERNAME_LEN];
    char kodeUnikInput[100];
    char kodeUnikAsli[100];
    char newPassword[PASSWORD_LEN];
    
    printf("\n+-------------------------------------------------+\n");
    printf("|                  LUPA PASSWORD                  |\n");
    printf("+-------------------------------------------------+\n");
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    User* user = NULL;
    for (int i = list_get_first_idx(*users); i <= list_get_last_idx(*users); i++) {
        if (strcmp(users->data[i].username, username) == 0) {
            user = &users->data[i];
            break;
        }
    }
    
    if (user == NULL) {
        printf("Username tidak terdaftar!\n");
        return;
    }
    
    printf("Kode Unik: ");
    if (scanf("%99s", kodeUnikInput) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    generate_kode_unik(user->username, kodeUnikAsli);
    
    if (strcmp(kodeUnikInput, kodeUnikAsli) != 0) {
        printf("Kode unik salah!\n");
        return;
    }
    
    printf("Halo %s %s, silakan daftarkan ulang password anda!\n", 
           role_to_string(user->role), user->username);
    printf("Password Baru: ");
    if (scanf("%49s", newPassword) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    strcpy(user->password, newPassword);
    printf("Password berhasil diubah!\n");
}