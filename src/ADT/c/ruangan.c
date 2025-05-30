#include "../header/Ruangan.h"
#include "../header/Dokter.h"

void init_ruang (ListRuangan *ruang, ListUser *users) {
    ruang->jumlah = 8; // contoh, 8 ruangan

    // Cari dokter dari daftar user
    Dokter *dokter_terpilih = NULL;

    for (int i = 0; i < list_nb_elmt(*users); i++) {
        if (users->data[i].role == ROLE_DOKTER && users->data[i].dataDokter == NULL) {
            // skip warning debug
        }
    }

    for (int i = 0; i < list_nb_elmt(*users); i++) {
        if (users->data[i].role == ROLE_DOKTER && users->data[i].dataDokter != NULL) {
            dokter_terpilih = users->data[i].dataDokter;
            break; // Ambil dokter pertama yang ditemukan
        }
    }

    if (dokter_terpilih == NULL) {
        printf("Tidak ada dokter ditemukan!\n");
        return;
    }

    // Isi data ruangan
    ruang->ruang[0].nomor = 1;
    ruang->ruang[0].kapasitas = MAX_PASIEN_RUANGAN;
    ruang->ruang[0].dokter = dokter_terpilih;  // ✅ Assign pointer dokter yang sudah ada
    dokter_terpilih->ruangan = 1;
    queue_init(&ruang->ruang[0].Antrian);

    for (int i = 1; i < ruang->jumlah; i++) {
        ruang->ruang[i].nomor = i + 1; // Nomor ruangan dimulai dari 2
        ruang->ruang[i].kapasitas = MAX_PASIEN_RUANGAN;
        ruang->ruang[i].dokter = NULL; // Ruangan lain belum ada dokter
        queue_init(&ruang->ruang[i].Antrian);
    }

    // Inisialisasi pasien di ruangan (hanya lewat queue, tidak perlu array manual)
    queue_enqueue(&ruang->ruang[0].Antrian, &users->data[2]); // Misal pasien GRO
    users->data[2].dataPasien->idDokter = dokter_terpilih->id;
    users->data[2].dataPasien->posisiAntrian = 0;
    queue_enqueue(&ruang->ruang[0].Antrian, &users->data[3]); // Misal pasien nimonsganteng
    users->data[3].dataPasien->idDokter = dokter_terpilih->id;
    users->data[3].dataPasien->posisiAntrian = 0;
}