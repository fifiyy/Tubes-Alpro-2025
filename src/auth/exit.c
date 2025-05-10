#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_system(const char* username) {
    char input[10];

    printf("\nApakah Anda mau keluar dari rumah sakit? (y/n)\n");

    while (1) {
        printf("Pilihan Anda: ");
        scanf("%s", input);

        if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
            printf("\n%s keluar dari Rumah Sakit,\nSampai jumpa!\n", username);
            exit(0);
        } else if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
            printf("\nKembali ke menu utama...\n");
            return;
        } else {
            printf("Tidak valid. Pilih Y atau N ya!\n");
        }
    }
}
