#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include "boolean.h"
#include "pasien.h"
// #include "dokter.h"

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct Dokter Dokter;

// Enum untuk role pengguna
typedef enum {
    ROLE_MANAGER,
    ROLE_DOKTER,
    ROLE_PASIEN,
    ROLE_NONE
} UserRole;

// Struktur data user
typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    UserRole role;

    union {
        Pasien *pasien_data;    // Jika role == ROLE_PASIEN
        Dokter *dokter_data;     // Jika role == ROLE_DOKTER
        // Manager *manager_data;   // Jika role == ROLE_MANAGER
    };
} User;

// Variabel global yang digunakan di seluruh program
extern int user_count;         // Jumlah user yang terdaftar
extern User* current_user;     // Pointer ke user yang sedang login

// Deklarasi fungsi utility
// Di user.h
// Deklarasi saja (tanpa implementasi)
const char* role_to_string(UserRole role);

boolean is_alpha_string(const char* str);  // Deklarasi saja!
#endif
