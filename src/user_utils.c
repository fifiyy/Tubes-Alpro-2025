#include "../include/user.h"

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
