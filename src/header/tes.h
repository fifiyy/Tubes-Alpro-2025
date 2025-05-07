#ifndef TES_H
#define TES_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "boolean.h"


#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50


typedef enum {
    ROLE_MANAGER,
    ROLE_DOKTER,
    ROLE_PASIEN,
    ROLE_NONE
} UserRole;


typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    UserRole role;
} User;


typedef struct {
    char usernames[MAX_USERS][USERNAME_LEN];
    int count;
} UsernameSet;


UsernameSet username_set = { .count = 0 };
// Global variables
extern User users[MAX_USERS];
extern int user_count;
extern User* current_user;


// Function prototypes
const char* role_to_string(UserRole role);
boolean is_username_unique(const char* username);
boolean is_alpha_string(const char* str);
void generate_kode_unik(const char* username, char* kode_unik);
void login_system();
void register_pasien();
void logout_system();
void lupa_password_system();
void help_system();
void exit_system(const char* username);

#endif
