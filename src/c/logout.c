#include "../header/Logout.h"

void logout_system() {
    if (currUser == NULL) {
        printf("ERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    printf("\n+-----------------------------------------------+\n");
    printf("|                     LOG OUT                   |\n");
    printf("+-----------------------------------------------+\n");

    printf("\n>> Sampai jumpa @%s!\n", currUser->username);
    currUser = NULL;
}
