#include <stdio.h>
#include "../header/Lihat_Denah.h"

void lihat_denah (ListRuangan ruangan) {
    if (currUser == NULL) {
        printf("\nERROR: Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    printf("\n+-----------------------------------------------+\n");
    printf("|                 DENAH RUMAH SAKIT             |\n");
    printf("+-----------------------------------------------+\n\n");
    printf("\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < ruangan.jumlah; i++) {
        printf("|  %d  ", ruangan.ruang[i].nomor);
    }
    printf("|\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");
}

void lihat_ruangan(ListRuangan *ruangan, int num, ListUser *users) {
    if (num < 1 || num > ruangan->jumlah) {
        printf("\nERROR: Nomor ruangan tidak valid.\n");
        return;
    }

    Ruangan *r = &ruangan->ruang[num - 1];

    printf("\n>> DETAIL RUANGAN %d\n", r->nomor);
    printf("    Kapasitas  : %d\n", r->kapasitas);

    // Doctor information
    if (r->dokter != NULL && strlen(r->dokter->username) > 0) {
        printf("    Dokter     : Dr. %s\n", r->dokter->username);
    } else {
        printf("    Dokter     : -\n");
    }

    // Patients in room (N terdepan dari queue)
    printf("    Pasien di dalam ruangan:\n");
    int countPasien = 0;
    address current = r->Antrian.first;
    while (current != NULL && countPasien < r->kapasitas) {
        printf("      %d. %s\n", ++countPasien, current->pasien->username);
        current = current->next;
    }
    if (countPasien == 0) {
        printf("      Tidak ada pasien di dalam ruangan saat ini.\n");
    }

    // Pasien di antrian (sisanya dari queue)
    printf("Pasien di antrian:\n");
    int counter = 1;
    while (current != NULL) {
        printf("  %d. %s\n", counter++, current->pasien->username);
        current = current->next;
    }
    if (counter == 1) {
        printf("  Tidak ada pasien di antrian saat ini.\n");
    }
    printf("------------------------------\n");
}

void lihat_ruangan_saya(ListRuangan *ruangan, ListUser *users) {
    if (currUser == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_DOKTER && currUser->role != ROLE_PASIEN) {
        printf("Hanya dokter atau pasien yang bisa melihat ruangan!\n");
        return;
    }

    Dokter *dokter = currUser->dataDokter;
    if (dokter == NULL || dokter->nomorRuangan <= 0 || dokter->nomorRuangan > ruangan->jumlah) {
        printf("Anda belum memiliki ruangan!\n");
        return;
    }

    printf("\n+-----------------------------------------------+\n");
    printf("|               RUANGAN SAYA                    |\n");
    printf("+-----------------------------------------------+\n");

    lihat_ruangan(ruangan, dokter->nomorRuangan, users);
}

void lihat_daftar_pasien(ListRuangan *ruangan, ListUser *users) {
    if (currUser == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_DOKTER) {
        printf("Hanya dokter yang bisa melihat daftar pasien!\n");
        return;
    }
    printf("\n+-----------------------------------------------+\n");
    printf("|               DAFTAR PASIEN SAYA              |\n");
    printf("+-----------------------------------------------+\n");

    Dokter *dokter = currUser->dataDokter;
    if (dokter == NULL || dokter->nomorRuangan <= 0 || dokter->nomorRuangan > ruangan->jumlah) {
        printf("Anda belum memiliki ruangan!\n");
        return;
    }

    Ruangan *r = &ruangan->ruang[dokter->nomorRuangan - 1];
    address current = r->Antrian.first;

    printf("\nDaftar Pasien di Ruangan %d:\n", r->nomor);
    int count = 0;
    while (current != NULL) {
        printf("%d. %s\n", ++count, current->pasien->username);
        current = current->next;
    }
    
    if (count == 0) {
        printf("Tidak ada pasien di ruangan ini.\n");
    }
}

void lihat_semua_antrian(ListRuangan *ruangan, int num, ListUser *users) {
    if (currUser == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER) {
        printf("Anda bukan Manajer, akses ditolak\n");
        return;
    }
    printf("\n+-----------------------------------------------+\n");
    printf("|                 SEMUA ANTRIAN                 |\n");
    printf("+-----------------------------------------------+\n");
    
    // Print room numbers header
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < ruangan->jumlah; i++) {
        printf("|  %d  ", ruangan->ruang[i].nomor);
    }
    printf("|\n");
    printf("+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");
    
    // Print details for each room
    
    for (int i = 0; i < ruangan->jumlah; i++){
        Ruangan r = ruangan->ruang[i];
        // Skip empty rooms (no doctor assigned)
        if (r.dokter == NULL || strlen(r.dokter->username) == 0) {
            continue;
        }
        printf("--- Detail Ruangan %d ---\n", ruangan->ruang[i].nomor);
        printf("Kapasitas  : %d\n", r.kapasitas);
        printf("Dokter     : Dr. %s\n", r.dokter->username);
        // Print patients in the room (N terdepan dari queue)
        printf("Pasien di dalam ruangan:\n");
        int countPasien = 0;
        address current = r.Antrian.first;
        while (current != NULL && countPasien < r.kapasitas) {
            printf("  %d. %s\n", ++countPasien, current->pasien->username);
            current = current->next;
        }
        if (countPasien == 0) {
            printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
        }
        // Print patients in queue (sisanya dari queue)
        printf("Pasien di antrian:\n");
        int counter = 1;
        while (current != NULL) {
            printf("  %d. %s\n", counter++, current->pasien->username);
            current = current->next;
        }
        if (counter == 1) {
            printf("  Tidak ada pasien di antrian saat ini.\n");
        }
        printf("\n");
    }
}