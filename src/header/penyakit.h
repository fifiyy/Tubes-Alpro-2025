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

Penyakit ketPenyakit[] = {
    {1, "Influenza", 36, 38.5, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {2, "COVID-19", 36,	39,	90,	130, 60, 85, 60, 120, 90, 100, 70, 180, 45, 90, 150, 185, 150, 240, 150, 450},
    {3, "Hipertensi", 36, 37.5, 140, 180, 90, 120, 60, 100, 90, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {4, "Diabetes Mellitus", 36, 37.5, 90, 140, 60, 90, 60, 100, 90, 100, 126, 200, 45, 90, 150, 185, 150, 240, 150, 450},
    {5, "Anemia", 36, 37, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
};

#endif