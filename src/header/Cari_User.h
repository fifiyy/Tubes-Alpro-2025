#ifndef CARI_USER_H
#define CARI_USER_H

#include <stdio.h>
#include <string.h>
#include "../ADT/header/list_user.h"
#include "../header/user.h"
#include "../header/pasien.h"
#include "../header/lihat_user.h"

int binary_search (ListUser L, int targetElement, int size);
int sequential_username (ListUser L, char* targetName, int size);
void search_penyakit (ListUser L, const char* targetPenyakit);
void cari_user (ListUser L);
void cari_pasien (ListUser L);
void cari_dokter(ListUser L);

#endif