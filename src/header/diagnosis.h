#ifndef DIAGNOSIS_H_
#define DIAGNOSIS_H_

#include "Penyakit.h"
#include "User.h"
#include "../../ADT/header/Queue_Linkedlist.h"
#include "../ADT/header/List_User.h"

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
static char *identifikasi_penyakit (Pasien *pasien);

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
void diagnosis_pasien(User *user_dokter);

#endif