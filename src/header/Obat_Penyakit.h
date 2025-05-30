#ifndef OBAT_PENYAKIT_H
#define OBAT_PENYAKIT_H

#include "Obat.h"
#include "Penyakit.h"
#include "Boolean.h"

#define MAX_STRING_LENGTH 100
#define MAX_OBAT_PER_PENYAKIT 10
#define MAX_PENYAKIT_MAP 50

typedef struct {
    char namaPenyakit[50];             // Key: Nama penyakit (string)
    Obat obat[MAX_OBAT_PER_PENYAKIT];   // Array obat
    int jumlahObat;                    // Jumlah obat untuk penyakit ini
} PenyakitObatEntry;

extern PenyakitObatEntry penyakitObatMap[];

#endif