#ifndef CHECKUP_H
#define CHECKUP_H

#include "user.h"
#include "antrian.h"

boolean validasiFloat(float nilai, const char* namaVar);
boolean validasiInt(int nilai, const char* namaVar);
void displayDokter(Dokter *dokter, int banyakDokter);
void daftarCheckUp(User *user, Dokter *dokter, int banyakDokter);

#endif