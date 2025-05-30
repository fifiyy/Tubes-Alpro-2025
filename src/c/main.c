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
// #include "../header/Minum_Obat.h"

ListUser users; // Deklarasi variabel global untuk menyimpan daftar pengguna
ListRuangan ruangan;
Set usernames; // Deklarasi variabel global untuk menyimpan daftar username
Set doctor_usernames;

int main(int argc, char *argv[]) {
    // displayMainMenu(); //display utama sebelum login atau register
    init_data(&users, &usernames); // Panggil fungsi init_data
    init_ruang (&ruangan, &users); // Inisialisasi ruangan
    currUser = NULL; // Inisialisasi pointer currUser ke NULL

    char command[20];
    int nomor_ruangan;
    
    while (1) {
        // Tampilkan menu sesuai role
        if (currUser == NULL) {
            display_main_menu();
            printf("\n>>> ");
        } else if (currUser->role == ROLE_PASIEN) {
            display_status_user(currUser->username, "Pasien");
            display_menu_pasien();
            printf("\n>>> ");
        } else if (currUser->role == ROLE_DOKTER) {
            display_status_user(currUser->username, "Dokter");
            display_menu_dokter();
            printf("\n>>> ");
        } else if (currUser->role == ROLE_MANAGER) {
            display_status_user(currUser->username, "Manajer");
            display_menu_manajer();
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
        } else if (strcmp(command, "EXIT") == 0) {
            exit_system(&users);
        } else if (strcmp(command, "LIHAT_DENAH") == 0) {
            lihat_denah(ruangan);
        } else if (strcmp(command, "LIHAT_SEMUA_ANTRIAN") == 0) {
                lihat_semua_antrian(&ruangan, ruangan.jumlah, &users);
        } else if (strcmp(command, "LIHAT_RUANGAN") == 0) {
            printf("Masukkan nomor ruangan (1-%d): ", ruangan.jumlah);
            if (scanf("%d", &nomor_ruangan) == 1) {
                if (nomor_ruangan >= 1 && nomor_ruangan <= nomor_ruangan) {
                    lihat_ruangan(&ruangan, nomor_ruangan, &users);
                } else {
                    printf("Nomor ruangan tidak valid! (1-%d)\n", nomor_ruangan);
                }
            } else {
                printf("Input tidak valid!\n");
            }
            // while (getchar() != '\n'); // Clear input buffer
        } else if (strcmp(command, "DAFTAR_CHECKUP") == 0) {
            daftar_check_up(currUser, users.data, users.length, &ruangan);
        } else if (strcmp(command, "LIHAT_RUANGAN_SAYA") == 0) {
            if (currUser && currUser->role == ROLE_DOKTER) {
                if (currUser->dataDokter->ruangan <= 0) {
                    printf("Anda belum memiliki ruangan!\n");
                    continue;
                }
                lihat_ruangan(&ruangan, currUser->dataDokter->ruangan, &users);

            } else {
                printf("Hanya dokter yang bisa melihat ruangan sendiri!\n");
            }
        } else if (strcmp(command, "LIHAT_DAFTAR_PASIEN") == 0) {
            if (currUser && currUser->role == ROLE_DOKTER) {
                // Tampilkan semua pasien di ruangan dokter (baik di ruangan maupun antrian)
                int idx_ruang = currUser->dataDokter->ruangan - 1;
                if (idx_ruang < 0 || idx_ruang >= ruangan.jumlah) {
                    printf("Anda belum memiliki ruangan!\n");
                } else {
                    Ruangan *r = &ruangan.ruang[idx_ruang];
                    printf("\n--- Daftar Pasien di Ruangan %d ---\n", r->nomor);
                    int pasien_count = 0;
                    address current = r->Antrian.first;
                    while (current != NULL) {
                        printf("%d. %s\n", ++pasien_count, current->pasien->username);
                        current = current->next;
                    }
                    if (pasien_count == 0) printf("Belum ada pasien di ruangan/antrian.\n");
                    printf("------------------------------\n");
                }
            } else {
                printf("Hanya dokter yang bisa melihat daftar pasien!\n");
            }
        } else if (strcmp(command, "DIAGNOSIS") == 0) {
            diagnosis_pasien(currUser);
        } else if (strcmp(command, "NGOBATIN") == 0) {
            ngobatin(currUser, users.data, users.length, &ruangan);
        } else if (strcmp(command,"LIHAT_ANTRIAN") == 0) {
            if (currUser->role != ROLE_PASIEN) {
                printf("Hanya pasien yang bisa melihat antrian!\n");
            } else {
                cek_antrian_saya(currUser, users.data, &ruangan, users.length);
            }
        // } else if (strcmp(command, "MINUM_OBAT") == 0) {
        //     if (currUser->role != ROLE_PASIEN) {
        //         printf("Hanya pasien yang bisa minum obat!\n");
        //     } else {
        //         minum_obat(currUser);
        //     }
        } else {
            printf("Command tidak dikenali. Ketik HELP untuk bantuan.\n");
        }
    }
    return 0; 
}