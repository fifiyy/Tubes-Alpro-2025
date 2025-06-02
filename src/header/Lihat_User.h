#ifndef LIHAT_USER_H
#define LIHAT_USER_H

#include <stdio.h>
#include <string.h>
#include "../ADT/header/list_user.h"
#include "user.h"
#include "pasien.h"

char to_lower(char c);
int compare_nama (char *a, char *b);
void sort_user (ListUser L, int idx[], int len, int id, int asc);
void print_user (ListUser L, int idx [],int len, int view);
void lihat_user (ListUser L);
void lihat_pasien (ListUser L);
void lihat_dokter (ListUser L);

#endif