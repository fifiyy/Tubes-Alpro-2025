#ifndef PENYAKIT_H
#define PENYAKIT_H

typedef struct
{
    int id;
    char nama[20]; // Nama Penyakit
    float suhu_min, suhu_max; // Suhu
    int bp_sis_min, bp_sis_max, bp_dias_min, bp_dias_max; // Tekanan Darah
    int bpm_min, bpm_max; // Detak Jantung
    float sats_min, sats_max; // Saturasi Oksigen
    float bg_min, bg_max; // Kadar Gula Darah
    float bb_min, bb_max; // Tinggi Badan
    int tb_min, tb_max; // Berat Badan
    int fat_min, fat_max; // Kadar Kolestrol
    int trom_min, trom_max; // Trombosit
} Penyakit;

extern Penyakit ketPenyakit[];
extern const int jumlahPenyakit;

#endif