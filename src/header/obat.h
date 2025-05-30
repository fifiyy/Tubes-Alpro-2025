#ifndef OBAT_H
#define OBAT_H

typedef struct AtributObat
{
    int id;
    char nama[20];    
} Obat;

extern Obat ketObat[];
extern const int JUMLAH_OBAT;

#endif