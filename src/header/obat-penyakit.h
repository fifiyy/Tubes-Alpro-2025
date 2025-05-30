#ifndef OBAT_PENYAKIT_H
#define OBAT_PENYAKIT_H

#include "obat.h"
#include "penyakit.h"
#include "boolean.h"

#define MAX_STRING_LENGTH 100
#define MAX_OBAT_PER_PENYAKIT 10
#define MAX_PENYAKIT_MAP 50

typedef struct {
    char nama_penyakit[50];             // Key: Nama penyakit (string)
    Obat obat[MAX_OBAT_PER_PENYAKIT];   // Array obat
    int jumlah_obat;                    // Jumlah obat untuk penyakit ini
} PenyakitObatEntry;

PenyakitObatEntry penyakitObatMap[] = {
    {"Influenza", {{1, "Oseltamivir"}, {2, "Vitamin C"}}, 2},
    {"COVID-19", {{3, "Remdesivir"}}, 1},
    {"Hipertensi", {{4, "Lisinopril"}}, 1},
    {"Diabetes Mellitus", {{5, "Metfomin"}, {4, "Lisinopril"}, {3, "Remdesivir"}, {2, "Vitamin C"}}, 4},
    {"Anemia", {{3, "Remdesivir"}, {2, "Vitamin C"}}, 2},
};

int totalPenyakit = 5;

#endif