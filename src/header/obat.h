#ifndef OBAT_H
#define OBAT_H

#define MAX_OBAT 10

typedef struct AtributObat
{
    int id;
    char nama[20];    
} Obat;

typedef struct {
    Obat daftar[MAX_OBAT];
    int jumlahObat;
} DatabaseObat;

extern Obat ketObat[];

#endif