#include "../header/help.h"

void help_system() {
    printf("\n=========== HELP ===========\n\n");
    
    if (currUser == NULL) {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("REGISTER: Membuat akun baru\n");
    } else {
        printf("Halo %s %s. ", role_to_string(currUser->role), currUser->username);
        
        if (currUser->role == ROLE_DOKTER) {
            printf("Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
        } else if (currUser->role == ROLE_PASIEN) {
            printf("Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
        } else if (currUser->role == ROLE_MANAGER) {
            printf("Kenapa kamu memanggil command HELP? Kan kamu manager, ");
            printf("tapi yasudahlah kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
        }
    }
    
    printf("\nFootnote: \n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}
