#ifndef ANTRIAN_SAYA_H
#define ANTRIAN_SAYA_H

#include "../header/user.h"
#include "../header/dokter.h"

void cek_antrian_saya(User *user, Dokter *dokter, ListRuangan *ruangan, int banyakDokter);
#endif