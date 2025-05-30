#include "init_data.h"

// Inisialisasi array obat
Obat ketObat[] = {
    {1, "Oseltamivir"},
    {2, "Vitamin C"},
    {3, "Remdesivir"},
    {4, "Lisinopril"},
    {5, "Metfomin"},
};
const int jumlahObat = sizeof(ketObat) / sizeof(ketObat[0]);

// Inisialisasi array penyakit
Penyakit ketPenyakit[] = {
    {1, "Influenza", 36, 38.5, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {2, "COVID-19", 36, 39, 90, 130, 60, 85, 60, 120, 90, 100, 70, 180, 45, 90, 150, 185, 150, 240, 150, 450},
    {3, "Hipertensi", 36, 37.5, 140, 180, 90, 120, 60, 100, 90, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {4, "Diabetes Mellitus", 36, 37.5, 90, 140, 60, 90, 60, 100, 90, 100, 126, 200, 45, 90, 150, 185, 150, 240, 150, 450},
    {5, "Anemia", 36, 37, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
};
const int jumlahPenyakit = sizeof(ketPenyakit) / sizeof(ketPenyakit[0]);

// Inisialisasi map penyakit-obat
PenyakitObatEntry penyakitObatMap[] = {
    {"Influenza", {{1, "Oseltamivir"}, {2, "Vitamin C"}}, 2},
    {"COVID-19", {{3, "Remdesivir"}}, 1},
    {"Hipertensi", {{4, "Lisinopril"}}, 1},
    {"Diabetes Mellitus", {{5, "Metfomin"}}, 1},
    {"Anemia", {{2, "Vitamin C"}}, 1},
};

void init_data(ListUser *users, Set *usernames) {
    MakeEmpty(users); // Inisialisasi list
    set_create_empty(usernames); // Inisialisasi set

    // Tambahkan pengguna awal ke ListUser dan Set
    SetEl(users, 0, (User){"a", "a", ROLE_MANAGER});
    set_insert(usernames, "nimonsslatte");
    
    // Initialize doctor
    User dokter_user = {"Neroifa", "Neroifa123", ROLE_DOKTER};
    dokter_user.dataDokter = (Dokter*) malloc(sizeof(Dokter));
    dokter_user.dataDokter->id = 1;
    strcpy(dokter_user.dataDokter->username, dokter_user.username);
    dokter_user.dataDokter->ruangan = '\0'; // belum ditugaskan
    SetEl(users, 1, dokter_user);
    set_insert(usernames, "Neroifa");

    // Initialize patient "GRO"
    User pasien_gro = {"GRO", "NeroifaCantik", ROLE_PASIEN};
    pasien_gro.dataPasien = (Pasien*) malloc(sizeof(Pasien));
    pasien_gro.dataPasien->id = 2;
    pasien_gro.dataPasien->posisiAntrian = 0;
    pasien_gro.dataPasien->status = butuhDiagnosa;
    pasien_gro.dataPasien->jumlahObat = 0;
    pasien_gro.dataPasien->id_dokter = -1;
    // Data medis saja, biar identifikasi penyakit jalan
    pasien_gro.dataPasien->suhu = 37.0;
    pasien_gro.dataPasien->tekananDarah[0] = 110;
    pasien_gro.dataPasien->tekananDarah[1] = 70;
    pasien_gro.dataPasien->detakJantung = 80;
    pasien_gro.dataPasien->saturasiOksigen = 98;
    pasien_gro.dataPasien->kadarGulaDarah = 90;
    pasien_gro.dataPasien->beratBadan = 60;
    pasien_gro.dataPasien->tinggiBadan = 170;
    pasien_gro.dataPasien->kadarKolesterol = 180;
    pasien_gro.dataPasien->trombosit = 250;
    SetEl(users, 2, pasien_gro);
    set_insert(usernames, "GRO");

    // Initialize patient "nimonsganteng"
    User pasien_nimons = {"nimonsganteng", "KelompokAmatGacor", ROLE_PASIEN};
    pasien_nimons.dataPasien = (Pasien*) malloc(sizeof(Pasien));
    pasien_nimons.dataPasien->id = 3;
    pasien_nimons.dataPasien->posisiAntrian = 0;
    pasien_nimons.dataPasien->status = butuhDiagnosa;
    pasien_nimons.dataPasien->jumlahObat = 0;
    pasien_nimons.dataPasien->id_dokter = -1;
    // Data medis saja, biar identifikasi penyakit jalan
    pasien_nimons.dataPasien->suhu = 36.8;
    pasien_nimons.dataPasien->tekananDarah[0] = 150;
    pasien_nimons.dataPasien->tekananDarah[1] = 100;
    pasien_nimons.dataPasien->detakJantung = 85;
    pasien_nimons.dataPasien->saturasiOksigen = 97;
    pasien_nimons.dataPasien->kadarGulaDarah = 100;
    pasien_nimons.dataPasien->tinggiBadan = 175;
    pasien_nimons.dataPasien->beratBadan = 65;
    pasien_nimons.dataPasien->kadarKolesterol = 200;
    pasien_nimons.dataPasien->trombosit = 300;
    SetEl(users, 3, pasien_nimons);
    set_insert(usernames, "nimonsganteng");

    SetLength(users, 4);
}