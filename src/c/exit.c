#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/exit.h"
#include "../header/user.h" // Untuk akses current_user

void exit_system(ListUser *users) {
    char input[10];

    printf("\nApakah Anda mau keluar dari rumah sakit? (y/n)\n");

    while (1) {
        printf("Pilihan Anda: ");
        scanf("%s", input);
    
        if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
            if (current_user == NULL) {
                printf("\nUser keluar dari Rumah Sakit,\nSampai jumpa!\n");
            } else {
                printf("\n%s keluar dari Rumah Sakit,\nSampai jumpa!\n", current_user->username);
            }
            exit(0);
        } else if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
            printf("\nKembali ke menu utama...\n");
            return;
        } else {
            printf("Tidak valid. Pilih Y atau N ya!\n");
        }
    }    
}
