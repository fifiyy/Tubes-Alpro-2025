#include <stdio.h>
#include <stdlib.h>  
#include "../header/logout.h"

int logout(User** current_user) {
    if (*current_user != NULL) {
        printf("Sampai jumpa, %s!\n", (*current_user)->username);
        free(*current_user);
        *current_user = NULL;
        return 1;
    } else {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        return 0;
    }
}