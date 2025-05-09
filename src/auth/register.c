#include "../../include/auth/register.h"

boolean is_username_unique(const char* username) {
    for (int i = 0; i < user_count; i++) {
        const char *a = users[i].username;
        const char *b = username;
        
        while (*a && *b) {
            char a_char = *a;
            char b_char = *b;
            
            if (a_char >= 'A' && a_char <= 'Z') a_char += 32;
            if (b_char >= 'A' && b_char <= 'Z') b_char += 32;
            
            if (a_char != b_char) break;
            
            a++;
            b++;
        }
        
        if (*a == '\0' && *b == '\0') {
            return false;
        }
    }
    return true;
}

void register_pasien() {
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
    
    if (!is_username_unique(username)) {
        printf("Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
        return;
    }
    
    printf("Password: ");
    if (scanf("%49s", password) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (user_count >= MAX_USERS) {
        printf("Kapasitas user penuh!\n");
        return;
    }
    
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    users[user_count].role = ROLE_PASIEN;
    user_count++;
    
    printf("Pasien %s berhasil ditambahkan!\n", username);
}
