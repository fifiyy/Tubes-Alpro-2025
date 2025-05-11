#include <stdio.h>
#include "../header/user.h"
#include "../header/login.h"
#include "../header/register.h"
#include "../header/logout.h"
#include "../header/lupa_password.h"
#include "../header/help.h"
#include "../header/init_data.h"
#include "../header/exit.h"
#include "../header/f10.h"
#include "../header/lihat_denah.h"

ListUser users; // Deklarasi variabel global untuk menyimpan daftar pengguna
ListRuangan ruangan;
Set usernames; // Deklarasi variabel global untuk menyimpan daftar username
Set doctor_usernames;

int main(int argc, char *argv[]) {
    init_data(&users, &usernames); // Panggil fungsi init_data
    init_ruang (&ruangan);

    char command[20];
    int nomor_ruangan;
    
    while (1) {
        printf("\n>>> ");
        if (scanf("%19s", command) != 1) {
            printf("Input tidak valid!\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (strcmp(command, "LOGIN") == 0) {
            login_system(&users);
        } else if (strcmp(command, "REGISTER") == 0) {
            register_pasien(&users, &usernames);
        } else if (strcmp(command, "LOGOUT") == 0) {
            logout_system();
        } else if (strcmp(command, "LUPA_PASSWORD") == 0) {
            lupa_password_system(&users);
        } else if (strcmp(command, "HELP") == 0) {
            help_system();
        } else if (strcmp(command, "TAMBAH_DOKTER") == 0) {
                tambah_dokter(&users, &usernames);
        } else if (strcmp(command, "ASSIGN_DOKTER") == 0) {
                assign_dokter(&users, &ruangan);
        } else if (strcmp(command, "EXIT") == 0) {
            exit_system(&users);
        } else if (strcmp(command, "LIHAT_DENAH") == 0) {
            lihat_denah(ruangan);
        } else if (strcmp(command, "LIHAT_RUANGAN") == 0) {
            printf("Masukkan nomor ruangan (1-%d): ", ruangan.jumlah);
            if (scanf("%d", &nomor_ruangan) == 1) {
                if (nomor_ruangan >= 1 && nomor_ruangan <= nomor_ruangan) {
                    lihat_ruangan(ruangan, nomor_ruangan);
                } else {
                    printf("Nomor ruangan tidak valid! (1-%d)\n", nomor_ruangan);
                }
            } else {
                printf("Input tidak valid!\n");
            }
            // while (getchar() != '\n'); // Clear input buffer
        } else {
            printf("Command tidak dikenali. Ketik HELP untuk bantuan.\n");
        }
    }
    return 0;
}
