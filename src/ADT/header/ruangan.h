
#ifndef RUANGAN_H
#define RUANGAN_H
#include "../header/List_User.h"
#include "Queue_Linkedlist.h"

#define MAX_PASIEN_RUANGAN 3
#define MAX_RUANGAN 100

struct Dokter;

typedef struct {
    int nomor;                          // Nomor ruangan
    int kapasitas;                      // Kapasitas ruangan
    struct Dokter *dokter;         // Pointer to dokter (NULL jika tidak ada)
    Pasien pasienDiRuangan[MAX_PASIEN_RUANGAN];
    AntrianDokter Antrian;              // Antrian pasien di ruangan
} Ruangan;

typedef struct {
    Ruangan ruang[MAX_RUANGAN];
    int jumlah; // banyak ruangan (ukuran denah, dari argumen)
} ListRuangan;

void init_ruang (ListRuangan *ruang, ListUser *users);

#endif
