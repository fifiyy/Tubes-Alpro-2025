
#ifndef DOKTER_H
#define DOKTER_H

#include "../../ADT/header/queue_linkedlist.h"
#include "../../ADT/header/ruangan.h"

#define MAX_PASIEN_RUANGAN 3

typedef struct Dokter {
    int id;
    char username[USERNAME_LEN];
    int ruangan;
} Dokter;

Pasien *assign_pasien_ke_dokter (User *user, Dokter* dokter, Pasien* pasien, ListRuangan *ruangan);

#endif