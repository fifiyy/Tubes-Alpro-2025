#ifndef DIAGNOSIS_H_
#define DIAGNOSIS_H_

#include "penyakit.h"
#include "user.h"
#include "antrian.h"
#include "../ADT/header/list_user.h"

/**
 * @brief Mengidentifikasi penyakit pasien berdasarkan gejala yang dimiliki
 * 
 * @param pasien Pointer ke struct Pasien yang akan didiagnosis
 * @return Nama penyakit pertama yang memenuhi semua kondisi atau NULL
 */
/*
    Menganalisis data pasien dan mencocokkan dengan kriteria penyakit yang ada di
    dalam database. Pakai static agar variabel disimpan di static memory dan nilainya
    tetap ada meskipun fungsi sudah selesai.
    Kriteria:
        - Mengembalikan nama penyakit PERTAMA yang memenuhi semua kondisi
        - Jika tidak ada penyakit yang cocok, return NULL
    { I.S.: Data penyakit sudah dimuat, data pasien valid, jumlah penyakit > 0 }
    { F.S.: Mengembalikan nama penyakit jika ketemu, NULL jika tidak }
*/
static char *identifikasiPenyakit (Pasien *pasien);

/**
 * @brief Melakukan proses diagnosis pasien oleh dokter
 * 
 * @param user_dokter Pointer ke struct User yang mewakili dokter yang login
 */
/*
    Melakukan diagnosa pasien berdasarkan antrian dan mencetak hasil diagnosis ke layar
    { I.S.: db terinisialisasi, nama pasien valid }
    { F.S.: Pesan diagnosis tercetak ke layar }
*/
void diagnosisPasien (User *user_dokter);

#endif