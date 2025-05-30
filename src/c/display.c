#include <stdio.h>
#include "display.h"

void displayMainMenu() {
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
    printf("=======================================================================================\n");
}

void displayMenuPasien() {
    printf("\n==== MENU PASIEN ====\n");
    printf("Ketikkan perintah di dalam kurung untuk menjalankan fungsi.\n");
    printf("1. Daftar Checkup (DAFTAR_CHECKUP)\n");
    printf("2. Lihat Denah Ruangan (LIHAT_DENAH)\n");
    printf("3. Lihat Ruangan (LIHAT_RUANGAN)\n");
    printf("4. Logout (LOGOUT)\n");
    printf("Pilih menu: ");
}

void displayMenuDokter() {
    printf("\n==== MENU DOKTER ====\n");
    printf("1. Lihat Ruangan Saya (LIHAT_RUANGAN_SAYA)\n");
    printf("2. Lihat Daftar Pasien (LIHAT_DAFTAR_PASIEN)\n");
    printf("3. Diagnosis Pasien (DIAGNOSIS)\n");
    printf("4. Ngobatin Pasien (NGOBATIN)\n");
    printf("5. Logout\n");
    printf("Pilih menu: ");
}

void displayMenuManajer() {
    printf("\n==== MENU MANAJER ====\n");
    printf("Ketikkan perintah di dalam kurung untuk menjalankan fungsi.\n");
    printf("1. Lihat Semua Antrian (LIHAT_SEMUA_ANTRIAN)\n");
    printf("2. Tambah Dokter (TAMBAH_DOKTER)\n");   
    printf("3. Assign Dokter ke Ruangan (ASSIGN_DOKTER)\n");
    printf("4. Lihat Denah Ruangan (LIHAT_DENAH)\n");
    printf("5. Lihat Ruangan (LIHAT_RUANGAN)\n");
    printf("6. Logout\n");
    printf("Pilih menu: ");
}

void displayHelp() {
    printf("\n==== BANTUAN ====\n");
    printf("- Pilih menu sesuai angka yang tersedia.\n");
    printf("- Setiap role (Pasien, Dokter, Manajer) memiliki menu berbeda.\n");
    printf("- Gunakan 'Logout' untuk keluar dari akun.\n");
    printf("- Jika ada masalah, hubungi admin rumah sakit.\n");
}

void displayStatusUser(const char* username, const char* role) {
    printf("\nHalo, %s! Anda login sebagai %s.\n", username, role);
}

