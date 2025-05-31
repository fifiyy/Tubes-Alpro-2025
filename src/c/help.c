#include "../header/Help.h"

void help_system() {
    printf("\n=========== HELP ===========\n\n");
    
    if (currUser == NULL) {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("REGISTER: Membuat akun baru\n");
        printf("LUPA_PASSWORD: Mengatur ulang password akun\n");
    } else {
        printf("Halo %s %s. ", role_to_string(currUser->role), currUser->username);
        
        if (currUser->role == ROLE_DOKTER) {
            printf("Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("LUPA_PASSWORD: Mengatur ulang password akun\n");
            printf("LIHAT_DENAH: Melihat denah ruangan rumah sakit\n");
            printf("LIHAT_RUANGAN: Melihat ruangan sesuai nomor ruangan yang dipilih\n");
            printf("LIHAT_RUANGAN_SAYA: Melihat ruangan tempatmu ditugaskan\n");
            printf("LIHAT_DAFTAR_PASIEN: Melihat daftar pasien yang sedang menunggu\n");
            printf("DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
            printf("NGOBATIN: Mengobati pasien yang sudah didiagnosis\n");
            printf("EXIT: Keluar dari aplikasi\n");

        } else if (currUser->role == ROLE_PASIEN) {
            printf("Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("LUPA_PASSWORD: Mengatur ulang password akun\n");
            printf("LIHAT_DENAH: Melihat denah ruangan rumah sakit\n");
            printf("LIHAT_RUANGAN: Melihat ruangan sesuai nomor ruangan yang dipilih\n");
            printf("LIHAT_RUANGAN_SAYA: Melihat ruangan tempatmu akan diobati\n");
            printf("DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
            printf("ANTRIAN_SAYA: Melihat posisi antrian check-up\n");
            printf("MINUM_OBAT: Minum obat sesuai resep dokter\n");
            printf("MINUM_PENAWAR: Minum penawar jika urutan obat salah\n");
            printf("PULANG: Pulang dari rumah sakit setelah selesai berobat\n");
            printf("EXIT: Keluar dari aplikasi\n");

        } else if (currUser->role == ROLE_MANAGER) {
            printf("Kenapa kamu memanggil command HELP? Kan kamu manager, ");
            printf("tapi yasudahlah kamu pasti sedang kebingungan.\n");
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("LUPA_PASSWORD: Mengatur ulang password akun\n");
            printf("LIHAT_DENAH: Melihat denah ruangan rumah sakit\n");
            printf("LIHAT_SEMUA_ANTRIAN: Melihat semua antrian pasien di setiap ruangan\n");
            printf("LIHAT_RUANGAN: Melihat ruangan sesuai nomor ruangan yang dipilih\n");
            printf("TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
            printf("ASSIGN_DOKTER: Menugaskan dokter ke ruangan tertentu\n");
        }
    }
    
    printf("\nFootnote: \n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}
