#include "../header/Register.h"
#include "../ADT/header/List_User.h"
#include "../ADT/header/Set.h"
#include "../header/User.h"    

boolean is_username_unique(const Set *usernames, const char* username) {
    return !set_is_member(*usernames, username); // Gunakan fungsi IsMember dari Set
}

void register_pasien(ListUser *users, Set *usernames) {
    if (currUser != NULL) {
        printf("Anda sudah login. Silakan logout terlebih dahulu.\n");
        return;
    }
    
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    
    printf("\n+-----------------------------------------------+\n");
    printf("|                   REGISTRASI                  |\n");
    printf("+-----------------------------------------------+\n");

    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (!is_alpha_string(username)) {
        printf("\nERROR: Username hanya boleh berisi huruf!\n");
        return;
    }
    
    if (!is_username_unique(usernames, username)) {
        printf("\nERROR: Registrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
        return;
    }
    
    printf("Password: ");
    if (scanf("%49s", password) != 1) {
        printf("\nERROR: Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (list_is_full(*users)) {
        printf("\nERROR: Kapasitas user penuh!\n");
        return;
    }
    
    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.role = ROLE_PASIEN;

    newUser.dataPasien = (Pasien*) malloc(sizeof(Pasien));
    if (newUser.dataPasien == NULL) {
        printf("\nERROR: Gagal mengalokasikan memori untuk pasien baru.\n");
        return;
    }

    newUser.idUser = list_nb_elmt(*users); // ID unik berdasarkan jumlah user
    newUser.dataPasien->id = list_nb_elmt(*users); // ID unik berdasarkan jumlah user
    newUser.dataPasien->jumlahObat = 0; // Inisialisasi jumlah obat
    newUser.dataPasien->idRuangan = -1; // Pasien belum dalam ruangan
    newUser.dataPasien->posisiAntrian = -1; // Pasien belum dalam antrian   
    newUser.dataPasien->jumlahObatResep = 0; // Inisialisasi jumlah obat resep
    newUser.dataPasien->sisaNyawa = 3;
    newUser.dataPasien->status = butuhDiagnosa; // Status awal pasien
    
    list_set_el(users, list_nb_elmt(*users), newUser);
    // list_set_length(users, list_nb_elmt(*users) + 1);
    set_insert(usernames, username); // Tambahkan username ke dalam Set
    create_stack(&newUser.dataPasien->perutPasien); // Inisialisasi stack perut pasien
    
    printf(">> Pasien %s berhasil ditambahkan!\n", username);
}