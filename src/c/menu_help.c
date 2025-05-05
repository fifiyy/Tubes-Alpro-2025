#include <stdio.h>
#include <string.h>
#include "menu_help.h"

void tampilkanHelp(bool isLoggedIn, const char* role, const char* username) {
    printf("\n=========== HELP ===========\n\n");

    if (!isLoggedIn) {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("REGISTER: Membuat akun baru\n");
    } else if (strcmp(role, "dokter") == 0) {
        printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", username);
        printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
        printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("DIAGNOSIS: Melakukan diagnosis penyakit pasien\n");
        // Tambahkan fitur lain sesuai kebutuhan
    } else if (strcmp(role, "pasien") == 0) {
        printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", username);
        printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
        printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("DAFTAR_CHECKUP: Mendaftarkan diri untuk check-up\n");
        // Tambahkan fitur lain sesuai kebutuhan
    } else if (strcmp(role, "manager") == 0) {
        printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan.\n", username);
        printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
        printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
        printf("TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
        // Tambahkan fitur lain sesuai kebutuhan
    }

    printf("\nFootnote:\n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}

void tampilkanMenu(bool isLoggedIn, const char* role) {
    printf("\n=========== MENU ===========\n\n");

    if (!isLoggedIn) {
        printf("LOGIN\nREGISTER\n");
    } else if (strcmp(role, "dokter") == 0) {
        printf("LOGOUT\nDIAGNOSIS\n");
        // Tambahkan menu dokter lain jika ada
    } else if (strcmp(role, "pasien") == 0) {
        printf("LOGOUT\nDAFTAR_CHECKUP\n");
        // Tambahkan menu pasien lain jika ada
    } else if (strcmp(role, "manager") == 0) {
        printf("LOGOUT\nTAMBAH_DOKTER\n");
        // Tambahkan menu manager lain jika ada
    }
}
