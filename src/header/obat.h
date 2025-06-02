#ifndef OBAT_H
#define OBAT_H

#define MAX_OBAT 10

typedef struct AtributObat
{
    int id;
    char nama[20];    
} Obat;

extern Obat ketObat[];
extern const int jumlahObat;

#endif