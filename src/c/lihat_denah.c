#include <stdio.h>
#include "../header/lihat_denah.h"



void lihat_denah (ListRuangan ruangan) {
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
        printf("Nomor ruangan tidak valid.\n");
        return;
    }

    Ruangan *r = &ruangan->ruang[num - 1];

    printf("\n--- Detail Ruangan %d ---\n", r->nomor);
    printf("Kapasitas  : %d\n", r->kapasitas);

    // Doctor information
    if (r->dokter != NULL && strlen(r->dokter->username) > 0) {
        printf("Dokter     : Dr. %s\n", r->dokter->username);
    } else {
        printf("Dokter     : -\n");
    }

    // Patients in room (N terdepan dari queue)
    printf("Pasien di dalam ruangan:\n");
    int pasien_count = 0;
    address current = r->Antrian.First;
    while (current != NULL && pasien_count < r->kapasitas) {
        printf("  %d. %s\n", ++pasien_count, current->pasien->username);
        current = current->next;
    }
    if (pasien_count == 0) {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
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


void lihat_semua_antrian(ListRuangan *ruangan, int num, ListUser *users) {
    if (current_user == NULL) {
        printf("Anda belum login.\n");
        return;
    }

    if (current_user->role != ROLE_MANAGER) {
        printf("Anda bukan Manajer, akses ditolak\n");
        return;
    }
    
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
        int pasien_count = 0;
        address current = r.Antrian.First;
        while (current != NULL && pasien_count < r.kapasitas) {
            printf("  %d. %s\n", ++pasien_count, current->pasien->username);
            current = current->next;
        }
        if (pasien_count == 0) {
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
