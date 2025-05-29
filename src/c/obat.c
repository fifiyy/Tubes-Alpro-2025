#include "obat.h"

void initObat (DatabaseObat *dbO) {
    Obat obat1 = {.id = 1, .nama = "Oseltamivir"};
    dbO->daftar[0] = obat1;

    Obat obat2 = {.id = 2, .nama = "Vitamin C"};
    dbO->daftar[1] = obat2;

    Obat obat3 = {.id = 3, .nama = "Remdesivir"};
    dbO->daftar[2] = obat3;

    Obat obat4 = {.id = 4, .nama = "Lisinopril"};
    dbO->daftar[3] = obat4;

    Obat obat5 = {.id = 5, .nama = "Metfomin"};
    dbO->daftar[4] = obat5;

    dbO->jumlahObat = 5;
}