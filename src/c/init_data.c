#include "Init_Data.h"

// Inisialisasi array obat
Obat ketObat[] = {
    {1, "Oseltamivir"},
    {2, "Vitamin C"},
    {3, "Remdesivir"},
    {4, "Lisinopril"},
    {5, "Metfomin"},
    {6, "Amoxicillin"},
    {7, "Ibuprofen"},
    {8, "Paracetamol"},
    {9, "Amlodipine"},
};
const int jumlahObat = sizeof(ketObat) / sizeof(ketObat[0]);

// Inisialisasi array penyakit
Penyakit ketPenyakit[] = {
    {1, "Influenza", 36, 38.5, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {2, "COVID-19", 36, 39, 90, 130, 60, 85, 60, 120, 90, 100, 70, 180, 45, 90, 150, 185, 150, 240, 150, 450},
    {3, "Hipertensi", 36, 37.5, 140, 180, 90, 120, 60, 100, 90, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {4, "Diabetes Mellitus", 36, 37.5, 90, 140, 60, 90, 60, 100, 90, 100, 126, 200, 45, 90, 150, 185, 150, 240, 150, 450},
    {5, "Anemia", 36, 37, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {6, "Tonsilitis", 36, 38, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {7, "Demam Berdarah", 36, 39, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {8, "Pneumonia", 36, 39, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    // Penyakit dengan 4 obat:
    {9, "Infeksi Parah", 36, 40, 90, 140, 60, 100, 60, 120, 90, 110, 70, 180, 45, 90, 150, 185, 150, 240, 150, 450},
};
const int jumlahPenyakit = sizeof(ketPenyakit) / sizeof(ketPenyakit[0]);

PenyakitObatEntry penyakitObatMap[] = {
    {"Influenza", {{1, "Oseltamivir"}, {2, "Vitamin C"}}, 2},
    {"COVID-19", {{3, "Remdesivir"}}, 1},
    {"Hipertensi", {{4, "Lisinopril"}}, 1},
    {"Diabetes Mellitus", {{5, "Metfomin"}}, 1},
    {"Anemia", {{2, "Vitamin C"}}, 1},
    {"Tonsilitis", {{6, "Amoxicillin"}, {2, "Vitamin C"}}, 2},
    {"Demam Berdarah", {{2, "Vitamin C"}, {7, "Ibuprofen"}}, 2},
    {"Pneumonia", {{6, "Amoxicillin"}, {8, "Paracetamol"}}, 2},
    {"Infeksi Parah", {{6, "Amoxicillin"}, {2, "Vitamin C"}, {7, "Ibuprofen"}, {9, "Amlodipine"}}, 4},
};

const int jumlahPenyakitObat = sizeof(penyakitObatMap) / sizeof(penyakitObatMap[0]);

void init_data(ListUser *users, Set *usernames) {
    list_make_empty(users);
    set_create_empty(usernames); // Inisialisasi set

    // Tambahkan pengguna awal ke ListUser dan Set
    list_set_el(users, 0, (User){"a", "a", ROLE_MANAGER});
    set_insert(usernames, "a");
    
    // Initialize doctor
    User dokter_user = {"NEROIFA", "NEROIFA123", ROLE_DOKTER,1};
    dokter_user.dataDokter = (Dokter*) malloc(sizeof(Dokter));
    dokter_user.dataDokter->id = 1;
    strcpy(dokter_user.dataDokter->username, dokter_user.username); // Pastikan username dokter terisi
    dokter_user.dataDokter->nomorRuangan = -1; // Belum memiliki ruangan
    list_set_el(users, 1, dokter_user);
    set_insert(usernames, "NEROIFA");

    // Inisialisasi pasien "GRO"
    User pasien_gro = {"GRO", "NEROIFACANTIK", ROLE_PASIEN,2};
    pasien_gro.dataPasien = (Pasien*) malloc(sizeof(Pasien));
    pasien_gro.dataPasien->id = 2;
    pasien_gro.dataPasien->posisiAntrian = -1;
    pasien_gro.dataPasien->status = butuhDiagnosa; // Sudah didiagnosa
    pasien_gro.dataPasien->jumlahObat = 0;
    pasien_gro.dataPasien->idRuangan = -1;
    pasien_gro.dataPasien->sisaNyawa = 3;
    // Data Medis
    pasien_gro.dataPasien->suhu = 39.5;
    pasien_gro.dataPasien->tekananDarah[0] = 135;
    pasien_gro.dataPasien->tekananDarah[1] = 95;
    pasien_gro.dataPasien->detakJantung = 110;
    pasien_gro.dataPasien->saturasiOksigen = 92;
    pasien_gro.dataPasien->kadarGulaDarah = 115;
    pasien_gro.dataPasien->beratBadan = 80;
    pasien_gro.dataPasien->tinggiBadan = 160;
    pasien_gro.dataPasien->kadarKolesterol = 170;
    pasien_gro.dataPasien->trombosit = 200;
    list_set_el(users, 2, pasien_gro);
    set_insert(usernames, "GRO");
    create_stack(&pasien_gro.dataPasien->perutPasien);

    // Inisialisasi pasien "nimonsganteng"
    User pasien_nimons = {"nimonssganteng", "KelompokAmatGacor", ROLE_PASIEN,3};
    pasien_nimons.dataPasien = (Pasien*) malloc(sizeof(Pasien));
    pasien_nimons.dataPasien->id = 3;
    pasien_nimons.dataPasien->posisiAntrian = -1;
    pasien_nimons.dataPasien->status = butuhDiagnosa;
    pasien_nimons.dataPasien->jumlahObat = 0;
    pasien_nimons.dataPasien->idRuangan = -1;
    pasien_nimons.dataPasien->sisaNyawa = 3;
    // Data Medis
    pasien_nimons.dataPasien->suhu = 36.8;
    pasien_nimons.dataPasien->tekananDarah[0] = 150;
    pasien_nimons.dataPasien->tekananDarah[1] = 100;
    pasien_nimons.dataPasien->detakJantung = 85;
    pasien_nimons.dataPasien->saturasiOksigen = 97;
    pasien_nimons.dataPasien->kadarGulaDarah = 100;
    pasien_nimons.dataPasien->beratBadan = 65;
    pasien_nimons.dataPasien->tinggiBadan = 175;
    pasien_nimons.dataPasien->kadarKolesterol = 200;
    pasien_nimons.dataPasien->trombosit = 300;
    list_set_el(users, 3, pasien_nimons);
    set_insert(usernames, "nimonsganteng");
    create_stack(&pasien_nimons.dataPasien->perutPasien); // Inisialisasi stack perut pasien

    list_set_length(users, 4);
}