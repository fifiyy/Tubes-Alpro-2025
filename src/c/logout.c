#include "../header/logout.h"

void logout_system() {
    if (current_user == NULL) {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        return;
    }
    
    printf("Sampai jumpa %s!\n", current_user->username);
    current_user = NULL;
}
