#include "dokter.h"
#include "../../ADT/header/ruangan.h"
#include <stdio.h>
#include <stdlib.h>

Pasien* assignPasienKeDokter(User *user, Dokter* dokter, Pasien* pasien, ListRuangan ruangan) {
    if (dokter == NULL || pasien == NULL) {
        printf("Error: Data dokter atau pasien tidak valid\n");
        return NULL;
    }

    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (ruangan.ruang[i].pasienDiRuangan == pasien) {
            printf("Pasien sudah terdaftar di ruangan!\n");
            return NULL;
        }
    }

    address current = ruangan.ruang[dokter->ruangan].Antrian.First;
    while (current != NULL) {
        if (current->pasien->pasien_data == pasien) {
            printf("Pasien sudah berada dalam antrian!\n");
            return NULL;
        }
        current = current->next;
    }

    for (int i = 0; i < MAX_PASIEN_RUANGAN; i++) {
        if (ruangan.ruang[i].pasienDiRuangan == NULL) {
            ruangan.ruang[i].pasienDiRuangan[i] = *pasien;
            pasien->posisiAntrian = i + 1;
            pasien->id_dokter = dokter->id;
            printf("Pasien berhasil didaftarkan ke ruangan\n");
            return pasien;
        }
    }

    int jumlahSebelum = queue_size(&ruangan.ruang[dokter->ruangan].Antrian);
    queue_enqueue(&ruangan.ruang->Antrian, user);
    
    if (queue_size(&ruangan.ruang->Antrian) > jumlahSebelum) {
        pasien->posisiAntrian = ruangan.ruang[dokter->ruangan].Antrian.jumlah;
        pasien->id_dokter = dokter->id;
        printf("Pasien berhasil didaftarkan ke antrian\n");
        return pasien;
    }

    printf("Gagal mendaftarkan pasien ke antrian\n");
    return NULL;
}