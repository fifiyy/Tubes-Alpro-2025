#ifndef DOKTER_H
#define DOKTER_H

#include "../../ADT/header/queue_linkedlist.h"
#include "../../ADT/header/ruangan.h"

#define MAX_PASIEN_RUANGAN 3


typedef struct Dokter {
    int id;
    char username[USERNAME_LEN];
    int ruangan;
    // Pasien *pasienDiRuangan[MAX_PASIEN_RUANGAN];
    // AntrianDokter antrian; // Uncommented this since it's used in dokter.c
} Dokter;

Pasien *assignPasienKeDokter(User *user, Dokter* dokter, Pasien* pasien, ListRuangan *ruangan);

#endif