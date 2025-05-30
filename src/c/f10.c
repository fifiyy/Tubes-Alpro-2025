#include <stdio.h>
#include "../header/f10.h"
#include "../header/dokter.h"

void tambah_dokter (ListUser *users, Set *usernames){
    if (current_user == NULL) {
        printf("\nTidak ada pengguna yang sedang login. Silakan login terlebih dahulu.\n");
        return;
    }

    if (current_user->role != ROLE_MANAGER){
        printf ("Akses ditolak. Anda bukan Manager.\n");
        return;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (!is_alpha_string(username)) {
        printf("Username hanya boleh berisi huruf!\n");
        return;
    }
    
    if (!is_username_unique(usernames, username)) {
        printf("Sudah ada dokter bernama %s!\n", username);
        return;
    }
    
    printf("Password: ");
    if (scanf("%49s", password) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (IsFull(*users)) {
        printf("Kapasitas user penuh!\n");
        return;
    }
    
    User new_user;
    strcpy(new_user.username, username);
    strcpy(new_user.password, password);
    new_user.role = ROLE_DOKTER;

    new_user.dataDokter = (Dokter*) malloc(sizeof(Dokter));
    if (new_user.dataDokter == NULL) {
        printf("Gagal mengalokasikan memori untuk dokter baru.\n");
        return;
    }
    new_user.dataDokter->id = NbElmt(*users) + 1; // ID unik berdasarkan jumlah user
    strcpy(new_user.dataDokter->username, username);
    new_user.dataDokter->ruangan = '\0'; // belum ditugaskan

    SetEl(users, NbElmt(*users), new_user);
    SetLength(users, NbElmt(*users) + 1);
    set_insert(usernames, username); // Tambahkan username ke dalam Set
    
    printf("Dokter %s berhasil ditambahkan!\n", username);
}

void assign_dokter (ListUser *users, ListRuangan *ruangan){
     if (current_user == NULL) {
        printf("Anda belum login.\n");
        return;
    }

    if (current_user->role != ROLE_MANAGER){
        printf ("Akses ditolak. Anda bukan Manager.\n");
        return;
    }

    char username[USERNAME_LEN];
    int nomor_ruangan;

    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }
    
    if (!is_alpha_string(username)) {
        printf("Username hanya boleh berisi huruf!\n");
        return;
    }

    boolean dokter_found = false;
    User *dokter_baru = NULL;
    for (int i = GetFirstIdx(*users); i <= GetLastIdx(*users); i++) {
        User *user = &users->data[i];
        if (strcmp(user->username, username) == 0 && user->role == ROLE_DOKTER) {
            dokter_baru = user;
            dokter_found = true;
            break;
        }
    }

    if (!dokter_found) {
        printf("Dokter dengan username %s tidak ditemukan!\n", username);
        return;
    }

    printf("Ruangan: ");
    if (scanf("%d", &nomor_ruangan) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }

    int ruangan_found = false;
    int ruangan_idx = -1;
    for (int i = 0; i < ruangan->jumlah; i++) {
        if (ruangan->ruang[i].nomor == nomor_ruangan) {
            ruangan_found = true;
            ruangan_idx = i;
            break;
        }
    }

    if (!ruangan_found) {
        printf("Tidak ada ruangan nomor %d!\n", nomor_ruangan);
        return;
    }

     // Cek apakah dokter sudah bertugas di ruangan lain
    for (int i = 0; i < ruangan->jumlah; i++) {
        if (ruangan->ruang[i].dokter != NULL && 
            ruangan->ruang[i].dokter->id == dokter_baru->dataDokter->id) {
            printf("Dokter %s sudah menempati ruangan %d!\n", 
                  username, ruangan->ruang[i].nomor);
            printf("Silakan cari ruangan lain untuk dokter %s.\n", username);
            return;
        }
    }

    // Cek apakah ruangan sudah ada dokternya
    if (ruangan->ruang[ruangan_idx].dokter != NULL) {
        printf("Ruangan %d sudah ditempati oleh dokter %s!\n", 
              nomor_ruangan, ruangan->ruang[ruangan_idx].dokter->username);
        return;
    }

    // Assign dokter ke ruangan
    ruangan->ruang[ruangan_idx].dokter = dokter_baru->dataDokter;
    dokter_baru->dataDokter->ruangan = nomor_ruangan; // Set ruangan dokter

    printf("Dokter %s berhasil diassign ke ruangan %d!\n", username, nomor_ruangan);
}
