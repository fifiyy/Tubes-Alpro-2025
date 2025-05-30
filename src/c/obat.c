#include "../header/obat.h"

Obat ketObat[] = {
    {1, "Oseltamivir"},
    {2, "Vitamin C"},
    {3, "Remdesivir"},
    {4, "Lisinopril"},
    {5, "Metfomin"},
};

void initObat (DatabaseObat *dbO) {
    for (int i = 0; i < 5; i++) {
        dbO->daftar[i] = ketObat[i];
    }
    dbO->jumlahObat = 5;
}