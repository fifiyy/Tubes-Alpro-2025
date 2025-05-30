#include "init_data.h"

// Inisialisasi array obat
Obat ketObat[] = {
    {1, "Oseltamivir"},
    {2, "Vitamin C"},
    {3, "Remdesivir"},
    {4, "Lisinopril"},
    {5, "Metfomin"},
};
const int JUMLAH_OBAT = sizeof(ketObat) / sizeof(ketObat[0]);

// Inisialisasi array penyakit
Penyakit ketPenyakit[] = {
    {1, "Influenza", 36, 38.5, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {2, "COVID-19", 36, 39, 90, 130, 60, 85, 60, 120, 90, 100, 70, 180, 45, 90, 150, 185, 150, 240, 150, 450},
    {3, "Hipertensi", 36, 37.5, 140, 180, 90, 120, 60, 100, 90, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {4, "Diabetes Mellitus", 36, 37.5, 90, 140, 60, 90, 60, 100, 90, 100, 126, 200, 45, 90, 150, 185, 150, 240, 150, 450},
    {5, "Anemia", 36, 37, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
};
const int JUMLAH_PENYAKIT = sizeof(ketPenyakit) / sizeof(ketPenyakit[0]);

void init_data(ListUser *users, Set *usernames) {
    MakeEmpty(users); // Inisialisasi list
    set_create_empty(usernames); // Inisialisasi set

    // Tambahkan pengguna awal ke ListUser dan Set
    SetEl(users, 0, (User){"a", "a", ROLE_MANAGER});
    set_insert(usernames, "nimonsslatte");
    
    // Initialize doctor
    User dokter_user = {"Neroifa", "Neroifa123", ROLE_DOKTER};
    dokter_user.dokter_data = (Dokter*) malloc(sizeof(Dokter));
    dokter_user.dokter_data->id = 1;
    strcpy(dokter_user.dokter_data->username, dokter_user.username);
    dokter_user.dokter_data->ruangan = '\0'; // belum ditugaskan
    SetEl(users, 1, dokter_user);
    set_insert(usernames, "Neroifa");

    // Initialize patient "GRO"
    User pasien_gro = {"GRO", "NeroifaCantik", ROLE_PASIEN};
    pasien_gro.pasien_data = (Pasien*) malloc(sizeof(Pasien));
    // Initialize all Pasien fields
    pasien_gro.pasien_data->id = 2;
    pasien_gro.pasien_data->posisiAntrian = -1; // Not in queue
    pasien_gro.pasien_data->status = statusDiagnosa;
    pasien_gro.pasien_data->jumlahObat = 0;
    pasien_gro.pasien_data->id_dokter = -1; // No doctor assigned
    SetEl(users, 2, pasien_gro);
    set_insert(usernames, "GRO");

    // Initialize patient "nimonsganteng"
    User pasien_nimons = {"nimonsganteng", "KelompokAmatGacor", ROLE_PASIEN};
    pasien_nimons.pasien_data = (Pasien*) malloc(sizeof(Pasien));
    // Initialize all Pasien fields
    pasien_nimons.pasien_data->id = 3;
    pasien_nimons.pasien_data->posisiAntrian = -1; // Not in queue
    pasien_nimons.pasien_data->status = statusDiagnosa;
    pasien_nimons.pasien_data->jumlahObat = 0;
    pasien_nimons.pasien_data->id_dokter = -1; // No doctor assigned
    SetEl(users, 3, pasien_nimons);
    set_insert(usernames, "nimonsganteng");

    SetLength(users, 4);
}