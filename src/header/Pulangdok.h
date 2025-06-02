
#ifndef PULANGDOK_H
#define PULANGDOK_H

#include "boolean.h"
#include "obat.h"
#include "Obat_Penyakit.h"
#include "pasien.h"
#include "../ADT/header/Queue_Linkedlist.h"
#include "../ADT/header/Ruangan.h"

void make_default_pasien(Pasien *pasien);

void pulangdok(User *user_pasien, ListRuangan *listRuangan);

#endif
