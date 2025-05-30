#include "../header/logout.h"

void logout_system() {
    if (currUser == NULL) {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        return;
    }
    
    printf("Sampai jumpa %s!\n", currUser->username);
    currUser = NULL;
}
