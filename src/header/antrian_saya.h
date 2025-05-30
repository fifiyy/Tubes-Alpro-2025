#ifndef ANTRIAN_SAYA_H
#define ANTRIAN_SAYA_H

#include "user.h"
#include "dokter.h"
#include "../ADT/header/ruangan.h"


void cek_antrian_saya(User *user, User *users, ListRuangan *ruangan, int banyakUser);

#endif