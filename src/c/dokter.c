
#include "dokter.h"
#include "../ADT/header/Ruangan.h"
#include <stdio.h>
#include <stdlib.h>

Pasien* assign_pasien_ke_dokter(User *user, Dokter* dokter, Pasien* pasien, ListRuangan *ruangan) {
    if (dokter == NULL || pasien == NULL) {
        printf("Error: Data dokter atau pasien tidak valid\n");
        return NULL;
    }

    int idx_ruang = dokter->ruangan - 1; // ruangan biasanya 1-based
    if (idx_ruang < 0 || idx_ruang >= ruangan->jumlah) {
        printf("Error: Dokter belum punya ruangan yang valid\n");
        return NULL;
    }

    // Cek apakah pasien sudah ada di queue
    address current = ruangan->ruang[idx_ruang].Antrian.first;
    while (current != NULL) {
        if (current->pasien->dataPasien == pasien) {
            printf("Pasien sudah berada dalam antrian atau ruangan!\n");
            return NULL;
        }
        current = current->next;
    }

    int jumlah_sekarang = queue_size(&ruangan->ruang[idx_ruang].Antrian);
    queue_enqueue(&ruangan->ruang[idx_ruang].Antrian, user);

    // Hitung posisi antrian setelah enqueue
    int jumlah_baru = queue_size(&ruangan->ruang[idx_ruang].Antrian);
    if (jumlah_baru > jumlah_sekarang) {
        if (jumlah_baru <= ruangan->ruang[idx_ruang].kapasitas) {
            pasien->posisiAntrian = 0; // langsung masuk ruangan
        } else {
            pasien->posisiAntrian = jumlah_baru - ruangan->ruang[idx_ruang].kapasitas;
        }
        pasien->idDokter = dokter->id;
        printf("Pasien berhasil didaftarkan ke antrian/ruangan\n");
        return pasien;
    }

    printf("Gagal mendaftarkan pasien ke antrian\n");
    return NULL;
}
