#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "Obat_Penyakit.h"
#include "../../ADT/header/Ruangan.h"
#include "User.h"

PenyakitObatEntry* cari_obat (const char *namaPenyakit);

void ngobatin (User *currUser, User *users, int banyakUser, ListRuangan *ruangan);

#endif