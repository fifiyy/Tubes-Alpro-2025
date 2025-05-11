#ifndef RUANGAN_H
#define RUANGAN_H
#include "../header/list_user.h"
#include "../header/set.h"

#define MAX_PASIEN_PER_RUANGAN 10
#define MAX_RUANGAN 100

typedef struct {
    int nomor;                          // Nomor ruangan
    int kapasitas;                      // Kapasitas ruangan
    char dokter[USERNAME_LEN];         // Nama dokter ("" jika tidak ada)
    Set pasien;                        // Set pasien
} Ruangan;

typedef struct {
    Ruangan ruang[MAX_RUANGAN];
    int jumlah; // banyak ruangan (ukuran denah, dari argumen)
} ListRuangan;

void init_ruang (ListRuangan *ruang);

#endif