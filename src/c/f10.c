#include <stdio.h>
#include "../header/f10.h"
#include "../header/dokter.h"

void tambah_dokter (ListUser *users, Set *usernames){
    if (currUser == NULL) {
        printf("\nTidak ada pengguna yang sedang login. Silakan login terlebih dahulu.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
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
    
    if (is_full(*users)) {
        printf("Kapasitas user penuh!\n");
        return;
    }
    
    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.role = ROLE_DOKTER;

    newUser.dataDokter = (Dokter*) malloc(sizeof(Dokter));
    if (newUser.dataDokter == NULL) {
        printf("Gagal mengalokasikan memori untuk dokter baru.\n");
        return;
    }
    newUser.dataDokter->id = nb_elmt(*users) + 1; // ID unik berdasarkan jumlah user
    strcpy(newUser.dataDokter->username, username);
    newUser.dataDokter->ruangan = '\0'; // belum ditugaskan

    set_el(users, nb_elmt(*users), newUser);
    set_length(users, nb_elmt(*users) + 1);
    set_insert(usernames, username); // Tambahkan username ke dalam Set
    
    printf("Dokter %s berhasil ditambahkan!\n", username);
}

void assign_dokter (ListUser *users, ListRuangan *ruangan){
     if (currUser == NULL) {
        printf("Anda belum login.\n");
        return;
    }

    if (currUser->role != ROLE_MANAGER){
        printf ("Akses ditolak. Anda bukan Manager.\n");
        return;
    }

    char username[USERNAME_LEN];
    int nomorRuangan;

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

    boolean isDokterFound = false;
    User *newDokter = NULL;
    for (int i = get_first_idx(*users); i <= get_last_idx(*users); i++) {
        User *user = &users->data[i];
        if (strcmp(user->username, username) == 0 && user->role == ROLE_DOKTER) {
            newDokter = user;
            isDokterFound = true;
            break;
        }
    }

    if (!isDokterFound) {
        printf("Dokter dengan username %s tidak ditemukan!\n", username);
        return;
    }

    printf("Ruangan: ");
    if (scanf("%d", &nomorRuangan) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        return;
    }

    int isRuangFound = false;
    int idxRuang = -1;
    for (int i = 0; i < ruangan->jumlah; i++) {
        if (ruangan->ruang[i].nomor == nomorRuangan) {
            isRuangFound = true;
            idxRuang = i;
            break;
        }
    }

    if (!isRuangFound) {
        printf("Tidak ada ruangan nomor %d!\n", nomorRuangan);
        return;
    }

     // Cek apakah dokter sudah bertugas di ruangan lain
    for (int i = 0; i < ruangan->jumlah; i++) {
        if (ruangan->ruang[i].dokter != NULL && 
            ruangan->ruang[i].dokter->id == newDokter->dataDokter->id) {
            printf("Dokter %s sudah menempati ruangan %d!\n", 
                  username, ruangan->ruang[i].nomor);
            printf("Silakan cari ruangan lain untuk dokter %s.\n", username);
            return;
        }
    }

    // Cek apakah ruangan sudah ada dokternya
    if (ruangan->ruang[idxRuang].dokter != NULL) {
        printf("Ruangan %d sudah ditempati oleh dokter %s!\n", 
              nomorRuangan, ruangan->ruang[idxRuang].dokter->username);
        return;
    }

    // Assign dokter ke ruangan
    ruangan->ruang[idxRuang].dokter = newDokter->dataDokter;
    newDokter->dataDokter->ruangan = nomorRuangan; // Set ruangan dokter

    printf("Dokter %s berhasil diassign ke ruangan %d!\n", username, nomorRuangan);
}