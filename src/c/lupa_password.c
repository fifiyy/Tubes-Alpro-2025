#include "../header/lupa_password.h"
#include "../ADT/header/list_user.h"

void generate_kode_unik(const char* username, char* kode_unik) {
    int len = strlen(username);
    int count = 1;
    int pos = 0;
    
    for (int i = 1; i <= len; i++) {
        if (i < len && username[i] == username[i-1]) {
            count++;
        } else {
            if (count > 1) {
                pos += sprintf(kode_unik + pos, "%d", count);
            }
            kode_unik[pos++] = username[i-1];
            count = 1;
        }
    }
    kode_unik[pos] = '\0';
}

void lupa_password_system(ListUser *users) {
    char username[USERNAME_LEN];
    char kode_unik_input[100];
    char kode_unik_asli[100];
    char password_baru[PASSWORD_LEN];
    
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    User* user = NULL;
    for (int i = GetFirstIdx(*users); i <= GetLastIdx(*users); i++) {
        if (strcmp(GetElmt(*users, i).username, username) == 0) {
            user = &users->data[i];
            break;
        }
    }
    
    if (user == NULL) {
        printf("Username tidak terdaftar!\n");
        return;
    }
    
    printf("Kode Unik: ");
    if (scanf("%99s", kode_unik_input) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    generate_kode_unik(user->username, kode_unik_asli);
    
    if (strcmp(kode_unik_input, kode_unik_asli) != 0) {
        printf("Kode unik salah!\n");
        return;
    }
    
    printf("Halo %s %s, silakan daftarkan ulang password anda!\n", 
           role_to_string(user->role), user->username);
    printf("Password Baru: ");
    if (scanf("%49s", password_baru) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    strcpy(user->password, password_baru);
    printf("Password berhasil diubah!\n");
}
