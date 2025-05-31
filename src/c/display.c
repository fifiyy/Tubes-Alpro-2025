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
}

void display_menu_pasien() {
    
}

void display_menu_dokter() {

}

void display_menu_manajer() {

}

void display_status_user(const char* username, UserRole *role) {
    printf("\n");
    switch (*role)
    {
    case ROLE_MANAGER:
        printf("-> Active Manager: %s\n", username);
        break;
    case ROLE_DOKTER:
        printf("-> Active Dokter: %s\n", username);
        break;
    case ROLE_PASIEN:
        printf("-> Active Pasien: %s\n", username);
        int status = currUser->dataPasien->status;
        switch (status)
        {
        case butuhDiagnosa:
            printf("   Status: Butuh Diagnosa\n");
            break;
        case butuhDiberiObat:
            printf("   Status: Butuh Diberi Obat\n");
            break;
        case butuhMinumObat:
            printf("   Status: Butuh Minum Obat\n");
            break;
        case butuhPenawar:
            printf("   Status: Butuh Minum Penawar\n");
            break;
        case butuhPulang:
            printf("   Status: Sudah Boleh Pulang!\n");
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}