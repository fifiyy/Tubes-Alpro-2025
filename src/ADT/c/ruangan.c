#include "../header/ruangan.h"

void init_ruang (ListRuangan *ruang){
    ruang->jumlah = 8;
    for (int i = 0; i < ruang->jumlah; i++) {
        ruang->ruang[i].nomor = i + 1;
        ruang->ruang[i].kapasitas = 3;
        strcpy(ruang->ruang[i].dokter, "");
        set_create_empty(&(ruang->ruang[i].pasien));
    }
}