#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "user.h"
#include "obat-penyakit.h"

PenyakitObatEntry* cariObat(const char *nama_penyakit);

void ngobatin(User *user_dokter);

#endif