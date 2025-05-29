#ifndef OBAT_H
#define OBAT_H

typedef struct AtributObat
{
    int id;
    char nama[20];    
} Obat;

Obat ketObat[] = {
    {1, "Oseltamivir"},
    {2, "Vitamin C"},
    {3, "Remdesivir"},
    {4, "Lisinopril"},
    {5, "Metfomin"},
};

#endif