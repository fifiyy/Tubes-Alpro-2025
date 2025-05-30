#ifndef LIHAT_DENAH_H
#define LIHAT_DENAH_H

#include "../ADT/header/List_User.h"
#include "../ADT/header/Set.h"
#include "../header/Register.h"
#include "../header/Ruangan.h"
#include "Dokter.h"

void lihat_denah (ListRuangan ruangan);

void lihat_ruangan (ListRuangan *ruangan, int num, ListUser *users);

void lihat_semua_antrian(ListRuangan *ruangan,int num, ListUser *users);
#endif