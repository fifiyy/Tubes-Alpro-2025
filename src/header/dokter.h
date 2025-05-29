#ifndef DOKTER_H
#define DOKTER_H

#include "antrian.h"

#define MAX_PASIEN_RUANGAN 3

typedef struct {
    int id;
    char ruangan;
    Pasien *pasienDiRuangan[MAX_PASIEN_RUANGAN];
    AntrianDokter antrian;
} Dokter;

/*
    Kalau jumlahPasienDiRuangan < 3, langsung masuk ke ruangan
    Tapi kalau jumlahPasienDiRuangan = 3, masuk ke antrian
*/
Pasien *assignPasienKeDokter (Dokter *dokter, Pasien *pasien);
User* getUserByIDDokter (int idDokter, ListUser *users);

#endif