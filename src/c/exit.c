#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Exit.h"
#include "../header/User.h"

void exit_system(ListUser *users) {
    char input[10];

    printf("\n+-----------------------------------------------+\n");
    printf("|                   EXIT SYSTEM                 |\n");
    printf("+-----------------------------------------------+\n");

    printf("\nApakah Anda mau keluar dari rumah sakit? (y/n)\n");

    while (1) {
        printf("Pilihan Kamu: ");
        scanf("%s", input);
    
        if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
            if (currUser == NULL) {
                printf("\n>> User berhasil keluar dari Rumah Sakit Nimons.\nSampai jumpa!\n");
            } else {
                printf("\n>> @%s berhasil keluar dari Rumah Sakit Nimons.\nSampai jumpa!\n", currUser->username);
            }
            exit(0);
        } else if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
            printf("\n>> Kembali ke menu utama...\n");
            return;
        } else {
            printf("ERROR: Input tidak valid.\n");
            printf("HELP: Pilih Y atau N.\n");
        }
    }    
}