
#include "../header/User.h"

int user_count = 0; // Implementasi variabel global
User* currUser = NULL; // Implementasi variabel global

const char* role_to_string(UserRole role) {
    switch(role) {
        case ROLE_MANAGER: return "Manager";
        case ROLE_DOKTER: return "Dokter";
        case ROLE_PASIEN: return "Pasien";
        default: return "Unknown";
    }
}

boolean is_alpha_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || 
              (str[i] >= 'a' && str[i] <= 'z'))) {
            return false;
        }
    }
    return true;
}