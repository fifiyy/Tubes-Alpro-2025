#ifndef PASIEN_H
#define PASIEN_H

#include "boolean.h"
#include "obat.h"
#include "../ADT/header/Stack.h"

#define MAX_PENYAKIT 20
// #define MAX_KELUHAN 51

typedef enum {
    butuhCheckup,
    butuhDiagnosa,
    butuhDiberiObat,
    butuhMinumObat,
    butuhPenawar,
    butuhPulang,
    meninggalDunia
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
    // char keluhan[MAX_KELUHAN];
    Obat daftarObat[MAX_OBAT];
    Obat daftarObatResep[MAX_OBAT];
    Stack perutPasien;
    int jumlahObat;
    int jumlahObatResep;
    StatusPasien status;
    int idRuangan;
    int posisiAntrian;
    int sisaNyawa;
} Pasien;

#endif