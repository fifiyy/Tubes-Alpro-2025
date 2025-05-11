#include <stdio.h>
#include "../header/f10.h"

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

    SetEl(users, NbElmt(*users), new_user);
    SetLength(users, NbElmt(*users) + 1);
    Insert(usernames, username); // Tambahkan username ke dalam Set
    
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
    User dokter_baru;
    for (int i = GetFirstIdx(*users); i <= GetLastIdx(*users); i++) {
        User user = GetElmt(*users, i);
        if (strcmp(user.username, username) == 0 && user.role == ROLE_DOKTER) {
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

    for (int i = 0; i < ruangan->jumlah; i++) {
        //sudah menempati ruangan
        if (strcmp(ruangan->ruang[i].dokter, username) == 0) {
            printf("Dokter %s sudah diassign ke ruangan %d!\n", username, ruangan->ruang[i].nomor);
            return;
        }
    }

    //belum ada dokkter
    if (strcmp(ruangan->ruang[ruangan_idx].dokter, "") == 0) {
        strcpy(ruangan->ruang[ruangan_idx].dokter, username);
        printf("Dokter %s berhasil diassign ke ruangan %d!\n", username, nomor_ruangan);
        return;
    }

    else if (strcmp(ruangan->ruang[ruangan_idx].dokter, "-") != 0 && ruangan_idx == -1) {
        printf("Dokter %s sudah menempati ruangan %d!\n", ruangan->ruang[ruangan_idx].dokter, nomor_ruangan);
        printf("Silakan cari ruangan lain untuk dokter %s.\n", username);

    // ruangan ditempati dokter lain
    printf("Dokter %s sudah menempati ruangan %d!\n", ruangan->ruang[ruangan_idx].dokter, ruangan_idx);
    printf("Ruangan %d juga sudah ditempati dokter %s!\n", nomor_ruangan, ruangan->ruang[ruangan_idx].dokter);

    }
}
