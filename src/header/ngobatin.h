#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "obat_penyakit.h"

PenyakitObatEntry* cari_obat (const char *namaPenyakit);

void ngobatin (User *currUser, User *users, int banyakUser, ListRuangan *ruangan);

#endif