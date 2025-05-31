#include <stdio.h>
#include <string.h>
#include "Minum_Penawar.h"

void minum_penawar(User *user_pasien) {
    if (currUser == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.\n");
        return;
    }
    else if (currUser->role != ROLE_PASIEN) {
        printf("Eits...pasien doang yang bisa minum penawar!\n");
        return;
    }
    Pasien *pasien = user_pasien->dataPasien;
    Stack *perutPasien = &pasien->perutPasien;

    if (stack_is_empty(*perutPasien)) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    int urutanBenar = 0;
    while (!urutanBenar && !stack_is_empty(*perutPasien)) {
        // Ambil obat terakhir dari perut (stack)
        Obat obatTerakhir;
        stack_pop(perutPasien, &obatTerakhir);

        pasien->daftarObat[pasien->jumlahObat] = obatTerakhir;
        pasien->jumlahObat++;

        printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", obatTerakhir.nama);

        // Cek urutan obat yang sudah diminum
        urutanBenar = 1;
        int n = perutPasien->idxTop + 1; // jumlah obat di perut
        for (int i = 0; i < n; i++) {
            if (strcmp(pasien->daftarObatResep[i].nama, perutPasien->buffer[i].nama) != 0) {
                urutanBenar = 0;
                break;
            }
        }

        if (!urutanBenar && !stack_is_empty(*perutPasien)) {
            printf("Urutan obat masih belum sesuai resep dokter! Muntahkan lagi satu obat...\n");
        }
    }

    if (urutanBenar) {
        printf("Urutan obat terdepan sudah sesuai resep dokter!\n");
        pasien->status = butuhMinumObat;
    }
}