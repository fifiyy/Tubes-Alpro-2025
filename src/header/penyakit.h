#ifndef PENYAKIT_H
#define PENYAKIT_H

typedef struct
{
    int id;
    char nama[20]; // Nama Penyakit
    float suhuMin, suhuMax; // Suhu
    int bpSisMin, bpSisMax, bpDiasMin, bpDiasMax; // Tekanan Darah
    int bpmMin, bpmMax; // Detak Jantung
    float satsMin, satsMax; // Saturasi Oksigen
    float bgMin, bgMax; // Kadar Gula Darah
    int tbMin, tbMax; // Tinggi Badan
    float bbMin, bbMax; // Berat Badan
    int fatMin, fatMax; // Kadar Kolestrol
    int tromMin, tromMax; // Trombosit
} Penyakit;

extern Penyakit ketPenyakit[];
extern const int jumlahPenyakit;

#endif