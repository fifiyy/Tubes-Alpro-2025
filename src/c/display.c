#include <stdio.h>
#include "../header/Display.h"

void display_main_menu() {
    printf("\n\n");
    printf("▗▄▄▖ █  ▐▌▄▄▄▄  ▗▞▀▜▌▐▌        ▗▄▄▖▗▞▀▜▌█  ▄ ▄    ■      ▗▖  ▗▖▄ ▄▄▄▄   ▄▄▄  ▄▄▄▄   ▄▄▄ \n");
    printf("▐▌ ▐▌▀▄▄▞▘█ █ █ ▝▚▄▟▌▐▌       ▐▌   ▝▚▄▟▌█▄▀  ▄ ▗▄▟▙▄▖    ▐▛▚▖▐▌▄ █ █ █ █   █ █   █ ▀▄▄  \n");
    printf("▐▛▀▚▖     █   █      ▐▛▀▚▖     ▝▀▚▖     █ ▀▄ █   ▐▌      ▐▌ ▝▜▌█ █   █ ▀▄▄▄▀ █   █ ▄▄▄▀ \n");
    printf("▐▌ ▐▌                ▐▌ ▐▌    ▗▄▄▞▘     █  █ █   ▐▌      ▐▌  ▐▌█                        \n");
    printf("                                                 ▐▌                                     \n");
    printf("=======================================================================================\n");
    printf("|                               WELCOME TO RUMAH SAKIT NIMONS                         |\n");
    printf("=======================================================================================\n");
    printf("| LOGIN                                                                               |\n");
    printf("| REGISTER                                                                            |\n");
    printf("| EXIT                                                                                |\n");
    printf("| HELP                                                                                |\n");
    printf("=======================================================================================\n");
    printf("© 2025 - K03-A. All rights reserved.\n");
}

void display_status_user(const char* username, UserRole *role) {
    printf("\n");
    switch (*role) {
    case ROLE_MANAGER:
        printf("-> Active Manager: %s\n", username);
        break;
    case ROLE_DOKTER:
        printf("-> Active Dokter: %s\n", username);
        break;
    case ROLE_PASIEN:
        printf("-> Active Pasien: %s\n", username);
        int status = currUser->dataPasien->status;
        switch (status) {
        case butuhDiagnosa:
            printf("   Status: Butuh Didiagnosa\n");
            break;
        case butuhDiberiObat:
            printf("   Status: Butuh Diberi Obat\n");
            break;
        case butuhMinumObat:
            printf("   Status: Butuh Minum Obat\n");
            break;
        case butuhPenawar:
            if (currUser->dataPasien->sisaNyawa <= 0) {
                printf("   Status: Pasien Sudah Meninggal\n");
                break;
            }
            else {
                printf("   Status: Butuh Minum Penawar\n");
                break;
            }
        
        case butuhPulang:
            printf("   Status: Sudah Boleh Pulang!\n");
            break;
        case butuhCheckup:
            printf("   Status: Butuh Checkup\n");
            break;
        default:
            printf("   Status: Tidak Diketahui\n");
            break;
        }
        printf("   Sisa Nyawa:\033[1;31m%d\033[0m\n", currUser->dataPasien->sisaNyawa);
        break;
    }
}