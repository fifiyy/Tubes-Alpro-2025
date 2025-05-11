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

void lihat_ruangan (ListRuangan ruangan, int num){
    while (current_user->role != ROLE_MANAGER && current_user->role != ROLE_DOKTER 
            && current_user->role != ROLE_PASIEN) {
        printf ("Role tidak ditemukan. Akses ditolak.\n");
        return;
    }

    if (num <= 0 || num > ruangan.jumlah) {
        printf("Nomor ruangan tidak valid.\n");
        return;
    }
    
    Ruangan *r = &ruangan.ruang[num-1];
    
    printf("\n--- Detail Ruangan %d ---\n", r->nomor);
    printf("Kapasitas : %d\n", r->kapasitas);
    printf("Dokter    : %s\n", r->dokter);
    printf("Pasien di dalam ruangan:\n");

    if (r->pasien.Count == 0) {
        printf("Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        for (int i = 0; i < r->pasien.Count; i++) {
            printf("  %d. %s\n", i + 1, r->pasien.Elements[i]);
        }
    }
    printf("------------------------------\n\n");

}

