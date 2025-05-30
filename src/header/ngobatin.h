#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "user.h"
#include "obat-penyakit.h"

PenyakitObatEntry* cari_obat(const char *namaPenyakit);

void ngobatin (User *currUser, User *users, int banyakUser, ListRuangan *ruangan);

#endif