#include <stdio.h>
#include <string.h>
#include "../header/Minum_Obat.h"

void minum_obat(User *user_pasien) {
    if (user_pasien == NULL) {
        printf("Kamu belum login. Silakan login terlebih dahulu dengan command LOGIN.");
        return;
    }

    if (user_pasien->role != ROLE_PASIEN) {
        printf("Eits...pasien doang yang bisa minum obat!\n");
        return;
    }

    Pasien *pasien =    (user_pasien->dataPasien);

    if (pasien->status != butuhMinumObat) {
        printf("Yuk minum obatmu dulu..\n");
        return;
    }

    while (pasien->jumlahObat > 0) {
        // printf("\n>>> MINUM_OBAT\n\n");
        printf("============ DAFTAR OBAT ============\n");
        for (int i = 0; i < pasien->jumlahObat; i++) {
            printf("%d. %s\n", i + 1, pasien->daftarObat[i].nama);
        }

        printf("\nPilih obat untuk diminum: ");
        int pilihan;
        scanf("%d", &pilihan);

        if (pilihan < 1 || pilihan > pasien->jumlahObat) {
            printf("\nObatnya gak diresepkan buat kamu!\n");
            continue;  //minta input lagi
        }

        int idx = pilihan - 1;

        pasien->perutPasien[pasien->jumlahObat - 1] = pasien->daftarObat[idx];

        printf("\nGLEKGLEKGLEK... %s berhasil diminum!!!\n", pasien->daftarObat[idx].nama);
        // hapusObat(pasien);

        if (pasien->jumlahObat == 0) {
            pasien->status = butuhSembuh;
            printf("\nSemua obat telah diminum. Kamu akan mulai proses penyembuhan...\n");
            break;
        }
    }
}
