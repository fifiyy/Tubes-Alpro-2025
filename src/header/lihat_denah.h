#ifndef LIHAT_DENAH_H
#define LIHAT_DENAH_H

#include "../ADT/header/list_user.h"
#include "../ADT/header/set.h"
#include "../header/register.h"
#include "../header/ruangan.h"
#include "dokter.h"

void lihat_denah (ListRuangan ruangan);

void lihat_ruangan (ListRuangan *ruangan, int num, ListUser *users);

void lihat_semua_antrian(ListRuangan *ruangan,int num, ListUser *users);
#endif
