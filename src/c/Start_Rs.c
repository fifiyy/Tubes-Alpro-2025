#include <stdio.h>
#include "../header/Display.h"
#include "../header/User.h"
#include "../header/Login.h"
#include "../header/Register.h"
#include "../header/Logout.h"
#include "../header/Lupa_Password.h"
#include "../header/Help.h"
#include "../header/Init_Data.h"
#include "../header/Exit.h"
#include "../header/F10.h"
#include "../header/Lihat_Denah.h"
#include "../header/Daftar_Check_Up.h"
#include "../header/Diagnosis.h"
#include "../header/Ngobatin.h"
#include "../header/Antrian_Saya.h"
#include "../header/Minum_Obat.h"
#include "../header/Minum_Penawar.h"
#include "Pulangdok.h"
#include "Lihat_User.h"
#include "Cari_User.h"
#include "Mainin_Antrian.h"

ListUser users;
ListRuangan ruangan;
Set usernames;
Set doctor_usernames;
extern User *currUser;

void run_rs() {
    init_data(&users, &usernames);
    init_ruang(&ruangan, &users);
    currUser = NULL;

    char command[20];
    int nomor_ruangan;

    while (1) {
        // Tampilkan menu sesuai role
        if (currUser == NULL) {
            display_main_menu();
            printf("\n>>> ");
        } else if (currUser->role == ROLE_PASIEN) {
            display_status_user(currUser->username, &(currUser->role));
            if (currUser != NULL && currUser->role == ROLE_PASIEN && currUser->dataPasien->sisaNyawa <= 0) {
            printf("Game over.. Pasien dinyatakan Ded dan dikeluarkan dari rumah sakit. RIP o7\n");
            int idRuangan = currUser->dataPasien->idRuangan;
            if (idRuangan > 0) {
                queue_dequeue(&ruangan.ruang[idRuangan - 1].Antrian);
                currUser->dataPasien->status = meninggalDunia;
                currUser = NULL; // Set dataPasien ke NULL agar tidak ada akses ke data yang sudah dihapus
                display_main_menu();
            }
        }
            printf("\n>>> ");
        } else if (currUser->role == ROLE_DOKTER) {
            display_status_user(currUser->username, &(currUser->role));
            // display_menu_dokter();
            printf("\n>>> ");
        } else if (currUser->role == ROLE_MANAGER) {
            display_status_user(currUser->username, &(currUser->role));
            // display_menu_manajer();
            printf("\n>>> ");
        }

        // printf("\n>>> ");
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
        } else if (strcmp(command, "LIHAT_USER") == 0) {
            lihat_user(users);
        } else if (strcmp(command, "LIHAT_PASIEN") == 0) {
            lihat_pasien(users);
        } else if (strcmp(command, "LIHAT_DOKTER") == 0) {
            lihat_dokter(users);
        } else if (strcmp(command, "CARI_USER") == 0) {
            cari_user(users);
        } else if (strcmp(command, "CARI_PASIEN") == 0) {
            cari_pasien(users);
        } else if (strcmp(command, "CARI_DOKTER") == 0) {
            cari_dokter(users);

        } else if (strcmp(command, "EXIT") == 0) {
            exit_system(&users);
        } else if (strcmp(command, "LIHAT_DENAH") == 0) {
            lihat_denah(ruangan);
        } else if (strcmp(command, "LIHAT_SEMUA_ANTRIAN") == 0) {
                lihat_semua_antrian(&ruangan, ruangan.jumlah, &users);
        } else if (strcmp(command, "LIHAT_RUANGAN") == 0) {
            printf("Masukkan nomor ruangan (1-%d): ", ruangan.jumlah);
            if (scanf("%d", &nomor_ruangan) == 1) {
                if (nomor_ruangan >= 1 && nomor_ruangan <= ruangan.jumlah) {
                    lihat_ruangan(&ruangan, nomor_ruangan, &users);
                } else {
                    printf("Nomor ruangan tidak valid! (1-%d)\n", ruangan.jumlah);
                }
            } else {
                printf("Input tidak valid!\n");
            }
        } else if (strcmp(command, "DAFTAR_CHECKUP") == 0) {
            daftar_check_up(currUser, users.data, users.length, &ruangan);
        } else if (strcmp(command, "LIHAT_RUANGAN_SAYA") == 0) {
            lihat_ruangan_saya(&ruangan, &users);
        } else if (strcmp(command, "LIHAT_DAFTAR_PASIEN") == 0) {
            lihat_daftar_pasien(&ruangan, &users);
        } else if (strcmp(command, "DIAGNOSIS") == 0) {
            diagnosis_pasien(currUser);
        } else if (strcmp(command, "NGOBATIN") == 0) {
            ngobatin(currUser, users.data, users.length, &ruangan);
        } else if (strcmp(command,"LIHAT_ANTRIAN") == 0) {
                cek_antrian_saya(currUser, users.data, &ruangan, users.length);
        } else if (strcmp(command, "MINUM_OBAT") == 0) {
                minum_obat(currUser);
        } else if (strcmp(command, "MINUM_PENAWAR") == 0) {
            minum_penawar(currUser);
        } else if (strcmp(command, "PULANG") == 0) {
            pulangdok(currUser, &ruangan);
        } else if (strcmp(command, "SKIP_ANTRIAN") == 0) {
            skip_antrian(currUser, &ruangan, users.length);
        } else {
            printf("Command tidak dikenali. Ketik HELP untuk bantuan.\n");
        }
    }
    return; 
}