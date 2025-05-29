#ifndef PASIEN_H
#define PASIEN_H

#include "boolean.h"
#include "obat.h"

#define MAX_OBAT 10
#define MAX_PENYAKIT 20
#define MAX_KELUHAN 51

typedef enum {
    statusDiagnosa,
    statusDiberiObat,
    statusMinumObat,
    statusSembuh,
    statusPulang
} StatusPasien;

// unsigned int digunakan untuk variabel yang tidak pernah bernilai negatif
typedef struct {
    int id;
    char penyakit[MAX_PENYAKIT];
    float suhu;
    float beratBadan; // kg
    int tinggiBadan; // cm
    int tekananDarah[2]; // [sistol, diastol]
    unsigned int detakJantung;
    float saturasiOksigen; 
    int kadarGulaDarah;
    unsigned int kadarKolesterol;
    unsigned int trombosit;
    char keluhan[MAX_KELUHAN];
    Obat daftarObat[MAX_OBAT];
    Obat perutPasien[MAX_OBAT];
    int jumlahObat;
    StatusPasien status;
    int id_dokter;
    int posisiAntrian;
} Pasien;

#endif